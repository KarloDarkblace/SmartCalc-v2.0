#ifndef CPP3_SMARTCALC_V2_SRC_CONTROLLER_CREDIT_S21_QCREDIT_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_SRC_CONTROLLER_CREDIT_S21_QCREDIT_CONTROLLER_H_

#include "../../model/calculators/credit/s21_credit_calc.h"

namespace s21 {
class QCreditController {
 public:
  AnnuityCreditResult CalculateAnnuityMonthPayments(
      const CreditParams& credit_params);
  DifferentialCreditResult CalculateDifferentialMonthPayments(
      const CreditParams& credit_params);

 private:
  CreditModel credit_model;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_CONTROLLER_CREDIT_S21_QCREDIT_CONTROLLER_H_
