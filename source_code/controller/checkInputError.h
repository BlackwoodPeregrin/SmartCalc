#pragma once

#include <string>

namespace s21_SmartCalc {
class checkInputError {
 public:
  /*--constructor--*/
  explicit checkInputError(const std::string &strInput)
      : _strInput(strInput), l_brecket(0), r_brecket(0) {}
  /*--------------*/
  std::string check_strInput() {
    for (size_t i = 0; i < _strInput.length(); ++i) {
      if (_strInput[i] >= 'a' && _strInput[i] <= 'z' && _strInput[i] != 'x') {
        std::string func;
        while (_strInput[i] >= 'a' && _strInput[i] <= 'z') {
          func.push_back(_strInput[i]);
          ++i;
        }
        _Check_func(func, i);
      }
      if (_strInput[i] == '(') {
        ++l_brecket;
      } else if (_strInput[i] == ')') {
        ++r_brecket;
      }
    }
    _Check_last_symbol_is_sign();
    _Check_breckets();
    return _strOutput;
  }

 private:
  void _Check_last_symbol_is_sign() {
    if (_strInput[_strInput.length() - 1] == '-' ||
        _strInput[_strInput.length() - 1] == '+' ||
        _strInput[_strInput.length() - 1] == '*' ||
        _strInput[_strInput.length() - 1] == '/' ||
        _strInput[_strInput.length() - 1] == '%' ||
        _strInput[_strInput.length() - 1] == '^') {
      _strOutput = "Error, incomplete expression";
    }
  }
  void _Check_func(const std::string &func, const size_t &index_str) {
    if (_strOutput.empty()) {
      if (_Is_func(func) == false) {
        _strOutput = "Error, function name - '" + func + "' is wrong";
      } else if (_strInput[index_str] != '(') {
        _strOutput = "Error, function - '" + func + "' haven't argument";
      }
    }
  }

  void _Check_breckets() {
    if (l_brecket > r_brecket) {
      _strOutput = "Error, mising " + std::to_string(l_brecket - r_brecket) +
                   " right breckets";
    }
  }

  bool _Is_func(const std::string &func) {
    const std::string functions[9]{"sin",  "cos",  "tan", "acos", "asin",
                                   "atan", "sqrt", "ln",  "log"};
    for (size_t i = 0; i < 9; ++i) {
      if (func == functions[i]) {
        return true;
      }
    }
    return false;
  }

 private:
  std::string _strInput;
  std::string _strOutput;  // output string
  int l_brecket = 0;       //  '('
  int r_brecket = 0;       // ')'
};
}  // namespace s21_SmartCalc
