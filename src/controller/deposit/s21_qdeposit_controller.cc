#include "s21_qdeposit_controller.h"

namespace s21 {

DepositResult QDepositController::CalculateDeposit(
    const DepositParams& deposit_params) {
  DepositResult deposit_result = deposit_model.CalculateDeposit(deposit_params);
  return deposit_result;
}

}  // namespace s21
