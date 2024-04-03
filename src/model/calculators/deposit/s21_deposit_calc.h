#ifndef CPP3_SMARTCALC_V2_SRC_MODEL_CALCULATORS_DEPOSIT_S21_DEPOSIT_CALC_H
#define CPP3_SMARTCALC_V2_SRC_MODEL_CALCULATORS_DEPOSIT_S21_DEPOSIT_CALC_H

#include <cmath>
#include <list>
#include <string>

#include <QDate>

namespace s21 {

enum InterestAccrualFrequency {
  EVERY_DAY,
  EVERY_WEEK,
  ONCE_A_MONTH,
  ONCE_A_YEAR
};

struct Transaction {
  QDate date;
  double amount;
};

struct TransactionsList {
  std::list<Transaction> replenishments;
  std::list<Transaction> withdrawals;
};

struct DepositParams {
  double key_rate = 16;   // %
  double tax_rate;        // %
  double interest_rate;   // %
  double deposit_amount;  // rub

  int posting_period;  // days
  bool capitalization;

  InterestAccrualFrequency frequency_of_payments;
  TransactionsList transactions;
};

struct DepositResult {
  long double accrued_interest = 0;
  long double tax_amount = 0;
  long double total_amount = 0;
};

class DepositModel {
 public:
  DepositResult CalculateDeposit(const DepositParams& deposit_params);

 private:
  long double UpdateYearlyTax(const QDate& current_date,
                              const DepositParams& deposit_params,
                              double& current_earnings);
  double CalculateInterestMultiplier(const DepositParams& deposit_params);
  double AccrueRemainingCapitalization(double& deposit,
                                       const double& current_earnings,
                                       const DepositParams& deposit_params);
  double CalculateDailyInterest(const double& deposit, const double& dayRate);
  double CalculateYearTax(double current_earnings, double tax_rate,
                          int key_rate);
  double ToDayRate(const double& rate);
  bool CheckTransactions(const TransactionsList& transactions, double& deposit,
                         const QDate& current_date);
  bool IsCapitalizationTime(const DepositParams& deposit_params,
                            const QDate current_date);
  void CheckWithdrawalsTransactions(const std::list<Transaction>& withdrawals,
                                    double& deposit, const QDate& current_date);
  void CheckReplenishmentsTransactions(
      const std::list<Transaction>& replenishments, double& deposit,
      const QDate& current_date);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_MODEL_CALCULATORS_DEPOSIT_CALC_S21_DEPOSIT_CALC_H
