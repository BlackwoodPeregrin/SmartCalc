#pragma once

#include <array>
#include <cmath>
#include <string>
#include <vector>

namespace s21_SmartCalc {
class ModelCreditCalc {
 public:
  enum { SUM_MOUNTH_PAYMENTS, CREDIT_OVERPAY, TOTAL_PAYOUT };
  std::array<double, 3> calculateAnnuity(const double &creditTerm,
                                         const double &creditAmount,
                                         const double &InterestRate) {
    std::array<double, 3> result;
    double ps = InterestRate / (100 * 12);  // rate in mouth
    result[SUM_MOUNTH_PAYMENTS] =
        creditTerm *
        ((ps * pow(1 + ps, creditAmount)) / (pow(1 + ps, creditAmount) - 1));

    result[TOTAL_PAYOUT] = result[SUM_MOUNTH_PAYMENTS] * creditAmount;
    result[CREDIT_OVERPAY] = result[TOTAL_PAYOUT] - creditTerm;
    return result;
  }

  std::array<std::vector<double>, 5> calculateDiff(const double &creditTerm,
                                                   const double &creditAmount,
                                                   const double &InterestRate) {
    std::array<std::vector<double>, 5> result;
    std::vector<double> main_answer(3);
    std::vector<double> graphPayments((int)creditAmount);
    std::vector<double> procents((int)creditAmount);
    std::vector<double> credit_body((int)creditAmount);
    std::vector<double> remainder((int)creditAmount);

    double PV = creditTerm / creditAmount;
    double sumV = 0;
    double rate = InterestRate / (100 * 12);
    for (int i = 0; i < (int)creditAmount; ++i) {
      double V = PV + ((creditTerm - PV * i) * rate);
      graphPayments[i] = V;
      procents[i] = (creditTerm - PV * i) * rate;
      credit_body[i] = PV;
      remainder[i] = creditTerm - PV * (i + 1);
      sumV += V;
    }
    main_answer[SUM_MOUNTH_PAYMENTS] = sumV / creditAmount;
    main_answer[TOTAL_PAYOUT] = sumV;
    main_answer[CREDIT_OVERPAY] = sumV - creditTerm;

    result[0] = main_answer;
    result[1] = graphPayments;
    result[2] = procents;
    result[3] = credit_body;
    result[4] = remainder;
    return result;
  }
};
}  // namespace s21_SmartCalc
