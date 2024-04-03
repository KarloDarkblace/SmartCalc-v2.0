#include <gtest/gtest.h>

#include "../model/polish/s21_calculator_model.h"

TEST(polish, regular_test_1) {
  std::string expression = "2 + 2";
  long double assert_result = 4.0f;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, regular_test_2) {
  std::string expression = "2 + (-2)";
  long double assert_result = 0.0f;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, sign_test) {
  std::string expression = "-2";
  long double assert_result = -2;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, subtraction_test) {
  std::string expression = "10 - 5";
  long double assert_result = 5.0;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, multiplication_test) {
  std::string expression = "3 * 4";
  long double assert_result = 12.0;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, division_test) {
  std::string expression = "15 / 3";
  long double assert_result = 5.0;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, complex_expression_test) {
  std::string expression = "(2 + 2) * (2 + 3)";
  long double assert_result = 20.0;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, exponentiation_test) {
  std::string expression = "2 ^ 3";
  long double assert_result = 8.0;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, unary_operator_test) {
  std::string expression = "-5 + 2";
  long double assert_result = -3.0;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, function_sin_test) {
  std::string expression = "sin(0)";
  long double assert_result = 0.0;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, function_cos_test) {
  std::string expression = "cos(0)";
  long double assert_result = 1.0;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, complex_expression_test_1) {
  std::string expression = "(5 + 3) * (8 - 2) / 2 ^ 2";
  long double assert_result = 12.0;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, complex_expression_with_functions_test) {
  std::string expression = "sin(0) + cos(0) * tan(45)";
  long double assert_result = (sin(0) + cos(0)) * tan(45);

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_NEAR(polish_result, assert_result, 1e-6);
}

TEST(polish, complex_expression_with_exponentiation_test) {
  std::string expression = "3 ^ 3 + sqrt(16) - 2";
  long double assert_result = 29.0;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, complex_expression_with_unary_operators_test) {
  std::string expression = "(2 + 3) * 4 + 5";
  long double assert_result = 25;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, expression_with_multiple_brackets_test) {
  std::string expression = "((2 + 3) * (4 + 5)) / (3 - 2)";
  long double assert_result = 45.0;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, expression_with_nested_functions_test) {
  std::string expression = "cos(sin(tan(45)))";
  long double assert_result = cos(sin(tan(45)));

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_NEAR(polish_result, assert_result, 1e-6);
}

TEST(polish, expression_with_x_variable_test_1) {
  std::string expression = "x * 5 + 3";
  long double assert_result = 23.0f;

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 4);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, expression_with_x_variable_test_2) {
  std::string expression = "sin(x)";
  long double assert_result = sin(4);

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 4);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, expression_with_x_variable_test_3) {
  std::string expression = "sin(x+1)";
  long double assert_result = sin(8 + 1);

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 8);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, expression_with_x_variable_test_4) {
  std::string expression = "sin(-x)";
  long double assert_result = sin(-4);

  s21::CalculatorModel calculator;
  long double polish_result;

  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 4);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}

TEST(polish, function_as_operator_argument) {
  std::string expression = "2 + sin(1) * 4";
  long double assert_result = 2 + sin(1) * 4;
  s21::CalculatorModel calculator;
  long double polish_result;
  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_NEAR(polish_result, assert_result, 1e-6);
}

TEST(polish, mixed_functions_and_operators) {
  std::string expression = "2 ^ acos(-1) * asin(1) - 3 * ln(0.5)";
  long double assert_result = pow(2, acos(-1)) * asin(1) - 3 * log10(0.5);
  s21::CalculatorModel calculator;
  long double polish_result;
  int error_code =
      calculator.CalculatePolishNotation(expression, polish_result, 0);
  ASSERT_EQ(error_code, s21::NO_ERROR);
  ASSERT_DOUBLE_EQ(polish_result, assert_result);
}