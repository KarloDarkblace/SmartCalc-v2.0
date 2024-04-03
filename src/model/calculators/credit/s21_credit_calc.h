#ifndef CPP3_SMARTCALC_V2_SRC_MODEL_CALCULATORS_CREDIT_S21_CREDIT_CALC_H
#define CPP3_SMARTCALC_V2_SRC_MODEL_CALCULATORS_CREDIT_S21_CREDIT_CALC_H

#include <cmath>

namespace s21 {

struct CreditParams {
  double amount = 0;
  double term = 0;
  double rate = 0;
};

struct AnnuityCreditResult {
  double monthly_payment = 0;
  double overpayment = 0;
  double total_payment = 0;
};

struct DifferentialCreditResult {
  double first_monthly_payment = 0;
  double last_monthly_payment = 0;
  double overpayment = 0;
  double total_payment = 0;
};

class CreditModel {
 public:
  AnnuityCreditResult CalculateAnnuity(const CreditParams& credit_params);
  DifferentialCreditResult CalculateDifferential(
      const CreditParams& credit_params);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_MODEL_CALCULATORS_CREDIT_S21_CREDIT_CALC_H
