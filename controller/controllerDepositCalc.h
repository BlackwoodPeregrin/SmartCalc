#pragma once

#include "../model/modelDepositCalc.h"

namespace s21_SmartCalc {
class ControllerDepositCalc {
 public:
  ControllerDepositCalc() {}

  std::array<double, 8> get_result_model(const size_t &period_replenishment,
                                         const size_t &period_withdrawal,
                                         const size_t &period_capitalization,
                                         const size_t &term_deposit,
                                         const std::array<double, 6> &value) {
    return _connectModel.deposit_calculator(
        period_replenishment, period_withdrawal, period_capitalization,
        term_deposit, value);
  }

 private:
  s21_SmartCalc::ModelDepositCalc _connectModel;
};
}  // namespace s21_SmartCalc
