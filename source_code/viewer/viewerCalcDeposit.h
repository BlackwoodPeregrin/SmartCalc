#pragma once

#include <QDialog>
#include <QKeyEvent>
#include <QMainWindow>
#include <array>

#include "../controller/controllerDepositCalc.h"
#include "ui_deposit_CalcResult.h"

namespace Ui {
class ViewerCalcDeposit;
}

namespace s21_SmartCalc {
class ViewerCalcDeposit : public QMainWindow {
  Q_OBJECT

 public:
  explicit ViewerCalcDeposit(QWidget *parent = nullptr);
  ~ViewerCalcDeposit();

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
  void _SetOptions();
  void _GenerationDataBuf(std::array<double, N> &data);
  void _GenerationResultDialog(const std::array<double, 8> &result_data);
  void keyPressEvent(QKeyEvent *key) {
    if (key->key() == Qt::Key_Escape) {
      close();
    } else if (key->key() == 16777220) {  // for mac Enter
      on_but_calculate_clicked();
    } else if (key->key() == Qt::Key_Enter) {
      on_but_calculate_clicked();
    }
  }

 private slots:
  void on_but_month_clicked();
  void on_but_year_clicked();
  void on_but_add_to_deposit_clicked();
  void on_but_pay_clicked();

  void on_comboBox_deposit_replenishment_currentIndexChanged(int index);
  void on_comboBox_deposit_withdrawal_currentIndexChanged(int index);

  void on_slider_deposit_amount_valueChanged(int value);
  void on_slider_placement_period_valueChanged(int value);

  void on_but_calculate_clicked();

 private:
  class ViewerCalcDepositResult : public QDialog {
   public:
    explicit ViewerCalcDepositResult(QWidget *parent = nullptr)
        : QDialog(parent), _ui(new Ui::Dialog) {
      _ui->setupUi(this);
    }
    ~ViewerCalcDepositResult() { delete _ui; }
    void keyPressEvent(QKeyEvent *key) {
      if (key->key() == Qt::Key_Escape) {
        close();
      }
    }
    Ui::Dialog *_ui;
  };

 private:
  enum { BUT_MONTH, BUT_YEAR, BUT_ADD_TO_DEPOSIT, BUT_PAY };
  enum {
    RES_SUM_DEPOSIT,
    RES_REPLENISHMENT,
    RES_WITHDRAWAL,
    RES_INTEREST_RATE,
    RES_TAXABLE_SUM,
    RES_SUM_TAX,
    RES_INCOME,
    RES_FINAL_SUM_DEPOSIT,
    LEN
  };
  Ui::ViewerCalcDeposit *_ui;
  s21_SmartCalc::ControllerDepositCalc _connectController;
  QString _butStyle;
  QString _butPressedStyle;
  bool _activeBut[4];
};
}  // namespace s21_SmartCalc
