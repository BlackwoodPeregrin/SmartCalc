#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include <QShortcut>

#include "../controller/controllerCalc.h"
#include "ui_main_Calc.h"
#include "viewer/viewerCalcCredit.h"
#include "viewer/viewerCalcX.h"
#include "viewer/viewerPlot.h"
#include "viewer/viewerCalcDeposit.h"

QT_BEGIN_NAMESPACE
namespace s21_SmartCalc {
class ViewerCalc : public QMainWindow {
  Q_OBJECT

 public:
  explicit ViewerCalc(QWidget *parent = nullptr);
  ~ViewerCalc();

 protected:
  void keyPressEvent(QKeyEvent *key);

 protected:
  void _Set_ivents();

 private slots:
  void on_Buttons_Num_clicked();
  void on_Buttons_Func_clicked();

  void on_But_Plus_clicked();
  void on_But_Minus_clicked();
  void on_But_Mult_clicked();
  void on_But_Div_clicked();
  void on_But_Mod_clicked();
  void on_But_Pow_clicked();
  void on_But_L_Brecket_clicked();
  void on_But_R_Brecket_clicked();
  void on_But_Dot_clicked();
  void on_But_X_clicked();

  void on_But_Clear_clicked();
  void on_But_Clear_Last_clicked();

  void on_But_Equal_clicked();
  void on_But_Credit_clicked();
  void on_But_Graph_clicked();
  void on_But_Deposit_clicked();

 private:
  void _Change_progress_bar();
  void _Change_label_sum_LB();
  void _Change_label_sum_RB();
  void _Change_label_sum_Symbols();

  bool _Is_last_symbol_sign();
  bool _Is_last_symbol_num();
  bool _Is_last_symbol_char();

  bool _Add_text_to_textEdit(const QString &text);
  void _Add_num_to_textEdit(const QString &num);
  void _Add_func_to_textEdit(const QString &func);
  void _Add_char_to_textEdit(const QString &symbol);

  void _Add_Plus_Minus_to_textEdit(const QString &str, const QString &sign);
  void _Add_Mult_Div_Mod_Pow_to_textEdit(QString &str, char &&sign);

 private:
  Ui::MainCalc *ui;
  ControllerCalc *connectController;
  ViewerCalcX *calcX;
  ViewerCalcCredit *calcCredit;
  ViewerCalcDeposit *calcDeposit;
  size_t _sum_left_brecket;
  size_t _sum_right_brecket;
  size_t _sum_symbols;
  bool _dot;
  QShortcut *SH_LB;
  QShortcut *SH_RB;
  QShortcut *SH_GRAPH_CALC;
  QShortcut *SH_CREDIT_CALC;
  QShortcut *SH_DEPOSIT_CALC;
};
}  // namespace s21_SmartCalc

QT_END_NAMESPACE
