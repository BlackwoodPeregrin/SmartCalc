#pragma once

#include <iostream>
#include <array>

namespace s21_SmartCalc {
class ModelDepositCalc {
 public:
  ModelDepositCalc() {}

 private:
  enum {
    SUM_DEPOSIT,
    REPLENISHMENT,
    WITHDRAWAL,
    INTEREST_RATE,
    CENTRAL_BANK_RATE,
    TAX_RATE,
    N  // summary elements in enam
  };

  std::array<double, N> calculate_deposit(const size_t &period_replenishment,
                                          const size_t &period_withdrawal,
                                          const size_t &period_capitalization,
                                          const size_t &term_deposit,
                                          const std::array<double, N> &value) {
    double sum_deposit = value[SUM_DEPOSIT];
    double interest = value[INTEREST_RATE] / (100 * 12);
    double sum_replenishment = 0.0;
    double sum_withdrawal = 0.0;
    double res_interest = 0.0;
    double period_rep = period_replenishment;
    double period_wi = period_withdrawal;
    double period_cap = period_capitalization;
    double tmp_sum_interest = 0.0;
    for (size_t i = 1; i <= term_deposit; ++i) {
      res_interest += interest * (sum_deposit + sum_replenishment);
      if (period_capitalization != 0) {
        tmp_sum_interest += interest * (sum_deposit + sum_replenishment);
        period_cap -= 1;
        if (period_cap == 0) {
          sum_deposit += tmp_sum_interest;
          period_cap = period_capitalization;
          tmp_sum_interest = 0.0;
        }
      }
      period_rep -= 1;
      if (period_rep == 0 && i != term_deposit) {
        sum_replenishment += value[REPLENISHMENT];
        period_rep = period_replenishment;
      }
      period_wi -= 1;
      if (period_wi == 0 && i != term_deposit) {
        sum_deposit -= value[WITHDRAWAL];
        sum_withdrawal += value[WITHDRAWAL];
        period_wi = period_withdrawal;
      }
    }
    std::array<double, N> result;
    result[SUM_DEPOSIT] = value[SUM_DEPOSIT];
    result[REPLENISHMENT] = sum_replenishment;
    result[WITHDRAWAL] = sum_withdrawal;
    result[INTEREST_RATE] = res_interest;
    return result;
  }

 public:
  std::array<double, 8> deposit_calculator(const size_t &period_replenishment,
                                           const size_t &period_withdrawal,
                                           const size_t &period_capitalization,
                                           const size_t &term_deposit,
                                           const std::array<double, N> &value) {
    std::array<double, N> answer =
        calculate_deposit(period_replenishment, period_withdrawal,
                          period_capitalization, term_deposit, value);

     double CB_rate = value[CENTRAL_BANK_RATE] / 100;
     double tax_rate = value[TAX_RATE] / 100;

    double taxable_sum = ((answer[INTEREST_RATE] / term_deposit) -
                         ((1000000 * CB_rate) / 12.0)) *
                        term_deposit;
    double sum_tax = taxable_sum * tax_rate;

    sum_tax = sum_tax < 0 ? 0.0 : sum_tax;

    double income_after_taxes = answer[INTEREST_RATE] - sum_tax;

    double final_sum_in_deposit = answer[SUM_DEPOSIT] + answer[REPLENISHMENT] +
                                  answer[INTEREST_RATE] - sum_tax;

    return std::array<double, 8>{answer[SUM_DEPOSIT],
                                 answer[REPLENISHMENT],
                                 answer[WITHDRAWAL],
                                 answer[INTEREST_RATE],
                                 taxable_sum,
                                 sum_tax,
                                 income_after_taxes,
                                 final_sum_in_deposit};
  }
};
}  // namespace s21_SmartCalc
