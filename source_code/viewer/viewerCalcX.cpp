#include "viewerCalcX.h"

namespace s21_SmartCalc {

ViewerCalcX::ViewerCalcX(QWidget *parent)
    : QMainWindow(parent),
      _ui(new Ui::XCalc),
      _connectController(new ControllerCalc),
      _sum_symbols(0),
      _dot(false) {
  _ui->setupUi(this);
  this->setFixedSize(361, 492);
}

ViewerCalcX::~ViewerCalcX() {
  delete _ui;
  delete _connectController;
}

void ViewerCalcX::setExpression(QString &expression) {
  _ui->textEdit_formule->setText(expression);
  expression.replace("√", "sqrt");
  _connectController->set_model_polishNot(expression.toStdString());
}

void ViewerCalcX::clearFields() { on_but_clear_clicked(); }

void ViewerCalcX::_AddSymbolsToLineEdit(const QString &symbols) {
  if (_sum_symbols <= 20) {
    _ui->lineEdit_input->setText(_ui->lineEdit_input->text() + symbols);
    ++_sum_symbols;
    _ui->textEdit_result->setText("0");
  }
}

void ViewerCalcX::keyPressEvent(QKeyEvent *key) {
  switch (key->key()) {
      /*press numbers*/
    case Qt::Key_0:
      _AddSymbolsToLineEdit("0");
      break;
    case Qt::Key_1:
      _AddSymbolsToLineEdit("1");
      break;
    case Qt::Key_2:
      _AddSymbolsToLineEdit("2");
      break;
    case Qt::Key_3:
      _AddSymbolsToLineEdit("3");
      break;
    case Qt::Key_4:
      _AddSymbolsToLineEdit("4");
      break;
    case Qt::Key_5:
      _AddSymbolsToLineEdit("5");
      break;
    case Qt::Key_6:
      _AddSymbolsToLineEdit("6");
      break;
    case Qt::Key_7:
      _AddSymbolsToLineEdit("7");
      break;
    case Qt::Key_8:
      _AddSymbolsToLineEdit("8");
      break;
    case Qt::Key_9:
      _AddSymbolsToLineEdit("9");
      break;
    /*press signs*/
    case Qt::Key_Plus:
      on_but_plus_clicked();
      break;
    case Qt::Key_Minus:
      on_but_minus_clicked();
      break;
    /*press other*/
    case Qt::Key_Backspace:
      on_but_clear_last_clicked();
      break;
    case 16777220:  // for mac Enter
      on_but_equal_clicked();
      break;
    case Qt::Key_Enter:
      on_but_equal_clicked();
      break;
    case '.':
      on_but_dot_clicked();
      break;
    case Qt::Key_Escape:
      close();
      break;
    case Qt::Key_Tab:
      on_but_clear_clicked();
      break;
  }
}

void ViewerCalcX::on_but_0_clicked() { _AddSymbolsToLineEdit("0"); }

void ViewerCalcX::on_but_1_clicked() { _AddSymbolsToLineEdit("1"); }

void ViewerCalcX::on_but_2_clicked() { _AddSymbolsToLineEdit("2"); }

void ViewerCalcX::on_but_3_clicked() { _AddSymbolsToLineEdit("3"); }

void ViewerCalcX::on_but_4_clicked() { _AddSymbolsToLineEdit("4"); }

void ViewerCalcX::on_but_5_clicked() { _AddSymbolsToLineEdit("5"); }

void ViewerCalcX::on_but_6_clicked() { _AddSymbolsToLineEdit("6"); }

void ViewerCalcX::on_but_7_clicked() { _AddSymbolsToLineEdit("7"); }

void ViewerCalcX::on_but_8_clicked() { _AddSymbolsToLineEdit("8"); }

void ViewerCalcX::on_but_9_clicked() { _AddSymbolsToLineEdit("9"); }

void ViewerCalcX::on_but_dot_clicked() {
  QString LineEdit = _ui->lineEdit_input->text();
  if (!LineEdit.isEmpty() && _dot == false) {
    _ui->lineEdit_input->setText(LineEdit + ".");
    _dot = true;
  }
}

void ViewerCalcX::on_but_plus_clicked() {
  QString LineEdit = _ui->lineEdit_input->text();
  if (LineEdit.isEmpty()) {
    _AddSymbolsToLineEdit("+");
  } else if (LineEdit.length() == 1 && LineEdit.back() == '-') {
    LineEdit.back() = '+';
    _ui->lineEdit_input->setText(LineEdit);
  }
}

void ViewerCalcX::on_but_minus_clicked() {
  QString LineEdit = _ui->lineEdit_input->text();
  if (LineEdit.isEmpty()) {
    _AddSymbolsToLineEdit("-");
  } else if (LineEdit.length() == 1 && LineEdit.back() == '+') {
    LineEdit.back() = '-';
    _ui->lineEdit_input->setText(LineEdit);
  }
}

void ViewerCalcX::on_but_clear_clicked() {
  _ui->lineEdit_input->clear();
  _ui->textEdit_result->setText("0");
  _sum_symbols = 0;
  _dot = false;
}

void ViewerCalcX::on_but_clear_last_clicked() {
  QString lineEdit = _ui->lineEdit_input->text();
  if (!lineEdit.isEmpty()) {
    _ui->textEdit_result->setText("0");
    if (lineEdit.back() == '.') {
      _dot = false;
    }
    QString::const_iterator iter = lineEdit.cend();
    lineEdit.erase(--iter, lineEdit.cend());
    _ui->lineEdit_input->setText(lineEdit);
    --_sum_symbols;
  }
}

void ViewerCalcX::on_but_equal_clicked() {
  QString number_for_X = _ui->lineEdit_input->text();
  QString res = QString::fromLocal8Bit(
      _connectController->get_result_model_with_X(number_for_X.toDouble())
          .c_str());
  if (res.contains("Error") == false) {  // correct calculate
    _ui->textEdit_result->setText("= " + res);
  } else {
    _ui->textEdit_result->setText(res);
  }
}

}  // namespace s21_SmartCalc
