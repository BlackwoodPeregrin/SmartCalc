#include "viewerCalcDeposit.h"

#include <QMessageBox>

#include "ui_deposit_Calc.h"

namespace s21_SmartCalc {

ViewerCalcDeposit::ViewerCalcDeposit(QWidget *parent)
    : QMainWindow(parent), _ui(new Ui::ViewerCalcDeposit) {
  _ui->setupUi(this);
  _ui->doubleSpinBox_deposit_replenishment->hide();
  _ui->doubleSpinBox_deposit_withdrawal->hide();
  _SetOptions();
}

ViewerCalcDeposit::~ViewerCalcDeposit() { delete _ui; }

void ViewerCalcDeposit::_SetOptions() {
  _butStyle =
      "QPushButton{\n"
      "border-radius: 10px;\n"
      "border: 2px solid rgb(12, 0, 0);\n"
      "font: bold 15px;\n"
      "color: black;\n"
      "background: rgba(175, 48, 173, 110);\n"
      "font-family: \"Comic Sans MS\";\n"
      "}\n"
      "QPushButton:pressed {\n"
      "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
      "                                      stop: 0 #BEBEBE, stop: 1 "
      "#D7D7D7);\n"
      "}\n"
      "QPushButton:hover {\n"
      "border: 2px solid gray;\n"
      "}";
  _butPressedStyle =
      "QPushButton{\n"
      "border-radius: 10px;\n"
      "border: 2px solid rgb(12, 0, 0);\n"
      "font: bold 15px;\n"
      "color: white;\n"
      "background: gray;\n"
      "font-family: \"Comic Sans MS\";\n"
      "}\n"
      "QPushButton:pressed {\n"
      "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
      "                                      stop: 0 #BEBEBE, stop: 1 "
      "#D7D7D7);\n"
      "}\n"
      "QPushButton:hover {\n"
      "border: 2px solid gray;\n"
      "}";
  _activeBut[BUT_MONTH] = true;
  _activeBut[BUT_YEAR] = false;
  _activeBut[BUT_ADD_TO_DEPOSIT] = false;
  _activeBut[BUT_PAY] = true;
}

void ViewerCalcDeposit::on_but_month_clicked() {
  if (_activeBut[BUT_MONTH] == false) {
    _ui->but_month->setStyleSheet(_butPressedStyle);
    _ui->but_year->setStyleSheet(_butStyle);
    _activeBut[BUT_YEAR] = false;
    _activeBut[BUT_MONTH] = true;

    _ui->label_placement_period_2->setText("Specify an integer from 0 to 120");
    _ui->spinBox_placement_period->setMaximum(120);
    _ui->slider_placement_period->setMaximum(120);
  }
}

void ViewerCalcDeposit::on_but_year_clicked() {
  if (_activeBut[BUT_YEAR] == false) {
    _ui->but_year->setStyleSheet(_butPressedStyle);
    _ui->but_month->setStyleSheet(_butStyle);
    _activeBut[BUT_MONTH] = false;
    _activeBut[BUT_YEAR] = true;

    _ui->label_placement_period_2->setText("Specify an integer from 0 to 10");
    _ui->spinBox_placement_period->setMaximum(10);
    _ui->slider_placement_period->setMaximum(10);
  }
}

void ViewerCalcDeposit::on_but_add_to_deposit_clicked() {
  if (_activeBut[BUT_ADD_TO_DEPOSIT] == false) {
    _ui->but_add_to_deposit->setStyleSheet(_butPressedStyle);
    _activeBut[BUT_ADD_TO_DEPOSIT] = true;
    _ui->but_pay->setStyleSheet(_butStyle);
    _activeBut[BUT_PAY] = false;
  }
}

void ViewerCalcDeposit::on_but_pay_clicked() {
  if (_activeBut[BUT_PAY] == false) {
    _ui->but_pay->setStyleSheet(_butPressedStyle);
    _activeBut[BUT_PAY] = true;
    _ui->but_add_to_deposit->setStyleSheet(_butStyle);
    _activeBut[BUT_ADD_TO_DEPOSIT] = false;
  }
}

void ViewerCalcDeposit::on_comboBox_deposit_replenishment_currentIndexChanged(
    int index) {
  if (index == 0) {
    _ui->doubleSpinBox_deposit_replenishment->hide();
  } else {
    _ui->doubleSpinBox_deposit_replenishment->show();
  }
}

void ViewerCalcDeposit::on_comboBox_deposit_withdrawal_currentIndexChanged(
    int index) {
  if (index == 0) {
    _ui->doubleSpinBox_deposit_withdrawal->hide();
  } else {
    _ui->doubleSpinBox_deposit_withdrawal->show();
  }
}

void ViewerCalcDeposit::on_slider_deposit_amount_valueChanged(int value) {
  if (value <= 50) {
    _ui->doubleSpinBox_deposit_amount->setValue(value * 2000);
  } else if (value <= 140) {
    _ui->doubleSpinBox_deposit_amount->setValue((2000 * 50) +
                                                (value - 50) * 10000);
  } else if (value <= 230) {
    _ui->doubleSpinBox_deposit_amount->setValue((2000 * 50) + (10000 * 90) +
                                                (value - 140) * 100000);
  } else if (value <= 320) {
    _ui->doubleSpinBox_deposit_amount->setValue(
        (2000 * 50) + (10000 * 90) + (100000 * 90) + (value - 230) * 1000000);

  } else if (value <= 410) {
    _ui->doubleSpinBox_deposit_amount->setValue((2000 * 50) + (10000 * 90) +
                                                (100000 * 90) + (1000000 * 90) +
                                                (value - 320) * 10000000);
  }
}

void ViewerCalcDeposit::on_slider_placement_period_valueChanged(int value) {
  _ui->spinBox_placement_period->setValue(value);
}

void ViewerCalcDeposit::_GenerationDataBuf(std::array<double, N> &data) {
  data[SUM_DEPOSIT] = _ui->doubleSpinBox_deposit_amount->value();
  data[REPLENISHMENT] = _ui->doubleSpinBox_deposit_replenishment->value();
  data[WITHDRAWAL] = _ui->doubleSpinBox_deposit_withdrawal->value();
  data[INTEREST_RATE] = _ui->doubleSpinBox_interest_rate->value();
  data[CENTRAL_BANK_RATE] = _ui->doubleSpinBox_rate_CB->value();
  data[TAX_RATE] = _ui->doubleSpinBox_rate_tax->value();
}

void ViewerCalcDeposit::_GenerationResultDialog(
    const std::array<double, 8> &result_data) {
  ViewerCalcDepositResult resultDialog;
  char buffer[255];
  std::snprintf(buffer, sizeof(buffer), "%.2lf", result_data[RES_SUM_DEPOSIT]);
  resultDialog._ui->label_sum_deposit->setText(buffer);
  std::snprintf(buffer, sizeof(buffer), "%.2lf",
                result_data[RES_REPLENISHMENT]);
  resultDialog._ui->label_sum_replenishment->setText(buffer);
  std::snprintf(buffer, sizeof(buffer), "%.2lf", result_data[RES_WITHDRAWAL]);
  resultDialog._ui->label_sum_withdrawal->setText(buffer);
  std::snprintf(buffer, sizeof(buffer), "%.2lf",
                result_data[RES_INTEREST_RATE]);
  resultDialog._ui->label_sum_interest_charges->setText(buffer);
  if (result_data[RES_SUM_TAX] == 0) {
    resultDialog._ui->label_hide_taxed->hide();
    resultDialog._ui->label_hide_taxed_sum->hide();
    resultDialog._ui->label_hide_income->hide();
    resultDialog._ui->label_sum_hide_income->hide();
  } else {
    std::snprintf(buffer, sizeof(buffer), "%.2lf",
                  result_data[RES_TAXABLE_SUM]);
    resultDialog._ui->label_hide_taxed_sum->setText(buffer);
    std::snprintf(buffer, sizeof(buffer), "%.2lf", result_data[RES_INCOME]);
    resultDialog._ui->label_sum_hide_income->setText(buffer);
  }
  std::snprintf(buffer, sizeof(buffer), "%.2lf", result_data[RES_SUM_TAX]);
  resultDialog._ui->label_sum_withheld_taxes->setText(buffer);
  std::snprintf(buffer, sizeof(buffer), "%.2lf",
                result_data[RES_FINAL_SUM_DEPOSIT]);
  resultDialog._ui->label_final_sum->setText(buffer);
  QString currency = _ui->comboBox_currency->currentText();
  resultDialog._ui->label_final_sum->setText(
      resultDialog._ui->label_final_sum->text() + " " + currency);
  resultDialog.exec();
}

void ViewerCalcDeposit::on_but_calculate_clicked() {
  if (_ui->doubleSpinBox_deposit_amount->value() == 0.0) {
    QMessageBox::information(this, "Information", "Input, Deposit Amount");
  } else if (_ui->spinBox_placement_period->value() == 0) {
    QMessageBox::information(this, "Information", "Input, Placement Period");
  } else if (_ui->lineEdit->text().isEmpty()) {
    QMessageBox::information(this, "Information", "Input, Start Data");
  } else if (_ui->doubleSpinBox_interest_rate->value() == 0.0) {
    QMessageBox::information(this, "Information", "Input, Interest Rate");
  } else {
    std::array<double, N> data;
    _GenerationDataBuf(data);
    size_t period_replenishment =
        _ui->comboBox_deposit_replenishment->currentIndex();
    size_t period_withdrawal = _ui->comboBox_deposit_withdrawal->currentIndex();
    size_t period_capitalization = 0;
    if (_activeBut[BUT_ADD_TO_DEPOSIT] == true) {
      int index = _ui->comboBox_interest_accrued->currentIndex();
      if (index <= 3) {
        index += 1;
      } else if (index == 4) {
        index = 6;
      } else {
        index = 12;
      }
      period_capitalization = index;
    }
    size_t term_deposit = _activeBut[BUT_MONTH] == true
                              ? _ui->spinBox_placement_period->value()
                              : _ui->spinBox_placement_period->value() * 12;
    std::array<double, 8> result_data = _connectController.get_result_model(
        period_replenishment, period_withdrawal, period_capitalization,
        term_deposit, data);
    _GenerationResultDialog(result_data);
  }
}

}  // namespace s21_SmartCalc
