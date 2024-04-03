#include "s21_deposit_calc.h"

namespace s21 {

void DepositModel::CheckReplenishmentsTransactions(
    const std::list<Transaction>& replenishments, double& deposit,
    const QDate& current_date) {
  for (auto& transaction : replenishments) {
    if (transaction.date == current_date) {
      deposit += transaction.amount;
    }
  }
}

void DepositModel::CheckWithdrawalsTransactions(
    const std::list<Transaction>& withdrawals, double& deposit,
    const QDate& current_date) {
  for (auto& transaction : withdrawals) {
    if (transaction.date == current_date) {
      deposit -= transaction.amount;
    }
  }
}

bool DepositModel::CheckTransactions(const TransactionsList& transactions,
                                     double& deposit,
                                     const QDate& current_date) {
  bool return_value = false;
  CheckReplenishmentsTransactions(transactions.replenishments, deposit,
                                  current_date);
  CheckWithdrawalsTransactions(transactions.withdrawals, deposit, current_date);
  if (deposit <= 0) {
    return_value = true;
  }
  return return_value;
}

double DepositModel::ToDayRate(const double& rate) {
  return rate / 365;
}

double DepositModel::CalculateYearTax(double current_earnings, double tax_rate,
                                      int key_rate) {
  double return_value = 0;
  current_earnings -= (10000 * key_rate);
  if (current_earnings > 0.0) {
    return_value = current_earnings * (tax_rate / 100);
  }
  return return_value;
}

double DepositModel::CalculateDailyInterest(const double& deposit,
                                            const double& dayRate) {
  return (deposit / 100) * dayRate;
}

long double DepositModel::UpdateYearlyTax(const QDate& current_date,
                                          const DepositParams& deposit_params,
                                          double& current_earnings) {
  long double return_value = 0.0f;
  if (current_date.year() != current_date.addDays(1).year()) {
    return_value = CalculateYearTax(current_earnings, deposit_params.tax_rate,
                                    deposit_params.key_rate);
    current_earnings = 0;
  }
  return return_value;
}

bool DepositModel::IsCapitalizationTime(const DepositParams& deposit_params,
                                        const QDate current_date) {
  bool isCapitalizationTime = false;
  switch (deposit_params.frequency_of_payments) {
    case EVERY_DAY:
      isCapitalizationTime = true;
      break;
    case EVERY_WEEK:
      isCapitalizationTime = current_date.dayOfWeek() == 7;
      break;
    case ONCE_A_MONTH:
      isCapitalizationTime = current_date.day() == current_date.daysInMonth();
      break;
    case ONCE_A_YEAR:
      isCapitalizationTime = current_date.dayOfYear() == 365 ||
                             (current_date.isLeapYear(current_date.year()) &&
                              current_date.dayOfYear() == 366);
      break;
  }
  return isCapitalizationTime;
}

double DepositModel::AccrueRemainingCapitalization(
    double& deposit, const double& current_earnings,
    const DepositParams& deposit_params) {
  if (deposit_params.capitalization) {
    deposit += current_earnings;
  }
  return current_earnings;
}

double DepositModel::CalculateInterestMultiplier(
    const DepositParams& deposit_params) {
  switch (deposit_params.frequency_of_payments) {
    case EVERY_DAY:
      return 1;
    case EVERY_WEEK:
      return 7;
    case ONCE_A_MONTH:
      return 30;
    case ONCE_A_YEAR:
      return 365;
  }
  return 0;
}

DepositResult DepositModel::CalculateDeposit(
    const DepositParams& deposit_params) {
  DepositResult result;
  QDate current_date = QDate::currentDate();

  double current_earnings = 0;
  double deposit = deposit_params.deposit_amount;
  double dayRate = ToDayRate(deposit_params.interest_rate);

  for (int period = deposit_params.posting_period; period > 0;
       --period, current_date = current_date.addDays(1)) {
    if (CheckTransactions(deposit_params.transactions, deposit, current_date)) {
      break;
    }

    result.tax_amount +=
        UpdateYearlyTax(current_date, deposit_params, current_earnings);

    double interest = CalculateDailyInterest(deposit, dayRate);
    result.accrued_interest += interest;
    current_earnings += interest;

    if (IsCapitalizationTime(deposit_params, current_date) &&
        deposit_params.capitalization) {
      deposit += interest * CalculateInterestMultiplier(deposit_params);
    }
  }

  result.tax_amount += CalculateYearTax(
      current_earnings, deposit_params.tax_rate, deposit_params.key_rate);
  if (deposit_params.capitalization) {
    result.total_amount =
        (deposit_params.deposit_amount + result.accrued_interest) -
        result.tax_amount;
  } else {
    result.total_amount =
        (deposit + result.accrued_interest) - result.tax_amount;
  }

  return result;
}

}  // namespace s21
