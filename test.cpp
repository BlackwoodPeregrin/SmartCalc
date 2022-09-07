#include <gtest/gtest.h>

#include <iostream>

#include "model/modelCalc.h"
#include "model/modelCreditCalc.h"
#include "model/modelDepositCalc.h"

TEST(CalcModel, num) {
  std::string str = "10.12345";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = 10.12345;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, plus) {
  std::string str = "1+2";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = 1 + 2;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, minus) {
  std::string str = "1-2";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = 1 - 2;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, div_br) {
  std::string str = "2/(1+1)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = 2 / (1 + 1);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, mul_br) {
  std::string str = "2*(5-2)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = 2 * (5 - 2);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, pow_) {
  std::string str = "2^3+2^2";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = 8 + 4;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, mod_) {
  std::string str = "4%2";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = 0;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, br_br) {
  std::string str = "((((10))))";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = 10;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, sqrt_) {
  std::string str = "sqrt(9)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = 3;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, mod_2) {
  std::string str = "0%5";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = 0;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, log10_1) {
  std::string str = "log(10)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = 1;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, ln_) {
  std::string str = "ln(2.718281828459045)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = 1;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, minus_minus) {
  std::string str = "(-(-(-5)))";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = -5;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, minus_plus) {
  std::string str = "(-(-(+(+5))))";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = 5;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, minus_2) {
  std::string str = "5-10";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = -5;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, mul_2) {
  std::string str = "0*3";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = 0;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, inf_) {
  std::string str = "0^(-1)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = pow(0, -1);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, minus_inf_) {
  std::string str = "ln(0)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = log(0);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, minus_zero_) {
  std::string str = "(-0)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = 0.0;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, sin_1) {
  std::string str = "sin(3.141592653589793/2)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = sin(3.141592653589793 / 2);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, sin_2) {
  std::string str = "sin(0)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = sin(0);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, sin_3) {
  std::string str = "(-sin(3.141592653589793/2))";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = -sin(3.141592653589793 / 2);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, cos_1) {
  std::string str = "cos(3.141592653589793)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = cos(3.141592653589793);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, cos_2) {
  std::string str = "cos(0)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = cos(0.0);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, cos_3) {
  std::string str = "cos(3.141592653589793/2)+10*(-1)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = cos(3.141592653589793 / 2) + 10 * -1;
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, tan_1) {
  std::string str = "tan(0)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = tan(0);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, tan_2) {
  std::string str = "(-tan(3.141592653589793/4))";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = -tan(3.141592653589793 / 4);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, tan_3) {
  std::string str = "tan(3.141592653589793/2)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = tan(3.141592653589793 / 2);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, atan_1) {
  std::string str = "atan(0)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = atan(0);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, asin_1) {
  std::string str = "asin(0)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = asin(0);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, asin_2) {
  std::string str = "asin(-1)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = asin(-1);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, acos_1) {
  std::string str = "acos(0)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = acos(0);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, acos_2) {
  std::string str = "acos(1)";
  s21_SmartCalc::ModelCalc model;
  double rez = model.getResultCalc(str).first;
  double check = acos(1);
  ASSERT_EQ(rez, check);
}

TEST(CalcModel, credit_1) {
  double sum_credit1 = 10000;
  double time_credit1 = 12.0;
  double per1 = 23;
  s21_SmartCalc::ModelCreditCalc model;
  std::array<std::vector<double>, 5> result =
      model.calculateDiff(sum_credit1, time_credit1, per1);
  std::vector<double> my_res = result[0];
  std::array<double, 3> check = {937.15277, 1245.8334, 11245.833};
  ASSERT_FLOAT_EQ(check[0], my_res[0]);
  ASSERT_FLOAT_EQ(check[1], my_res[1]);
  ASSERT_FLOAT_EQ(check[2], my_res[2]);
}

TEST(CalcModel, credit_2) {
  double sum_credit1 = 10000;
  double time_credit1 = 12.0;
  double per1 = 23;
  s21_SmartCalc::ModelCreditCalc model;
  std::array<double, 3> my_res =
      model.calculateAnnuity(sum_credit1, time_credit1, per1);
  std::array<double, 3> check = {940.76318, 1289.1586, 11289.158};
  ASSERT_FLOAT_EQ(check[0], my_res[0]);
  ASSERT_FLOAT_EQ(check[1], my_res[1]);
  ASSERT_FLOAT_EQ(check[2], my_res[2]);
}

TEST(CalcModel, deposit_1) {
  double sum_deposit = 1000000;
  double rep = 10000;
  double wi = 0;
  double interest = 12;
  double cb_rate = 11;
  double tax_rate = 13;
  std::array<double, 6> value{sum_deposit, rep,     wi,
                              interest,    cb_rate, tax_rate};
  s21_SmartCalc::ModelDepositCalc model;
  std::array<double, 8> result = model.deposit_calculator(1, 0, 1, 12, value);
  std::array<double, 8> orig_result{1000000,  110000,  0,         133650.06,
                                    23650.06, 3074.5078, 130575.55, 1240575.55};

  ASSERT_FLOAT_EQ(orig_result[0], result[0]);
  ASSERT_FLOAT_EQ(orig_result[1], result[1]);
  ASSERT_FLOAT_EQ(orig_result[2], result[2]);
  ASSERT_FLOAT_EQ(orig_result[3], result[3]);
  ASSERT_FLOAT_EQ(orig_result[4], result[4]);
  ASSERT_FLOAT_EQ(orig_result[5], result[5]);
  ASSERT_FLOAT_EQ(orig_result[6], result[6]);
  ASSERT_FLOAT_EQ(orig_result[7], result[7]);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
