#include "s21_qcredit_controller.h"

namespace s21 {

AnnuityCreditResult QCreditController::CalculateAnnuityMonthPayments(
    const CreditParams& credit_params) {
  AnnuityCreditResult annuity_result =
      credit_model.CalculateAnnuity(credit_params);
  return annuity_result;
}

DifferentialCreditResult QCreditController::CalculateDifferentialMonthPayments(
    const CreditParams& credit_params) {
  DifferentialCreditResult differential_result =
      credit_model.CalculateDifferential(credit_params);
  return differential_result;
}

}  // namespace s21
