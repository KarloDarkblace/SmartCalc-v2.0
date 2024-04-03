#include "../s21_calculator_model.h"

namespace s21 {

int CalculatorModel::CalculatePolishNotation(const std::string& input_line,
                                             long double& result,
                                             const long double x) {
  int return_value = NO_ERROR;

  std::string polish_notation;
  return_value = ParserExpression(input_line, polish_notation);
  if (return_value == NO_ERROR) {
    return_value = PolishSolution(polish_notation, result, x);
  }
  return return_value;
}

}  // namespace s21
