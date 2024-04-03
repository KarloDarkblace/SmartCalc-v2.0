#ifndef CPP3_SMARTCALC_V2_SRC_CONTROLLER_MAIN_S21_NAIN_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_SRC_CONTROLLER_MAIN_S21_NAIN_CONTROLLER_H_

#include "../../model/polish/s21_calculator_model.h"

namespace s21 {

class QMainController {
 public:
  bool IsExpressionNormal(const std::string& expression,
                          const long double& x = 0.0f);
  int CalculateExpression(const std::string& input_line, long double& result,
                          const long double x = 0.0f);

 private:
  CalculatorModel calculator_model;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_CONTROLLER_MAIN_S21_NAIN_CONTROLLER_H_
