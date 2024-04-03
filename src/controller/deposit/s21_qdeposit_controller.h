#ifndef CPP3_SMARTCALC_V2_SRC_CONTROLLER_DEPOSIT_S21_DEPOSIT_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_SRC_CONTROLLER_DEPOSIT_S21_DEPOSIT_CONTROLLER_H_

#include "../../model/calculators/deposit/s21_deposit_calc.h"

namespace s21 {
class QDepositController {
 public:
  DepositResult CalculateDeposit(const DepositParams& deposit_params);

 private:
  DepositModel deposit_model;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_CONTROLLER_DEPOSIT_S21_DEPOSIT_CONTROLLER_H_
