#include <gtest/gtest.h>

#include "../model/polish/s21_calculator_model.h"

TEST(edge, empty_expression_test) {
  std::string expression = "";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, only_numbers_test) {
  std::string expression = "2 45 4.6";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, zero_division_test) {
  std::string expression = "2 / 0";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, zero_division_complex_test) {
  std::string expression = "(10 / (5 - 5)) * 2";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, expression_ends_with_operator_test) {
  std::string expression = "5 + 2 -";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, number_format_missing_number_after_dot_test) {
  std::string expression = "5. + 2";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, function_with_wrong_arguments_order_test) {
  std::string expression = "5 sin";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, unknown_symbol_test) {
  std::string expression = "5 + 2$a";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, multiple_dots_in_number_test) {
  std::string expression = "5.2.3 + 1";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, division_by_zero_test) {
  std::string expression = "5 / 0";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_expression_test_1) {
  std::string wrong_expression = "22---22";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(wrong_expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_expression_test_2) {
  std::string wrong_expression = "mod 5 2 + 3(-4)";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(wrong_expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_expression_test_3) {
  std::string wrong_expression = "199--";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(wrong_expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_expression_test_4) {
  std::string wrong_expression = "++504+2";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(wrong_expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_expression_test_5) {
  std::string wrong_expression = ".2+4.4";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(wrong_expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_expression_test_6) {
  std::string wrong_expression = "2.2+2e";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(wrong_expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_expression_test_7) {
  std::string wrong_expression = "321.e";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(wrong_expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_expression_test_8) {
  std::string wrong_expression = "5.5.5.5";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(wrong_expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_expression_test_9) {
  std::string wrong_expression = "1.4e*01";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(wrong_expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_expression_test_10) {
  std::string wrong_expression = "10.10000e+000";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(wrong_expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_expression_test_11) {
  std::string wrong_expression = "224,";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(wrong_expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_expression_test_12) {
  std::string wrong_expression = "(-4) + 2.2 - 3 + () - 2";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(wrong_expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_expression_test_13) {
  std::string wrong_expression = "2+2*(-2";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(wrong_expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_expression_test_14) {
  std::string wrong_expression = "2+2+";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(wrong_expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_brackets_test_1) {
  std::string expression = "(5+2*(2-3)";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_brackets_test_2) {
  std::string expression = "2+((-5)";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_brackets_test_3) {
  std::string expression = "(-2)*(2";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, wrong_brackets_test_4) {
  std::string expression = "()(()())))";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, function_without_arguments_test_1) {
  std::string expression = "sin()";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, function_without_arguments_test_2) {
  std::string expression = "cos";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, function_without_arguments_test_3) {
  std::string expression = "cos(x";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}

TEST(edge, function_without_arguments_test_4) {
  std::string expression = "co(4)";

  s21::CalculatorModel calculator;
  long double result;

  bool is_wrong = calculator.CalculatePolishNotation(expression, result);
  ASSERT_TRUE(is_wrong);
}