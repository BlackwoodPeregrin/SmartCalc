#pragma once

#include <QKeyEvent>
#include <QLineEdit>
#include <QMainWindow>

#include "../controller/controllerCreditCalc.h"
#include "ui_credit_Calc.h"
#include "ui_credit_CalcResult.h"

namespace s21_SmartCalc {
class ViewerCalcCredit : public QMainWindow {
  Q_OBJECT

 public:
  explicit ViewerCalcCredit(QWidget *parent = nullptr);
  ~ViewerCalcCredit();
  void clearFields();

 private slots:
  void on_checkBox_years_clicked();
  void on_checkBox_mounths_clicked();
  void on_checkBox_annuity_clicked();
  void on_checkBox_diff_clicked();

  void on_but_clear_last_clicked();
  void on_but_clear_clicked();

  void on_but_0_clicked();
  void on_but_1_clicked();
  void on_but_2_clicked();
  void on_but_3_clicked();
  void on_but_4_clicked();
  void on_but_5_clicked();
  void on_but_6_clicked();
  void on_but_7_clicked();
  void on_but_8_clicked();
  void on_but_9_clicked();
  void on_but_dot_clicked();

  void on_but_calculate_clicked();

 private:
  bool _CheckLineEdit(QString &strOutput, const QString &nameLineEdit);
  QString _HaveErrorsInput();
  void _AddSymbolsToLineEdit(const QString &symbols);
  void _AddSymbols(QLineEdit *lineEdit, const QString &symbols);
  void _EraceLastElement(QLineEdit *lineEdit);
  void on_but_number_clicked();
  void keyPressEvent(QKeyEvent *key);

 private:
  class ViewerCalcCreditResult : public QMainWindow {
   public:
    explicit ViewerCalcCreditResult(QWidget *parent = nullptr)
        : QMainWindow(parent), _ui_res(new Ui::CreditCalcResult) {
      _ui_res->setupUi(this);
      this->setFixedSize(625, 522);
    }
    ~ViewerCalcCreditResult() { delete _ui_res; }
    void keyPressEvent(QKeyEvent *key) {
      if (key->key() == Qt::Key_Escape) {
        close();
      }
    }

    Ui::CreditCalcResult *_ui_res;
  };

 private:
  Ui::CreditCalc *_ui;
  ViewerCalcCreditResult *_viewer_res;
  ControllerCreditCalc *_connectController;
  bool _dot;
};
}  // namespace s21_SmartCalc
