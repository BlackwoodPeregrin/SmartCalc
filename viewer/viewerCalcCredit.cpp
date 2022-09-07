#include "viewerCalcCredit.h"

#include <QMessageBox>
#include <QStandardItemModel>
#include <iostream>

namespace s21_SmartCalc {

ViewerCalcCredit::ViewerCalcCredit(QWidget *parent)
    : QMainWindow(parent),
      _ui(new Ui::CreditCalc),
      _viewer_res(new ViewerCalcCreditResult),
      _connectController(new ControllerCreditCalc),
      _dot(false) {
  _ui->setupUi(this);
  this->setFixedSize(654, 594);
}

ViewerCalcCredit::~ViewerCalcCredit() {
  delete _ui;
  delete _viewer_res;
  delete _connectController;
}

void ViewerCalcCredit::clearFields() { on_but_clear_clicked(); }

void ViewerCalcCredit::keyPressEvent(QKeyEvent *key) {
  switch (key->key()) {
    case Qt::Key_Escape:
      close();
      break;
    case 16777220:  // pressed enter
      on_but_calculate_clicked();
      break;
    case Qt::Key_Enter:
      on_but_calculate_clicked();
      break;
  }
}

void ViewerCalcCredit::on_checkBox_years_clicked() {
  if (_ui->checkBox_mounths->isChecked()) {
    _ui->checkBox_mounths->setChecked(false);
  }
  _ui->checkBox_years->setChecked(true);
}

void ViewerCalcCredit::on_checkBox_mounths_clicked() {
  if (_ui->checkBox_years->isChecked()) {
    _ui->checkBox_years->setChecked(false);
  }
  _ui->checkBox_mounths->setChecked(true);
}

void ViewerCalcCredit::on_checkBox_annuity_clicked() {
  if (_ui->checkBox_diff->isChecked()) {
    _ui->checkBox_diff->setChecked(false);
  }
  _ui->checkBox_annuity->setChecked(true);
}

void ViewerCalcCredit::on_checkBox_diff_clicked() {
  if (_ui->checkBox_annuity->isChecked()) {
    _ui->checkBox_annuity->setChecked(false);
  }
  _ui->checkBox_diff->setChecked(true);
}

void ViewerCalcCredit::_EraceLastElement(QLineEdit *lineEdit) {
  QString text = lineEdit->text();
  qsizetype positionCursor = lineEdit->cursorPosition();
  if (positionCursor != 0) {
    if (text[positionCursor - 1] == '.') {
      _dot = false;
    }
    QString::const_iterator first;
    QString::const_iterator last;
    if (positionCursor == 1) {
      first = text.cbegin();
      last = (first + 1);
    } else {
      first = text.cbegin();
      for (qsizetype i = 0; i < positionCursor - 2; ++i) {
        ++first;
      }
      ++first;
      last = (first + 1);
    }
    text.erase(first, last);
    lineEdit->setText(text);
    lineEdit->setCursorPosition(--positionCursor);
  }
}

void ViewerCalcCredit::on_but_clear_last_clicked() {
  if (_ui->lineEdit_cretidTerm->hasFocus()) {
    _EraceLastElement(_ui->lineEdit_cretidTerm);
  } else if (_ui->lineEdit_cretidRate->hasFocus()) {
    _EraceLastElement(_ui->lineEdit_cretidRate);
  } else if (_ui->lineEdit_cretidAmount->hasFocus()) {
    _EraceLastElement(_ui->lineEdit_cretidAmount);
  }
}

void ViewerCalcCredit::on_but_clear_clicked() {
  _ui->lineEdit_cretidAmount->clear();
  _ui->lineEdit_cretidRate->clear();
  _ui->lineEdit_cretidTerm->clear();
  _ui->checkBox_years->setChecked(false);
  _ui->checkBox_mounths->setChecked(false);
  _ui->checkBox_annuity->setChecked(false);
  _ui->checkBox_diff->setChecked(false);
  _dot = false;
}

void ViewerCalcCredit::_AddSymbols(QLineEdit *lineEdit,
                                   const QString &symbols) {
  qsizetype positionCursor = lineEdit->cursorPosition();
  QString text = lineEdit->text();
  text.insert(positionCursor, symbols);
  lineEdit->setText(text);
  positionCursor += symbols.length();
  lineEdit->setCursorPosition(positionCursor);
}

void ViewerCalcCredit::_AddSymbolsToLineEdit(const QString &symbols) {
  if (_ui->lineEdit_cretidTerm->hasFocus()) {
    _AddSymbols(_ui->lineEdit_cretidTerm, symbols);
  } else if (_ui->lineEdit_cretidRate->hasFocus()) {
    _AddSymbols(_ui->lineEdit_cretidRate, symbols);
  } else if (_ui->lineEdit_cretidAmount->hasFocus()) {
    _AddSymbols(_ui->lineEdit_cretidAmount, symbols);
  }
}

void ViewerCalcCredit::on_but_number_clicked() {
  QPushButton *button = (QPushButton *)sender();
  _AddSymbolsToLineEdit(button->text());
}

void ViewerCalcCredit::on_but_0_clicked() { on_but_number_clicked(); }

void ViewerCalcCredit::on_but_1_clicked() { on_but_number_clicked(); }

void ViewerCalcCredit::on_but_2_clicked() { on_but_number_clicked(); }

void ViewerCalcCredit::on_but_3_clicked() { on_but_number_clicked(); }

void ViewerCalcCredit::on_but_4_clicked() { on_but_number_clicked(); }

void ViewerCalcCredit::on_but_5_clicked() { on_but_number_clicked(); }

void ViewerCalcCredit::on_but_6_clicked() { on_but_number_clicked(); }

void ViewerCalcCredit::on_but_7_clicked() { on_but_number_clicked(); }

void ViewerCalcCredit::on_but_8_clicked() { on_but_number_clicked(); }

void ViewerCalcCredit::on_but_9_clicked() { on_but_number_clicked(); }

void ViewerCalcCredit::on_but_dot_clicked() {
  if (_dot == false) {
    QLineEdit *current;
    if (_ui->lineEdit_cretidTerm->hasFocus()) {
      current = _ui->lineEdit_cretidTerm;
    } else if (_ui->lineEdit_cretidRate->hasFocus()) {
      current = _ui->lineEdit_cretidRate;
    } else {
      current = _ui->lineEdit_cretidAmount;
    }
    if (current->cursorPosition() == 0) {
      current->setText("0.");
    } else {
      _AddSymbols(current, ".");
    }
    _dot = true;
  }
}

bool ViewerCalcCredit::_CheckLineEdit(QString &strOutput,
                                      const QString &nameLineEdit) {
  qsizetype sumDot = 0;
  for (qsizetype i = 0; i < strOutput.length(); ++i) {
    if ((strOutput[i] < '0' || strOutput[i] > '9') && strOutput[i] != '.') {
      QChar error_symbol = strOutput[i];
      strOutput = "Error, incorrect symbol in field " + nameLineEdit + " - '";
      strOutput.push_back(error_symbol);
      strOutput.push_back("'");
      return false;
    }
    if (strOutput[i] == '.') {
      ++sumDot;
    }
  }
  if (nameLineEdit == "Credit Amount") {
    if (sumDot != 0) {
      strOutput = "Error, field Credit Amount, must be integer";
      return false;
    }
  } else {
    if (sumDot > 1) {
      strOutput.setNum(sumDot);
      strOutput =
          "Error, in field " + nameLineEdit + ", summary dot is " + strOutput;
      return false;
    }
  }
  return true;
}

QString ViewerCalcCredit::_HaveErrorsInput() {
  QString resultCheck = _ui->lineEdit_cretidTerm->text();
  if (!resultCheck.isEmpty()) {
    if (_CheckLineEdit(resultCheck, "Credit Term") == false) {
      return resultCheck;
    }
  } else {
    return "Error, Credit Term field is empty!";
  }

  resultCheck = _ui->lineEdit_cretidAmount->text();
  if (!resultCheck.isEmpty()) {
    if (_CheckLineEdit(resultCheck, "Credit Amount") == false) {
      return resultCheck;
    }
  } else {
    return "Error, Credit Amount field is empty!";
  }

  resultCheck = _ui->lineEdit_cretidRate->text();
  if (!resultCheck.isEmpty()) {
    if (_CheckLineEdit(resultCheck, "Interest Rate") == false) {
      return resultCheck;
    }
  } else {
    return "Error, Interest Rate field is empty!";
  }
  resultCheck.clear();
  return resultCheck;
}

void ViewerCalcCredit::on_but_calculate_clicked() {
  QString error_str = _HaveErrorsInput();
  if (error_str.isEmpty()) {  // haven't errors
    if (_ui->checkBox_mounths->isChecked() == false &&
        _ui->checkBox_years->isChecked() == false) {
      QMessageBox::warning(this, "Information",
                           "Choose Amount: mouths or years!");
    } else if (_ui->checkBox_annuity->isChecked() == false &&
               _ui->checkBox_diff->isChecked() == false) {
      QMessageBox::warning(
          this, "Information",
          "Choose the type of Payments: Annuity or Differentiated!");
    } else {
      std::array<double, 3> parametrs_input;
      parametrs_input[0] = _ui->lineEdit_cretidTerm->text().toDouble();
      parametrs_input[1] = _ui->lineEdit_cretidAmount->text().toDouble();
      parametrs_input[2] = _ui->lineEdit_cretidRate->text().toDouble();
      if (_ui->checkBox_years->isChecked() == true) {
        parametrs_input[1] *= 12;
      }
      if (parametrs_input[1] > 1200) {
        QMessageBox::warning(this, "Information", "Incorrect input Amount!");
      } else {
        /*--заполнение в таблице выплат количества строк--*/
        QStandardItemModel *model =
            new QStandardItemModel((int)parametrs_input[1], 5, this);
        model->setHeaderData(0, Qt::Horizontal, "Mounth");
        model->setHeaderData(1, Qt::Horizontal, "Payment");
        model->setHeaderData(2, Qt::Horizontal, "Procents");
        model->setHeaderData(3, Qt::Horizontal, "Body");
        model->setHeaderData(4, Qt::Horizontal, "Remainder");
        for (int row = 0; row < model->rowCount(); ++row) {
          model->setData(model->index(row, 0), row + 1);
          model->setHeaderData(row, Qt::Vertical, "");
        }
        /*-----------------------------------------------*/
        if (_ui->checkBox_annuity->isChecked() ==
            true) {  //    annuity payments
          std::array<double, 3> parametrs_output =
              _connectController->getCalculateAnnuity(
                  parametrs_input[0], parametrs_input[1], parametrs_input[2]);
          char buffer[255];
          std::snprintf(buffer, sizeof(buffer), "%.2lf", parametrs_output[0]);
          _viewer_res->_ui_res->label_resMP->setText(buffer);
          std::snprintf(buffer, sizeof(buffer), "%.2lf", parametrs_output[1]);
          _viewer_res->_ui_res->label_resOP->setText(buffer);
          std::snprintf(buffer, sizeof(buffer), "%.2lf", parametrs_output[2]);
          _viewer_res->_ui_res->label_resTP->setText(buffer);
          /*--заполнение в таблице выплат ежемесячных платежей--*/
          std::snprintf(buffer, sizeof(buffer), "%.2lf", parametrs_output[0]);
          for (int row = 0; row < model->rowCount(); ++row) {
            model->setData(model->index(row, 1), buffer);
          }
          /*-----------------------------------------------*/
        } else {  // differentiated payments
          std::array<std::vector<double>, 5> parametrs_output =
              _connectController->getCalculateDiff(
                  parametrs_input[0], parametrs_input[1], parametrs_input[2]);
          char buffer[255];
          std::snprintf(buffer, sizeof(buffer), "%.2lf",
                        parametrs_output[0][0]);
          _viewer_res->_ui_res->label_resMP->setText(buffer);
          std::snprintf(buffer, sizeof(buffer), "%.2lf",
                        parametrs_output[0][1]);
          _viewer_res->_ui_res->label_resOP->setText(buffer);
          std::snprintf(buffer, sizeof(buffer), "%.2lf",
                        parametrs_output[0][2]);
          _viewer_res->_ui_res->label_resTP->setText(buffer);
          /*--заполнение в таблице выплат ежемесячных платежей--*/
          for (int row = 0; row < model->rowCount(); ++row) {
            for (int column = 1; column < model->columnCount(); ++column) {
              std::snprintf(buffer, sizeof(buffer), "%.2lf",
                            parametrs_output[column][row]);
              model->setData(model->index(row, column), buffer);
            }
          }
          /*-----------------------------------------------*/
        }
        _viewer_res->_ui_res->tableView->setModel(model);
        _viewer_res->_ui_res->tableView->horizontalHeader()->resizeSection(4,
                                                                           120);
        _viewer_res->show();
      }
    }
  } else {
    QMessageBox::critical(this, "Error", error_str);
  }
}

}  // namespace s21_SmartCalc
