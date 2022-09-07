#pragma once

#include <QDialog>

#include "../controller/controllerCalc.h"

namespace Ui {
class Plot;
}

namespace s21_SmartCalc {
class Plot : public QDialog {
  Q_OBJECT

 public:
  explicit Plot(const QString &formule);
  ~Plot();

 private slots:
  void on_but_graph_clicked();

 private:
  void _SetOptions();
  Ui::Plot *_ui;
  ControllerCalc *_connectController;
  QString _strFormule;
};
}  // namespace s21_SmartCalc
