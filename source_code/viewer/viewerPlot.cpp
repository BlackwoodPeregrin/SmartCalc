#include "viewerPlot.h"

#include <QMessageBox>
#include <QVector>
#include <string>

#include "ui_plot.h"

namespace s21_SmartCalc {

Plot::Plot(const QString &formule)
    : _ui(new Ui::Plot),
      _connectController(new ControllerCalc),
      _strFormule(formule) {
  _ui->setupUi(this);
  _ui->textEdit_formule->setText(_strFormule);
  _SetOptions();
  _connectController->set_model_polishNot(_strFormule.toStdString());
}

Plot::~Plot() {
  delete _ui;
  delete _connectController;
}

void Plot::_SetOptions() {
  _ui->widgetPlot->xAxis->setRange(-10, 10);  // defoult xAxis range
  _ui->widgetPlot->yAxis->setRange(-10, 10);  // defoult yAxis range
  _ui->widgetPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
  _ui->widgetPlot->xAxis->setTickLabelColor(Qt::white);
  _ui->widgetPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
  _ui->widgetPlot->yAxis->setTickLabelColor(Qt::white);
  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(80, 80, 80));
  plotGradient.setColorAt(1, QColor(50, 50, 50));
  _ui->widgetPlot->setBackground(plotGradient);
  QLinearGradient axisRectGradient;
  axisRectGradient.setStart(0, 0);
  axisRectGradient.setFinalStop(0, 350);
  axisRectGradient.setColorAt(0, QColor(80, 80, 80));
  axisRectGradient.setColorAt(1, QColor(20, 20, 20));
  _ui->widgetPlot->axisRect()->setBackground(axisRectGradient);
  _ui->widgetPlot->setInteraction(QCP::iRangeZoom, true);
  _ui->widgetPlot->setInteraction(QCP::iRangeDrag, true);
}

void Plot::on_but_graph_clicked() {
  double xBegin = _ui->doubleSpinBox_x_min->value();
  double xEnd = _ui->doubleSpinBox_x_max->value();
  double yBegin = _ui->doubleSpinBox_y_min->value();
  double yEnd = _ui->doubleSpinBox_y_max->value();
  double step = 0.1;
  if (xBegin >= xEnd) {
    QMessageBox::warning(this, "Warning",
                         "Incorrect values, x_min must be less then x_max!");
  } else if (yBegin >= yEnd) {
    QMessageBox::warning(this, "Warning",
                         "Incorrect values, y_min must be less then y_max!");
  } else {
    _ui->widgetPlot->xAxis->setRange(xBegin, xEnd);
    _ui->widgetPlot->yAxis->setRange(yBegin, yEnd);
    QVector<double> x_values, y_values;
    for (double X = xBegin; X <= xEnd;) {
      std::string Y = _connectController->get_result_model_with_X(X);
      if (Y.find("Error") == std::string::npos) {
        x_values.push_back(X);
        y_values.push_back(QString::fromLocal8Bit(Y.c_str()).toDouble());
        X += step;
      } else {
        X += step;
        continue;
      }
    }
    _ui->widgetPlot->addGraph();
    _ui->widgetPlot->graph(0)->addData(x_values, y_values);
    _ui->widgetPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    _ui->widgetPlot->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssDiamond, 10));
    _ui->widgetPlot->graph(0)->setPen(QPen(Qt::white));
    _ui->widgetPlot->replot();
    _ui->label_complete->setText("Graph complete!");
  }
}

}  // namespace s21_SmartCalc
