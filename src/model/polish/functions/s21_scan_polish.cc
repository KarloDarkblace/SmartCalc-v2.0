#include "../s21_calculator_model.h"

namespace s21 {

bool CalculatorModel::IsNumber(const char& symb) {
  return std::isdigit(symb);
}

bool CalculatorModel::IsExponent(const char& symb) {
  return symb == 'e' || symb == 'E';
}

bool CalculatorModel::IsOperator(const char& symb) {
  return symb == '-' || symb == '+' || symb == '*' || symb == '/' ||
         symb == '^';
}

bool CalculatorModel::IsDot(const char& symb) {
  return symb == '.';
}

bool CalculatorModel::IsBracket(const char& symb) {
  return symb == '(' || symb == ')';
}

bool CalculatorModel::IsPlusOrMinus(const char& symb) {
  return symb == '+' || symb == '-';
}

bool CalculatorModel::IsFunction(const std::string input_line, int position) {
  const std::vector<std::string> functions_full = {
      "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log", "mod"};

  const std::vector<std::string> function_reduction = {"c", "s", "t", "a", "b",
                                                       "n", "q", "l", "o", "m"};

  for (const auto& func : functions_full) {
    if (input_line.compare(position, func.length(), func) == 0) {
      return true;
    }
  }

  for (const auto& func : function_reduction) {
    if (input_line.compare(position, func.length(), func) == 0) {
      return true;
    }
  }

  return false;
}

bool CalculatorModel::IsUnaryOperator(size_t position,
                                      const std::string& input_line) {
  int return_value = false;

  position -= 1;
  if (position < input_line.size() && IsPlusOrMinus(input_line[position])) {
    if (position == 0) {
      return_value = true;
    } else if (position - 1 < input_line.size() &&
               input_line[position - 1] == '(') {
      return_value = true;
    }
  }

  return return_value;
}

void CalculatorModel::HandleNumber(size_t& position,
                                   const std::string& input_line,
                                   std::string& result_line,
                                   std::stack<char>& polish_stack) {
  bool isUnaryOperator = IsUnaryOperator(position, input_line);
  while (IsNumber(input_line[position]) || IsDot(input_line[position]) ||
         IsExponent(input_line[position])) {
    if (IsExponent(input_line[position])) {
      if (position + 1 < input_line.size() &&
          (input_line[position + 1] == '+' ||
           input_line[position + 1] == '-')) {
        result_line.push_back(input_line[position]);
        ++position;
      }
    }
    result_line.push_back(input_line[position]);
    ++position;
  }
  if (isUnaryOperator) {
    result_line.push_back(polish_stack.top());
    polish_stack.pop();
  }
  result_line.push_back(' ');
}

void CalculatorModel::HandleBracket(size_t& position, char bracket,
                                    std::string& result_line,
                                    std::stack<char>& polish_stack) {
  if (bracket == '(') {
    polish_stack.push(bracket);
  } else {
    while (!polish_stack.empty() && polish_stack.top() != '(') {
      result_line += polish_stack.top();
      result_line.push_back(' ');
      polish_stack.pop();
    }
    if (!polish_stack.empty()) {
      polish_stack.pop();
    }
  }
  ++position;
}

void CalculatorModel::HandleOperator(const char& symbol, size_t& position,
                                     std::string& result_line,
                                     std::stack<char>& polish_stack,
                                     const std::string& input_line) {
  if (position + 1 < input_line.size() &&
      IsUnaryOperator(position + 1, input_line) == false) {
    while (!polish_stack.empty() &&
           CheckPriority(polish_stack.top()) >= CheckPriority(symbol)) {

      result_line.push_back(polish_stack.top());
      result_line.push_back(' ');
      polish_stack.pop();
    }
  }
  polish_stack.push(symbol);
  ++position;
}

void CalculatorModel::HandleX(size_t& position, const std::string& input_line,
                              std::string& result_line,
                              std::stack<char>& polish_stack) {
  bool isUnaryOperator = IsUnaryOperator(position, input_line);
  result_line.push_back('x');
  ++position;
  if (isUnaryOperator) {
    result_line.push_back(polish_stack.top());
    polish_stack.pop();
  }
  result_line.push_back(' ');
}

void CalculatorModel::HandleFunction(size_t& position,
                                     const std::string& input_line,
                                     std::string& result_line,
                                     std::stack<char>& polish_stack) {
  char funcSymbol = GetSymbolFromFunction(position, input_line);
  if (funcSymbol != '\0') {
    while (!polish_stack.empty() &&
           CheckPriority(polish_stack.top()) >= CheckPriority(funcSymbol)) {
      result_line.push_back(polish_stack.top());
      result_line.push_back(' ');
      polish_stack.pop();
    }
    polish_stack.push(funcSymbol);
  }
}

char CalculatorModel::GetSymbolFromFunction(size_t& position,
                                            const std::string& input_line) {
  static const std::map<std::string, char> functions = {
      {"cos", 'c'},  {"sin", 's'},  {"tan", 't'}, {"acos", 'a'}, {"asin", 'b'},
      {"atan", 'n'}, {"sqrt", 'q'}, {"ln", 'l'},  {"log", 'o'},  {"mod", 'm'}};

  char return_value = '\0';
  for (const auto& pair : functions) {
    const auto& funcName = pair.first;
    if (input_line.compare(position, funcName.length(), funcName) == 0) {
      position += funcName.length();
      return_value = pair.second;
    }
  }
  return return_value;
}

int CalculatorModel::CheckPriority(const char& symb) {
  int return_value = 0;
  switch (symb) {
    case '+':
    case '-':
      return_value = 1;
      break;
    case '*':
    case '/':
    case 'm':  // mod
      return_value = 2;
      break;
    case '^':
      return_value = 3;
      break;
    case 'c':  // cos
    case 's':  // sin
    case 't':  // tan
    case 'a':  // acos
    case 'b':  // asin
    case 'n':  // atan
    case 'q':  // sqrt
    case 'l':  // ln
    case 'o':  // log
      return_value = 4;
      break;
  }
  return return_value;
}

void CalculatorModel::PopAllStack(std::stack<char>& polish_stack,
                                  std::string& result_line) {
  while (!polish_stack.empty()) {
    if (result_line.back() != ' ') {
      result_line.push_back(' ');
    }
    result_line.push_back(polish_stack.top());
    polish_stack.pop();
  }

  if (!result_line.empty() && result_line.back() == ' ') {
    result_line.pop_back();
  }
}

int CalculatorModel::CheckSymbol(size_t& position,
                                 const std::string& input_line,
                                 std::string& result_line,
                                 std::stack<char>& polish_stack) {
  int return_value = NO_ERROR;
  char symbol = input_line[position];
  if (IsNumber(symbol)) {
    HandleNumber(position, input_line, result_line, polish_stack);
  } else if (IsOperator(symbol)) {
    HandleOperator(symbol, position, result_line, polish_stack, input_line);
  } else if (IsBracket(symbol)) {
    HandleBracket(position, symbol, result_line, polish_stack);
  } else if (IsFunction(input_line, position)) {
    HandleFunction(position, input_line, result_line, polish_stack);
  } else if (symbol == 'x') {
    HandleX(position, input_line, result_line, polish_stack);
  } else {
    return_value = ERROR;
  }
  return return_value;
}

bool CalculatorModel::IsBracketAfterFunction(const std::string& input_line,
                                             size_t& position) {
  bool return_value = true;

  if (GetSymbolFromFunction(position, input_line) != 'm') {
    if (input_line[position] != '(') {
      return_value = false;
    }
  }

  return return_value;
}

bool CalculatorModel::IsCorrectNumber(const std::string& input_line,
                                      size_t& position) {
  bool return_value = true;

  while (position < input_line.size() && IsNumber(input_line[position])) {
    ++position;
  }

  if (position + 1 >= input_line.size() && IsDot(input_line[position])) {
    return_value = false;
  }
  if (IsDot(input_line[position])) {
    ++position;
    if (!IsNumber(input_line[position])) {
      return_value = false;
    } else {
      while (position < input_line.size() && IsNumber(input_line[position])) {
        ++position;
      }

      if (IsExponent(input_line[position])) {
        ++position;
        return_value = IsCorrectExponentialForm(input_line, position);
      }
    }
  }

  return return_value;
}

bool CalculatorModel::IsCorrectExponentialForm(const std::string& input_line,
                                               size_t& position) {
  if (position + 3 >= input_line.size()) {
    return false;
  }

  bool return_value = true;

  if (IsPlusOrMinus(input_line[position])) {
    ++position;
    if (!IsNumber(input_line[position + 1]) ||
        !IsNumber(input_line[position + 2])) {
      return_value = false;
    } else {
      position += 2;
      if (!IsOperator(input_line[position])) {
        return_value = false;
      }
    }
  } else {
    return_value = false;
  }

  return return_value;
}

bool CalculatorModel::IsBracketNormal(const std::string& input_line,
                                      size_t& position, int& balance) {
  bool return_value = true;

  if (input_line[position] == '(') {
    ++balance;
    if (position + 1 < input_line.size() && input_line[position + 1] == ')') {
      return_value = false;
    }
  }
  if (input_line[position] == ')') {
    if (balance <= 0) {
      return_value = false;
    }
    --balance;
  }
  if (return_value == true) {
    ++position;
  }

  return return_value;
}

int CalculatorModel::CheckAllExpression(const std::string& input_line) {
  if (input_line.empty()) {
    return ERROR;
  }

  int return_value = NO_ERROR;
  int bracket_balance = 0;
  for (size_t i = 0; i < input_line.size() && return_value == NO_ERROR;) {
    char current_symbol = input_line[i];
    if (IsFunction(input_line, i)) {
      if (!IsBracketAfterFunction(input_line, i)) {
        return_value = ERROR;
      }
    } else if (IsNumber(current_symbol)) {
      if (!IsCorrectNumber(input_line, i)) {
        return_value = ERROR;
      }
    } else if (IsBracket(current_symbol)) {
      if (!IsBracketNormal(input_line, i, bracket_balance)) {
        return_value = ERROR;
      }
    } else if (IsOperator(current_symbol)) {
      if (i + 1 < input_line.size() && IsOperator(input_line[i + 1])) {
        return_value = ERROR;
      } else if (i + 1 >= input_line.size()) {
        return_value = ERROR;
      } else {
        ++i;
      }
    } else if (current_symbol == ' ' || current_symbol == 'x') {
      ++i;
    } else {
      return_value = ERROR;
    }
  }

  if (bracket_balance != 0) {
    return_value = ERROR;
  }

  return return_value;
}

int CalculatorModel::ParserExpression(const std::string& input_line,
                                      std::string& result) {
  if (CheckAllExpression(input_line) == ERROR) {
    return ERROR;
  }

  int return_value = NO_ERROR;
  std::stack<char> polish_stack;
  size_t position = 0;

  while (position < input_line.size() && return_value == NO_ERROR) {
    if (input_line[position] == ' ') {
      ++position;
    } else {
      return_value = CheckSymbol(position, input_line, result, polish_stack);
    }
  }

  if (return_value == NO_ERROR) {
    PopAllStack(polish_stack, result);
  } else {
    result.clear();
  }

  return return_value;
}

}  // namespace s21
