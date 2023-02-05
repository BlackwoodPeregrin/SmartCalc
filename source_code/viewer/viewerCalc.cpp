#include "viewerCalc.h"

namespace s21_SmartCalc {
/*-----------------------Constructor-----------------------------*/

ViewerCalc::ViewerCalc(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainCalc),
      connectController(new ControllerCalc),
      calcX(new ViewerCalcX),
      calcCredit(new ViewerCalcCredit),
      calcDeposit(new ViewerCalcDeposit),
      _sum_left_brecket(0),
      _sum_right_brecket(0),
      _sum_symbols(0),
      _dot(false),
      SH_LB(new QShortcut(QKeySequence("shift+9"), this)),
      SH_RB(new QShortcut(QKeySequence("shift+0"), this)),
      SH_GRAPH_CALC(new QShortcut(QKeySequence("shift+1"), this)),
      SH_CREDIT_CALC(new QShortcut(QKeySequence("shift+2"), this)),
      SH_DEPOSIT_CALC(new QShortcut(QKeySequence("shift+3"), this)) {
  //
  ui->setupUi(this);
  _Set_ivents();

  QString strStyleSheet(
      "QMessageBox { \
      background-color:#3d3d3d; \
      font-size:26px; \
      font-family:'Comic Sans MS'; \
      }\n"

      "QPushButton {\n"
      "width:\
  90px;\n"
      "height:\
  60px;\n"
      " border-radius:20px;\n"
      "border:3px solid rgb(12, 0, 0);\n"
      "font-size:26px;\n"
      "color:white;\n"
      "font-family:'Comic Sans MS';\n"
      "}\n"

      "QPushButton:hover {\n"
      "border:\
  4px solid gray;\n"
      "color:\
  black;\n"
      "}\n"

      "QPushButton#Gradient_1 {\n"
      "background:rgba(254, 105, 193, 100);\n"
      "}\n"
      "QPushButton#Gradient_1:pressed {\n"
      "background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop"
      ":0#BEBEBE, stop:1#D7D7D7);\n"
      "}\n"

      "QPushButton#Gradient_2 {\n"
      "background:\
  rgba(225, 92, 189, 100);\n"
      "}\n"
      "QPushButton#Gradient_2:pressed {\n"
      "background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, \
                                       stop:0#BEBEBE, stop:1#D7D7D7);\n"
      "}\n"

      "QPushButton#Gradient_3 {\n"
      "background:\
  rgba(210, 73, 182, 110);\n"
      "}\n"
      "QPushButton#Gradient_3:pressed {\n"
      " background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, \
                                       stop:0#BEBEBE, stop:1#D7D7D7);\n"
      "}\n"

      "QPushButton#Gradient_4 {\n"
      "background:\
  rgba(175, 48, 173, 110);\n"
      "}\n"
      "QPushButton#Gradient_4:pressed {\n"
      "  background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, \
                                       stop:0#BEBEBE, stop:1#D7D7D7);\n"
      "}\n"

      "QPushButton#Gradient_5 {\n"
      "background:\
  rgba(139, 23, 167, 110);\n"
      "}\n"
      "QPushButton#Gradient_5:pressed {\n"
      "background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, \
                                       stop:0#BEBEBE, stop:1#D7D7D7);\n"
      "}\n"

      "QPushButton#Gradient_6 {\n"
      "background:\
  rgba(103, 10, 166, 110);\n"
      "}\n"
      "QPushButton#Gradient_6:pressed {\n"
      "background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, \
                                       stop:0#BEBEBE, stop:1#D7D7D7);\n"
      "}\n"

      "QPushButton#Gradient_7 {\n"
      "background:\
  rgba(90, 16, 180, 110);\n"
      "}\n"
      "QPushButton#Gradient_7:pressed {\n"
      "background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, \
                                       stop:0#BEBEBE, stop:1#D7D7D7);\n"
      "}\n"

      "QPushButton#Gradient_8 {\n"
      "background:\
  rgba(80, 16, 183, 110);\n"
      "}\n"
      "QPushButton#Gradient_8:pressed {\n"
      "  background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, \
                                       stop:0#BEBEBE, stop:1#D7D7D7);\n"
      "}\n"

      "QPushButton#Gradient_9 {\n"
      "background:\
  rgba(70, 12, 190, 110);"
      "}\n"
      "QPushButton#Gradient_9:pressed {\n"
      "  background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, \
                                       stop:0#BEBEBE, stop:1#D7D7D7);\n"
      "}\n"

      "QPushButton#Gradient_10 {\n"
      "background:\
  rgba(60, 10, 200, 100);\n"
      "}\n"
      "QPushButton#Gradient_10:pressed {\n"
      "  background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, \
                                       stop:0#BEBEBE, stop:1#D7D7D7);\n"
      "}\n"

      "QPushButton#Gradient_11 {\n"
      "background:\
  rgba(50, 10, 210, 100);\n"
      "}\n"
      "QPushButton#Gradient_11:pressed {\n"
      "background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, \
      stop:0#BEBEBE, stop:1#D7D7D7);\n"
      "}\n"

      "QTextEdit {\n"
      "background-color:black;\n"
      "color:white;\n"
      "font-size:23px;\n"
      "border-radius:10px;\n"
      "font-family:'Comic Sans MS';\n"
      "}\n"

      "QProgressBar {\n"
      "border:2px solid black;\n"
      "border-radius:5px;\n"
      "text-align:center;\n"
      "font-size:15px;\n"
      "font-family:'Comic Sans MS';\n"
      "}\n"

      "QProgressBar::chunk {\n"
      "background-color:rgba(210, 73, 182, 110);\n"
      "width:20px;\n"
      "}\n"

      "QLabel#Label {"
      "border: 2px solid black;\n"
      "background-color: rgba(90, 16, 180, 110);\n"
      "border-radius: 5px;\n"
      "color: white;\n"
      "font-size: 20px;\n"
      "font-family: 'Comic Sans MS;'\n"
      "}\n"

      "QLabel#LabelFormule {\n"
      "    width: 30px;\n"
      "    height: 100px;\n"
      "    background-color: black;\n"
      " color: white;\n"
      "   border-radius: 10px;\n"
      " font-size: 23px;\n"
      "    font-family: 'Comic Sans MS';"
      " margin-left: 3px;\n"
      "}\n"

      "QWidget#centralwidget {\n"
      "     background-color:#3d3d3d;\n"
      "}");
  this->setStyleSheet(strStyleSheet);
}

/*-----------------------Disstructor-----------------------------*/

ViewerCalc::~ViewerCalc() {
  delete ui;
  delete connectController;
  delete calcX;
  delete calcCredit;
  delete calcDeposit;
  delete SH_LB;
  delete SH_RB;
  delete SH_GRAPH_CALC;
  delete SH_CREDIT_CALC;
  delete SH_DEPOSIT_CALC;
}

/*-----------------------Set All events-----------------------------*/

void ViewerCalc::_Set_ivents() {
  /*--for event "(" && ")"---*/
  connect(SH_LB, SIGNAL(activated()), this, SLOT(on_But_L_Brecket_clicked()));
  connect(SH_RB, SIGNAL(activated()), this, SLOT(on_But_R_Brecket_clicked()));
  connect(SH_GRAPH_CALC, SIGNAL(activated()), this,
          SLOT(on_But_Graph_clicked()));
  connect(SH_CREDIT_CALC, SIGNAL(activated()), this,
          SLOT(on_But_Credit_clicked()));
  connect(SH_DEPOSIT_CALC, SIGNAL(activated()), this,
          SLOT(on_But_Deposit_clicked()));
  /*--buttons 0...9--*/
  connect(ui->buttons_num + 0, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Num_clicked()));
  connect(ui->buttons_num + 1, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Num_clicked()));
  connect(ui->buttons_num + 2, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Num_clicked()));
  connect(ui->buttons_num + 3, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Num_clicked()));
  connect(ui->buttons_num + 4, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Num_clicked()));
  connect(ui->buttons_num + 5, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Num_clicked()));
  connect(ui->buttons_num + 6, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Num_clicked()));
  connect(ui->buttons_num + 7, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Num_clicked()));
  connect(ui->buttons_num + 8, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Num_clicked()));
  connect(ui->buttons_num + 9, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Num_clicked()));
  /*--buttons funcs--*/
  connect(ui->but_sin, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Func_clicked()));
  connect(ui->but_cos, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Func_clicked()));
  connect(ui->but_tan, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Func_clicked()));
  connect(ui->but_asin, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Func_clicked()));
  connect(ui->but_acos, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Func_clicked()));
  connect(ui->but_atan, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Func_clicked()));
  connect(ui->but_ln, SIGNAL(clicked()), this, SLOT(on_Buttons_Func_clicked()));
  connect(ui->but_log, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Func_clicked()));
  connect(ui->but_sqrt, SIGNAL(clicked()), this,
          SLOT(on_Buttons_Func_clicked()));
  /*--buttons signs--*/
  connect(ui->but_plus, SIGNAL(clicked()), this, SLOT(on_But_Plus_clicked()));
  connect(ui->but_minus, SIGNAL(clicked()), this, SLOT(on_But_Minus_clicked()));
  connect(ui->but_mult, SIGNAL(clicked()), this, SLOT(on_But_Mult_clicked()));
  connect(ui->but_div, SIGNAL(clicked()), this, SLOT(on_But_Div_clicked()));
  connect(ui->but_mod, SIGNAL(clicked()), this, SLOT(on_But_Mod_clicked()));
  connect(ui->but_pow, SIGNAL(clicked()), this, SLOT(on_But_Pow_clicked()));
  connect(ui->but_l_brecket, SIGNAL(clicked()), this,
          SLOT(on_But_L_Brecket_clicked()));
  connect(ui->but_r_brecket, SIGNAL(clicked()), this,
          SLOT(on_But_R_Brecket_clicked()));
  /*other buttons--*/
  connect(ui->but_dot, SIGNAL(clicked()), this, SLOT(on_But_Dot_clicked()));
  connect(ui->but_equal, SIGNAL(clicked()), this, SLOT(on_But_Equal_clicked()));
  connect(ui->but_x, SIGNAL(clicked()), this, SLOT(on_But_X_clicked()));
  connect(ui->but_credit, SIGNAL(clicked()), this,
          SLOT(on_But_Credit_clicked()));
  connect(ui->but_deposit, SIGNAL(clicked()), this,
          SLOT(on_But_Deposit_clicked()));
  connect(ui->but_graph, SIGNAL(clicked()), this, SLOT(on_But_Graph_clicked()));
  connect(ui->but_clear, SIGNAL(clicked()), this, SLOT(on_But_Clear_clicked()));
  connect(ui->but_clear_last, SIGNAL(clicked()), this,
          SLOT(on_But_Clear_Last_clicked()));
}

/*----------------For keystrokes from the keyboard---------------*/

void ViewerCalc::keyPressEvent(QKeyEvent *key) {
  switch (key->key()) {
    /*press numbers*/
    case Qt::Key_0:
      _Add_num_to_textEdit("0");
      break;
    case Qt::Key_1:
      _Add_num_to_textEdit("1");
      break;
    case Qt::Key_2:
      _Add_num_to_textEdit("2");
      break;
    case Qt::Key_3:
      _Add_num_to_textEdit("3");
      break;
    case Qt::Key_4:
      _Add_num_to_textEdit("4");
      break;
    case Qt::Key_5:
      _Add_num_to_textEdit("5");
      break;
    case Qt::Key_6:
      _Add_num_to_textEdit("6");
      break;
    case Qt::Key_7:
      _Add_num_to_textEdit("7");
      break;
    case Qt::Key_8:
      _Add_num_to_textEdit("8");
      break;
    case Qt::Key_9:
      _Add_num_to_textEdit("9");
      break;
    case '.':
      on_But_Dot_clicked();
      break;
    /*press signs*/
    case Qt::Key_Plus:
      on_But_Plus_clicked();
      break;
    case Qt::Key_Minus:
      on_But_Minus_clicked();
      break;
    case Qt::Key_Asterisk:
      on_But_Mult_clicked();  // mult
      break;
    case Qt::Key_Slash:
      on_But_Div_clicked();  // div
      break;
    case '%':
      on_But_Mod_clicked();  // mod
      break;
    case '^':
      on_But_Pow_clicked();  // pow
      break;
      /*press symbols*/
    case Qt::Key_S:
      _Add_char_to_textEdit("s");
      break;
    case Qt::Key_I:
      _Add_char_to_textEdit("i");
      break;
    case Qt::Key_N:
      _Add_char_to_textEdit("n");
      break;
    case Qt::Key_C:
      _Add_char_to_textEdit("c");
      break;
    case Qt::Key_O:
      _Add_char_to_textEdit("o");
      break;
    case Qt::Key_T:
      _Add_char_to_textEdit("t");
      break;
    case Qt::Key_A:
      _Add_char_to_textEdit("a");
      break;
    case Qt::Key_L:
      _Add_char_to_textEdit("l");
      break;
    case Qt::Key_G:
      _Add_char_to_textEdit("g");
      break;
    case Qt::Key_Q:
      _Add_char_to_textEdit("q");
      break;
    case Qt::Key_R:
      _Add_char_to_textEdit("r");
      break;
    case Qt::Key_X:
      on_But_X_clicked();
      break;
      /*press press functional buttons*/
    case Qt::Key_Backspace:
      on_But_Clear_Last_clicked();
      break;
    case 16777220:  // for mac Enter
      on_But_Equal_clicked();
      break;
    case Qt::Key_Enter:
      on_But_Equal_clicked();
      break;
    case Qt::Key_Escape:
      close();
      break;
    case Qt::Key_Tab:  // TAB for clear TextEdit
      on_But_Clear_clicked();
      break;
  }
}

/*-----------------------Secondary functions-----------------------------*/

bool ViewerCalc::_Is_last_symbol_num() {
  QString textEdit = ui->textEdit_formule->toPlainText();
  if (textEdit.size() != 0) {
    if ((textEdit.back() >= '0' && textEdit.back() <= '9') ||
        textEdit.back() == '.') {
      return true;
    }
  }
  return false;
}

bool ViewerCalc::_Is_last_symbol_sign() {
  QString str = ui->textEdit_formule->toPlainText();
  if (str.size() != 0) {
    if (str.back() == '+' || str.back() == '-' || str.back() == '*' ||
        str.back() == '/' || str.back() == '%' || str.back() == '^') {
      return true;
    }
  }
  return false;
}

bool ViewerCalc::_Is_last_symbol_char() {
  QString str = ui->textEdit_formule->toPlainText();
  if (str.size() != 0) {
    if (str.back() >= 'a' && str.back() <= 'z' && str.back() != 'x') {
      return true;
    }
  }
  return false;
}

void ViewerCalc::_Change_progress_bar() {
  ui->progress_bar->setValue(_sum_symbols);
}

void ViewerCalc::_Change_label_sum_LB() {
  ui->label_sum_l_brecket->setNum((int)_sum_left_brecket);
  _Change_progress_bar();
}

void ViewerCalc::_Change_label_sum_RB() {
  ui->label_sum_r_brecket->setNum((int)_sum_right_brecket);
  _Change_progress_bar();
}

void ViewerCalc::_Change_label_sum_Symbols() {
  ui->label_sum_symbols->setNum((int)_sum_symbols);
  _Change_progress_bar();
}

/*-----------------------Callback funcs-----------------------------*/

void ViewerCalc::on_Buttons_Num_clicked() {
  QPushButton *pButton = (QPushButton *)sender();
  if (pButton != nullptr) {
    _Add_num_to_textEdit(pButton->text());
  }
}

void ViewerCalc::on_Buttons_Func_clicked() {
  QPushButton *pButton = (QPushButton *)sender();
  if (pButton != nullptr) {
    _Add_func_to_textEdit(pButton->text() + "(");
  }
}

void ViewerCalc::on_But_Plus_clicked() {
  QString textEdit = ui->textEdit_formule->toPlainText();
  if (textEdit.size() == 0) {
    _Add_text_to_textEdit("(+");
    ++_sum_left_brecket;
    _sum_symbols += 2;
    _Change_label_sum_LB();
    _Change_label_sum_Symbols();
  } else if (textEdit.back() != '+') {
    if (textEdit.back() == '-') {
      textEdit.back() = '+';
      ui->textEdit_formule->setText(textEdit);
    } else {
      _Add_Plus_Minus_to_textEdit(textEdit, "+");
    }
  }
}

void ViewerCalc::on_But_Minus_clicked() {
  QString textEdit = ui->textEdit_formule->toPlainText();
  if (textEdit.size() == 0) {
    _Add_text_to_textEdit("(-");
    ++_sum_left_brecket;
    _sum_symbols += 2;
    _Change_label_sum_LB();
    _Change_label_sum_Symbols();
  } else {
    if (textEdit.back() == '-') {
      textEdit.back() = '+';
      ui->textEdit_formule->setText(textEdit);
    } else if (textEdit.back() == '+') {
      textEdit.back() = '-';
      ui->textEdit_formule->setText(textEdit);
    } else {
      _Add_Plus_Minus_to_textEdit(textEdit, "-");
    }
  }
}

void ViewerCalc::on_But_Mult_clicked() {
  QString textEdit = ui->textEdit_formule->toPlainText();
  if (textEdit.size() != 0) {
    if (textEdit.back() == '*') {
      textEdit.back() = '^';
      ui->textEdit_formule->setText(textEdit);
    } else {
      _Add_Mult_Div_Mod_Pow_to_textEdit(textEdit, '*');
    }
  }
}

void ViewerCalc::on_But_Div_clicked() {
  QString textEdit = ui->textEdit_formule->toPlainText();
  if (textEdit.size() != 0 && textEdit.back() != '/') {
    _Add_Mult_Div_Mod_Pow_to_textEdit(textEdit, '/');
  }
}

void ViewerCalc::on_But_Mod_clicked() {
  QString textEdit = ui->textEdit_formule->toPlainText();
  if (textEdit.size() != 0 && textEdit.back() != '%') {
    _Add_Mult_Div_Mod_Pow_to_textEdit(textEdit, '%');
  }
}

void ViewerCalc::on_But_Pow_clicked() {
  QString textEdit = ui->textEdit_formule->toPlainText();
  if (textEdit.size() != 0 && textEdit.back() != '^') {
    _Add_Mult_Div_Mod_Pow_to_textEdit(textEdit, '^');
  }
}

void ViewerCalc::on_But_L_Brecket_clicked() {
  QString textEdit = ui->textEdit_formule->toPlainText();
  if (textEdit.size() == 0 || _Is_last_symbol_sign() == true ||
      textEdit.back() == '(' || _Is_last_symbol_char() == true) {
    if (_Add_text_to_textEdit("(") == true) {
      ++_sum_left_brecket;
      ++_sum_symbols;
      _Change_label_sum_LB();
      _Change_label_sum_Symbols();
      _dot = false;
    }
  }
}

void ViewerCalc::on_But_R_Brecket_clicked() {
  QString str = ui->textEdit_formule->toPlainText();
  if (str.size() != 0 && ((str.back() >= '0' && str.back() <= '9') ||
                          str.back() == ')' || str.back() == 'x')) {
    if (_sum_right_brecket != _sum_left_brecket) {
      if (_Add_text_to_textEdit(")") == true) {
        ++_sum_right_brecket;
        ++_sum_symbols;
        _Change_label_sum_RB();
        _Change_label_sum_Symbols();
        _dot = false;
      }
    }
  }
}

void ViewerCalc::on_But_Dot_clicked() {
  QString textEdit = ui->textEdit_formule->toPlainText();
  if (textEdit.size() != 0 && _Is_last_symbol_num() == true && _dot == false) {
    _dot = true;
    ui->textEdit_formule->setText(textEdit + ".");
    ++_sum_symbols;
    _Change_label_sum_Symbols();
  }
}

void ViewerCalc::on_But_X_clicked() {
  if (_Is_last_symbol_char() != true) {
    _Add_char_to_textEdit("x");
  }
}

void ViewerCalc::on_But_Clear_clicked() {
  ui->textEdit_formule->clear();
  ui->label_final_formule->setText("0");
  _sum_symbols = 0;
  _sum_left_brecket = 0;
  _sum_right_brecket = 0;
  _Change_label_sum_Symbols();
  _Change_label_sum_LB();
  _Change_label_sum_RB();
  _dot = false;
}

void ViewerCalc::on_But_Clear_Last_clicked() {
  QString textEdit = ui->textEdit_formule->toPlainText();
  if (textEdit.size() != 0) {
    ui->label_final_formule->setText("0");
    if (textEdit.back() == '(') {
      --_sum_left_brecket;
    } else if (textEdit.back() == ')') {
      --_sum_right_brecket;
    }
    if (textEdit.back() == '.') {
      _dot = false;
    }
    /*--delete last symbol in textEdit--*/
    QString::const_iterator iter = textEdit.cend();
    textEdit.erase(--iter, textEdit.cend());
    ui->textEdit_formule->setText(textEdit);
    /*------------*/
    --_sum_symbols;
    _Change_label_sum_LB();
    _Change_label_sum_RB();
    _Change_label_sum_Symbols();
  }
}

void ViewerCalc::on_But_Equal_clicked() {
  QString textEdit = ui->textEdit_formule->toPlainText();
  if (!textEdit.isEmpty()) {
    std::string result = connectController->_CheckInput(textEdit.toStdString());
    if (result.empty()) {  // errors not found
      if (textEdit.contains('x') == false) {
        textEdit.replace("√", "sqrt");
        result = connectController->get_result_model(textEdit.toStdString());
        if (result.find("Error") == std::string::npos) {
          ui->label_final_formule->setText(
              "= " + QString::fromLocal8Bit(result.c_str()));
        } else {
          ui->label_final_formule->setText(
              QString::fromLocal8Bit(result.c_str()));
        }
      } else {
        calcX->clearFields();
        calcX->setExpression(textEdit);
        calcX->show();
      }
    } else {
      ui->label_final_formule->setText(QString::fromLocal8Bit(result.c_str()));
    }
  } else {
    ui->label_final_formule->setText("0");
  }
}

void ViewerCalc::on_But_Credit_clicked() {
  calcCredit->clearFields();
  calcCredit->show();
  calcCredit->setFocus();
}

void ViewerCalc::on_But_Graph_clicked() {
  QString textEdit = ui->textEdit_formule->toPlainText();
  if (!textEdit.isEmpty()) {
    if (textEdit.contains('x') == false) {
      ui->label_final_formule->setText("Enter an expression with X!");
    } else {
      std::string checkInput =
          connectController->_CheckInput(textEdit.toStdString());
      if (checkInput.empty()) {  // errors not found
        Plot graphCalc(ui->textEdit_formule->toPlainText());
        graphCalc.exec();
      } else {
        ui->label_final_formule->setText(
            QString::fromLocal8Bit(checkInput.c_str()));  // print error string
      }
    }
  } else {
    ui->label_final_formule->setText("Enter an expression with X!");
  }
}

void ViewerCalc::on_But_Deposit_clicked() {
  calcDeposit->show();
  calcDeposit->setFocus();
}

/*-----------------------Add funcs to TextEdit-----------------------------*/

bool ViewerCalc::_Add_text_to_textEdit(const QString &text) {
  if (_sum_symbols + text.size() <= 255) {
    ui->label_final_formule->setText("0");
    ui->textEdit_formule->setText(ui->textEdit_formule->toPlainText() + text);
    return true;
  }
  return false;
}

void ViewerCalc::_Add_func_to_textEdit(const QString &func) {
  QString textEdit = ui->textEdit_formule->toPlainText();
  if (textEdit.size() == 0 || textEdit.back() == '(' ||
      _Is_last_symbol_sign() == true) {
    if (_Add_text_to_textEdit(func) == true) {
      ++_sum_left_brecket;
      _sum_symbols += func.size();
      _Change_label_sum_LB();
      _Change_label_sum_Symbols();
      _dot = false;
    }
  }
}

void ViewerCalc::_Add_char_to_textEdit(const QString &symbol) {
  QString textEdit = ui->textEdit_formule->toPlainText();
  if (textEdit.size() == 0 || textEdit.back() == '(' ||
      _Is_last_symbol_sign() == true || _Is_last_symbol_char()) {
    if (_Add_text_to_textEdit(symbol) == true) {
      ++_sum_symbols;
      _Change_label_sum_Symbols();
      _dot = false;
    }
  }
}

void ViewerCalc::_Add_num_to_textEdit(const QString &num) {
  QString textEdit = ui->textEdit_formule->toPlainText();
  if (textEdit.size() == 0 || _Is_last_symbol_sign() == true ||
      _Is_last_symbol_num() == true || textEdit.back() == '(') {
    if (_Add_text_to_textEdit(num) == true) {
      ++_sum_symbols;
      _Change_label_sum_Symbols();
    }
  }
}

void ViewerCalc::_Add_Plus_Minus_to_textEdit(const QString &str,
                                             const QString &sign) {
  if ((str.back() >= '0' && str.back() <= '9') || str.back() == '(' ||
      str.back() == ')' || str.back() == 'x') {
    if (_Add_text_to_textEdit(sign) == true) {
      ++_sum_symbols;
      _Change_label_sum_Symbols();
      _dot = false;
    }
  } else if (str.back() == '*' || str.back() == '/' || str.back() == '%' ||
             str.back() == '^') {
    if (_Add_text_to_textEdit("(" + sign) == true) {
      ++_sum_left_brecket;
      _sum_symbols += 2;
      _Change_label_sum_LB();
      _Change_label_sum_Symbols();
      _dot = false;
    }
  }
}

void ViewerCalc::_Add_Mult_Div_Mod_Pow_to_textEdit(QString &str, char &&sign) {
  if (str.back() == '*' || str.back() == '/' || str.back() == '%' ||
      str.back() == '^') {
    str.back() = sign;
    ui->textEdit_formule->setText(str);
  } else if ((str.back() >= '0' && str.back() <= '9') || str.back() == ')' ||
             str.back() == 'x') {
    QString tmp(sign);
    if (_Add_text_to_textEdit(tmp) == true) {
      ++_sum_symbols;
      _Change_label_sum_Symbols();
      _dot = false;
    }
  }
}

}  // namespace s21_SmartCalc
