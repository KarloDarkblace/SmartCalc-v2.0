#include "s21_credit_calc.h"

namespace s21 {

AnnuityCreditResult CreditModel::CalculateAnnuity(
    const CreditParams& credit_params) {
  AnnuityCreditResult result;
  double monthly_rate = credit_params.rate / 12 / 100;

  result.monthly_payment =
      (credit_params.amount * monthly_rate) /
      (1 - std::pow(1 + monthly_rate, -credit_params.term));

  result.total_payment = result.monthly_payment * credit_params.term;
  result.overpayment = result.total_payment - credit_params.amount;

  return result;
}

DifferentialCreditResult CreditModel::CalculateDifferential(
    const CreditParams& credit_params) {
  DifferentialCreditResult result;

  double temp_amount = credit_params.amount;
  double monthly_rate = credit_params.rate / 12 / 100;
  double monthly_payment = 0.0f;
  double main_payment = credit_params.amount / credit_params.term;

  while (temp_amount > 0) {
    monthly_payment = temp_amount * monthly_rate;
    result.overpayment += monthly_payment;
    temp_amount -= main_payment;
  }

  result.total_payment = credit_params.amount + result.overpayment;

  result.first_monthly_payment =
      (credit_params.amount * monthly_rate) + main_payment;
  result.last_monthly_payment = monthly_payment + main_payment;

  return result;
}

}  // namespace s21
