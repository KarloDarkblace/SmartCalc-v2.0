#include "s21_qmain_controller.h"

namespace s21 {

bool QMainController::IsExpressionNormal(const std::string& expression,
                                         const long double& x) {
  long double number;
  int return_error =
      calculator_model.CalculatePolishNotation(expression, number, x);
  return return_error == NO_ERROR;
}

int QMainController::CalculateExpression(const std::string& input_line,
                                         long double& result,
                                         const long double x) {
  int return_error =
      calculator_model.CalculatePolishNotation(input_line, result, x);
  return return_error;
}

}  // namespace s21
