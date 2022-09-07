#pragma once

#include "../model/modelCreditCalc.h"

namespace s21_SmartCalc {
class ControllerCreditCalc {
 public:
  ControllerCreditCalc() {}

  std::array<double, 3> getCalculateAnnuity(const double &creditTerm,
                                            const double &creditAmount,
                                            const double &InterestRate) {
    return _connectModel.calculateAnnuity(creditTerm, creditAmount,
                                          InterestRate);
  }
  std::array<std::vector<double>, 5> getCalculateDiff(
      const double &creditTerm, const double &creditAmount,
      const double &InterestRate) {
    return _connectModel.calculateDiff(creditTerm, creditAmount, InterestRate);
  }

 private:
  s21_SmartCalc::ModelCreditCalc _connectModel;
};
}  // namespace s21_SmartCalc
