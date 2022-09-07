#pragma once

#include <exception>
#include <string>

#include "../model/modelCalc.h"
#include "checkInputError.h"

namespace s21_SmartCalc {
class ControllerCalc {
 public:
  ControllerCalc() {}

  std::string _CheckInput(const std::string &strInput) {
    checkInputError *checkStr = new checkInputError(strInput);
    _result_str = checkStr->check_strInput();
    delete checkStr;
    return _result_str;
  }

  std::string get_result_model(const std::string &strInput) {
    if (_result_str.empty()) {
      std::string strOut;
      try {
        strOut = _connectModel.getResultCalc(strInput).second;
      } catch (const std::exception &e) {
        strOut = "Error";
      }
      return strOut;
    }
    return _result_str;
  }

  std::string get_result_model_with_X(double x_value) {
    if (_result_str.empty()) {
      std::string strOut;
      try {
        strOut = _connectModel.getResultCalcWith_X(x_value).second;
      } catch (const std::exception &e) {
        strOut = "Error";
      }
      return strOut;
    }
    return _result_str;
  }

  void set_model_polishNot(const std::string &strInput) {
    if (_result_str.empty()) {
      _connectModel.installPolishNot(strInput);
    }
  }

 private:
  ModelCalc _connectModel;
  std::string _result_str;
};
}  // namespace s21_SmartCalc
