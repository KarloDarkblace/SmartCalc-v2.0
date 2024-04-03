#ifndef CPP3_SMARTCALC_V2_SRC_MODEL_POLISH_S21_POLISH_H_
#define CPP3_SMARTCALC_V2_SRC_MODEL_POLISH_S21_POLISH_H_

#include <map>
#include <stack>
#include <string>
#include <vector>

#include <cctype>
#include <cmath>
#include <iostream>

namespace s21 {

constexpr int NO_ERROR = 0;
constexpr int ERROR = 1;

class CalculatorModel {
 public:
  int CalculatePolishNotation(const std::string& input_line,
                              long double& result, const long double x = 0.0f);

 private:
  bool IsDot(const char& symb);
  bool IsNumber(const char& symb);
  bool IsExponent(const char& symb);
  bool IsOperator(const char& symb);
  bool IsBracket(const char& symb);
  bool IsPlusOrMinus(const char& symb);
  bool IsFunction(const std::string input_line, int position);
  bool IsCorrectNumber(const std::string& input_line, size_t& position);
  bool IsBracketAfterFunction(const std::string& input_line, size_t& position);
  bool IsCorrectExponentialForm(const std::string& input_line,
                                size_t& position);
  bool IsUnaryOperator(size_t position, const std::string& input_line);
  bool IsBracketNormal(const std::string& input_line, size_t& position,
                       int& balance);

  void HandleNumber(size_t& position, const std::string& input_line,
                    std::string& result_line, std::stack<char>& polish_stack);
  void HandleBracket(size_t& position, char bracket, std::string& result_line,
                     std::stack<char>& polish_stack);
  void HandleOperator(const char& symbol, size_t& position,
                      std::string& result_line, std::stack<char>& polish_stack,
                      const std::string& input_line);
  void HandleX(size_t& position, const std::string& input_line,
               std::string& result_line, std::stack<char>& polish_stack);
  void HandleFunction(size_t& position, const std::string& input_line,
                      std::string& result_line, std::stack<char>& polish_stack);

  int CheckPriority(const char& symb);
  int CheckSymbol(size_t& position, const std::string& input_line,
                  std::string& result_line, std::stack<char>& polish_stack);
  int CheckAllExpression(const std::string& input_line);

  void PopAllStack(std::stack<char>& polish_stack, std::string& result_line);
  void StringToDouble(const std::string& polish_notation, size_t& position,
                      std::stack<long double>& numbers);

  char GetSymbolFromFunction(size_t& position, const std::string& input_line);

  int StringProcessing(const std::string& polish_notation, size_t& position,
                       std::stack<long double>& numbers,
                       const long double x = 0.0f);
  int CalculationFunctions(const std::string& polish_notation, size_t& position,
                           std::stack<long double>& numbers);
  int ArithmeticOperations(const std::string& polish_notation, size_t& position,
                           std::stack<long double>& numbers);

  int ParserExpression(const std::string& input_line, std::string& result);
  int PolishSolution(const std::string& polish_notation, long double& result,
                     const long double x = 0.0f);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_MODEL_POLISH_S21_POLISH_H_
