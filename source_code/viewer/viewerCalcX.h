#pragma once

#include <QKeyEvent>
#include <QMainWindow>

#include "../controller/controllerCalc.h"
#include "ui_x_Calc.h"

namespace s21_SmartCalc {
class ViewerCalcX : public QMainWindow {
  Q_OBJECT

 public:
  explicit ViewerCalcX(QWidget *parent = nullptr);
  ~ViewerCalcX();
  void setExpression(QString &expression);
  void clearFields();

 private:
  void _AddSymbolsToLineEdit(const QString &symbols);
  void keyPressEvent(QKeyEvent *key);

 private slots:

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

  void on_but_plus_clicked();
  void on_but_minus_clicked();

  void on_but_clear_last_clicked();
  void on_but_clear_clicked();

  void on_but_equal_clicked();

 private:
  Ui::XCalc *_ui;
  ControllerCalc *_connectController;
  size_t _sum_symbols;
  bool _dot;
};
}  // namespace s21_SmartCalc
