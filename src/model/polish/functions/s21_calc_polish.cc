#include "../s21_calculator_model.h"

namespace s21 {

void CalculatorModel::StringToDouble(const std::string& polish_notation,
                                     size_t& position,
                                     std::stack<long double>& numbers) {
  std::locale::global(std::locale::classic());
  size_t processed_length = 0;
  long double number =
      std::stold(polish_notation.substr(position), &processed_length);
  position += processed_length;

  if (polish_notation[position] != ' ') {
    if (polish_notation[position] == '-')
      number *= -1;
    ++position;
  }

  numbers.push(number);
}

int CalculatorModel::ArithmeticOperations(const std::string& polish_notation,
                                          size_t& position,
                                          std::stack<long double>& numbers) {
  if (numbers.size() < 2) {
    return ERROR;
  }

  int return_value = NO_ERROR;
  char symbol = polish_notation[position];

  long double second_number = numbers.top();
  numbers.pop();
  long double first_number = numbers.top();
  numbers.pop();

  long double result_number = 0;

  if (symbol == '+') {
    result_number = first_number + second_number;
  } else if (symbol == '-') {
    result_number = first_number - second_number;
  } else if (symbol == '*') {
    result_number = first_number * second_number;
  } else if (symbol == '^') {
    result_number = std::pow(first_number, second_number);
  } else if (symbol == '/') {
    if (second_number != 0) {
      result_number = first_number / second_number;
    } else {
      return_value = ERROR;
    }
  }

  if (return_value == NO_ERROR) {
    numbers.push(result_number);
    ++position;
  }
  return return_value;
}

int CalculatorModel::CalculationFunctions(const std::string& polish_notation,
                                          size_t& position,
                                          std::stack<long double>& numbers) {
  if (numbers.empty()) {
    return ERROR;
  }

  int return_value = NO_ERROR;
  char symbol = polish_notation[position];

  long double first_number = numbers.top();
  numbers.pop();

  long double result_number = 0;

  switch (symbol) {
    case 'c':
      result_number = std::cos(first_number);
      break;
    case 's':
      result_number = std::sin(first_number);
      break;
    case 't':
      result_number = std::tan(first_number);
      break;
    case 'a':
      result_number = std::acos(first_number);
      break;
    case 'b':
      result_number = std::asin(first_number);
      break;
    case 'n':
      result_number = std::atan(first_number);
      break;
    case 'q':
      result_number = std::sqrt(first_number);
      break;
    case 'l':
      result_number = std::log10(first_number);
      break;
    case 'o':
      result_number = std::log(first_number);
      break;
    case 'm':
      if (numbers.empty() || first_number == 0) {
        return_value = ERROR;
      } else {
        long double second_number = numbers.top();
        numbers.pop();

        result_number = std::fmod(second_number, first_number);
      }
      break;
  }

  if (return_value == NO_ERROR) {
    numbers.push(result_number);
    ++position;
  }

  return return_value;
}

int CalculatorModel::StringProcessing(const std::string& polish_notation,
                                      size_t& position,
                                      std::stack<long double>& numbers,
                                      const long double x) {
  int return_value = NO_ERROR;
  char symbol = polish_notation[position];

  if (IsNumber(symbol)) {
    StringToDouble(polish_notation, position, numbers);
  } else if (IsOperator(symbol)) {
    return_value = ArithmeticOperations(polish_notation, position, numbers);
  } else if (IsFunction(polish_notation, position)) {
    return_value = CalculationFunctions(polish_notation, position, numbers);
  } else if (symbol == 'x') {
    long double temp = x;
    ++position;

    if (polish_notation[position] != ' ') {
      if (polish_notation[position] == '-') {
        temp *= -1;
      }
      ++position;
    }

    numbers.push(temp);
  } else {
    return_value = ERROR;
  }

  return return_value;
}

int CalculatorModel::PolishSolution(const std::string& polish_notation,
                                    long double& result, const long double x) {
  int return_value = NO_ERROR;

  std::stack<long double> numbers;
  size_t position = 0;

  while (position < polish_notation.size() && return_value == NO_ERROR) {
    if (polish_notation[position] == ' ') {
      ++position;
    } else {
      return_value = StringProcessing(polish_notation, position, numbers, x);
    }
  }

  if (numbers.size() > 1) {
    return_value = ERROR;
  }

  if (return_value == NO_ERROR) {
    result = numbers.top();
  }

  return return_value;
}

}  // namespace s21
