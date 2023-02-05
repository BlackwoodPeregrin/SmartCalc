#include "modelCalc.h"

#include <limits>

namespace s21_SmartCalc {

/*--get result--*/

void ModelCalc::installPolishNot(const std::string &strInput) {
  _Clear();
  _strInput = strInput;
  _Polish_natation();
}

std::pair<double, std::string> ModelCalc::getResultCalc(
    const std::string &strInput) {
  _SmartCalc(strInput);
  return resultCalc;
}

std::pair<double, std::string> ModelCalc::getResultCalcWith_X(
    const double &x_value) {
  resultCalc = {};
  _SmartCalcWith_X(x_value);
  return resultCalc;
}

void ModelCalc::_SmartCalc(const std::string &strInput) {
  installPolishNot(strInput);
  _Calc_result();
}

void ModelCalc::_SmartCalcWith_X(const double &x_value) {
  _Calc_result(x_value);
}

/*--ModelCalc methots--*/

void ModelCalc::_Clear() {
  _queuePolish.clear();
  _stackResult.clear();
  _strInput.clear();
  resultCalc = {};
}

void ModelCalc::_Polish_natation() {
  if (!_strInput.empty()) {
    std::string signs = "+-*/%^()";
    for (size_t i = 0; i < _strInput.size(); ++i) {
      /*--push X--*/
      if (_strInput[i] == 'x') {
        _queuePolish.push(Lexem(X));
        ++i;
      }
      /*--push number to queue--*/
      if (_strInput[i] >= '0' && _strInput[i] <= '9') {
        _IsNumber(i);
      }
      /*--push function to stack--*/
      if (_strInput[i] >= 'a' && _strInput[i] <= 'z') {
        _IsFunc(i);
      }
      /*--push sign to stack--*/
      if (signs.find(_strInput[i]) != std::string::npos) {
        if (_stackResult.empty()) {
          size_t ValueLexem = signs.find(_strInput[i]);
          _stackResult.push(Lexem(SIGN, ValueLexem));
        } else {
          _IsSign(i, signs);
        }
      }
    }
    /*--push operators in stack to queue--*/
    while (!_stackResult.empty()) {
      _queuePolish.push(_stackResult.pop());
    }
  }
}

void ModelCalc::_IsNumber(size_t &index_str) {
  std::string number;
  while ((_strInput[index_str] >= '0' && _strInput[index_str] <= '9') ||
         (_strInput[index_str] == '.')) {
    number.push_back(_strInput[index_str]);
    ++index_str;
  }
  Lexem element(NUMBER, std::stod(number));
  _queuePolish.push(element);
}

void ModelCalc::_IsFunc(size_t &index_str) {
  std::string funcs = "sin|cos|tan|acos|asin|atan|sqrt|ln|log";
  std::string func;
  while (_strInput[index_str] >= 'a' && _strInput[index_str] <= 'z') {
    func.push_back(_strInput[index_str]);
    ++index_str;
  }
  Lexem element(FUNC, funcs.find(func));
  _stackResult.push(element);
}

void ModelCalc::_IsSign(const size_t &index_str, const std::string &signs) {
  Lexem element;
  size_t ValueLexem = signs.find(_strInput[index_str]);
  if (ValueLexem == RIGHT_BRECKET) {
    while (_stackResult.get_top().getValueLexem() != LEFT_BRECKET) {
      _queuePolish.push(_stackResult.pop());
    }
    _stackResult.pop();
  } else {
    if (ValueLexem == PLUS || ValueLexem == MINUS) {
      if (_strInput[index_str - 1] == '(') {
        element.setTypeLexem(UNARY_SIGN);
      } else {
        while (!_stackResult.empty() &&
               _stackResult.get_top().getValueLexem() != LEFT_BRECKET) {
          _queuePolish.push(_stackResult.pop());
        }
      }
    } else if (ValueLexem == MULT || ValueLexem == DIV || ValueLexem == MOD) {
      while (!_stackResult.empty() &&
             ((_stackResult.get_top().getValueLexem() != PLUS &&
               _stackResult.get_top().getValueLexem() != MINUS) ||
              _stackResult.get_top().isUnarySign()) &&
             _stackResult.get_top().getValueLexem() != LEFT_BRECKET) {
        _queuePolish.push(_stackResult.pop());
      }
    } else if (ValueLexem == POW) {
      if (_stackResult.get_top().isUnarySign()) {
        _queuePolish.push(_stackResult.pop());
      }
    }
    if (!element.isUnarySign()) {
      element.setTypeLexem(SIGN);
    }
    element.setValueLexem(ValueLexem);
    _stackResult.push(element);
  }
}

void ModelCalc::_Calc_result(double x_value) {
  _stackResult.clear();
  s21::Queue<Lexem> queue_copy(_queuePolish);
  while (!queue_copy.empty()) {
    Lexem element = queue_copy.pop();
    if (element.isSign()) {
      _CalcSign(element);
    } else if (element.isUnarySign()) {
      _CalcUnarySign(element);
    } else if (element.isFunc()) {
      _CalcFunc(element);
    } else if (element.isX()) {
      element.setTypeLexem(NUMBER);
      element.setValueLexem(x_value);
      _stackResult.push(element);
    } else if (element.isNumber()) {
      _stackResult.push(element);
    }
    if (!resultCalc.second.empty()) {  // was error in calculation
      break;
    }
  }
  if (resultCalc.second.empty()) {  // if haven't error in calculation
    if (_stackResult.size() != 1) {
      throw std::invalid_argument(
          "ERROR, in func _Calc_result(), final stack size is not unit one");
    } else {
      resultCalc.first =
          _stackResult.pop().getValueLexem();  // double value result
      char result_str[255];
      std::snprintf(result_str, sizeof(result_str), "%g", resultCalc.first);
      resultCalc.second = result_str;  // string value result
    }
  }
}

void ModelCalc::_CalcSign(const Lexem &lexem) {
  if (_stackResult.size() < 2) {
    throw std::invalid_argument(
        "ERROR, in func _CalcSign(), size of stack less two");
  }
  double second = _stackResult.pop().getValueLexem();
  double first = _stackResult.pop().getValueLexem();
  int valueLexem = lexem.getValueLexem();
  switch (valueLexem) {
    case PLUS:
      _stackResult.push(Lexem(NUMBER, first + second));
      break;
    case MINUS:
      _stackResult.push(Lexem(NUMBER, first - second));
      break;
    case MULT:
      _stackResult.push(Lexem(NUMBER, first * second));
      break;
    case DIV:
      if (second == 0) {
        resultCalc.first = std::numeric_limits<double>::infinity();
        resultCalc.second =
            "Error, " + std::to_string(first) + " is div by zero";
      } else {
        _stackResult.push(Lexem(NUMBER, first / second));
      }
      break;
    case MOD:
      if (second == 0) {
        resultCalc.first = std::numeric_limits<double>::quiet_NaN();
        resultCalc.second =
            "Error, " + std::to_string(first) + " is mod by zero";
      } else {
        _stackResult.push(Lexem(NUMBER, fmod(first, second)));
      }
      break;
    case POW:
      _stackResult.push(Lexem(NUMBER, pow(first, second)));
      break;
  }
}

void ModelCalc::_CalcUnarySign(const Lexem &lexem) {
  if (_stackResult.size() < 1) {
    throw std::invalid_argument(
        "ERROR, in func _CalcUnarySign(), size of stack less one");
  }
  if (lexem.getValueLexem() == MINUS) {
    double number = _stackResult.pop().getValueLexem() * -1;
    _stackResult.push(Lexem(NUMBER, number));
  }
}

void ModelCalc::_CalcFunc(const Lexem &lexem) {
  if (_stackResult.size() < 1) {
    throw std::invalid_argument(
        "ERROR, in func _CalcFunc(), size of stack less one");
  }
  int valueLexem = lexem.getValueLexem();
  double number = _stackResult.pop().getValueLexem();
  switch (valueLexem) {
    case SIN:
      number = sin(number);
      break;
    case COS:
      number = cos(number);
      break;
    case TAN:
      number = tan(number);
      break;
    case ACOS:
      if (number < -1 || number > 1) {
        resultCalc.first = std::numeric_limits<double>::quiet_NaN();
        resultCalc.second = "Error, arg in acos() equal " +
                            std::to_string(number) +
                            ", arg must be range in [-1;1]";
      } else {
        number = acos(number);
      }
      break;
    case ASIN:
      if (number < -1 || number > 1) {
        resultCalc.first = std::numeric_limits<double>::quiet_NaN();
        resultCalc.second = "Error, arg in asin() equal " +
                            std::to_string(number) +
                            ", arg must be range in [-1;1]";
      } else {
        number = asin(number);
      }
      break;
    case ATAN:
      number = atan(number);
      break;
    case SQRT:
      if (number < 0) {
        resultCalc.first = std::numeric_limits<double>::quiet_NaN();
        resultCalc.second = "Error, arg in sqrt() equal " +
                            std::to_string(number) + ", arg must be positive";
      } else {
        number = sqrt(number);
      }
      break;
    case LN:
      if (number <= 0) {
        resultCalc.first = log(number);
        resultCalc.second = "Error, arg in ln() equal " +
                            std::to_string(number) + ", arg must be positive";
      } else {
        number = log(number);
      }
      break;
    case LOG:
      if (number <= 0) {
        resultCalc.first = log10(number);
        resultCalc.second = "Error, arg in log() equal " +
                            std::to_string(number) + ", arg must be positive";
      } else {
        number = log10(number);
      }
      break;
  }
  _stackResult.push(Lexem(NUMBER, number));
}

}  // namespace s21_SmartCalc
