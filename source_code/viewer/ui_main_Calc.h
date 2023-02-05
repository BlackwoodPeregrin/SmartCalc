#pragma once

#include <QCoreApplication>
#include <QLabel>
#include <QLayout>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_MainCalc {
 public:
  Ui_MainCalc() : sum_numbers(10) {
    _DistribMemory();
    progress_bar->setRange(0, 255);
    progress_bar->setValue(0);
    textEdit_formule->setReadOnly(true);
    label_final_formule->setAlignment(Qt::AlignRight | Qt::AlignTrailing |
                                      Qt::AlignVCenter);
    label_final_formule->setText("0");
  }

  ~Ui_MainCalc() {
    delete[] buttons_num;
    delete but_sin;
    delete but_cos;
    delete but_tan;
    delete but_acos;
    delete but_asin;
    delete but_atan;
    delete but_ln;
    delete but_log;
    delete but_sqrt;
    delete but_plus;
    delete but_minus;
    delete but_mult;
    delete but_div;
    delete but_mod;
    delete but_pow;
    delete but_l_brecket;
    delete but_r_brecket;
    delete but_dot;
    delete but_equal;
    delete but_clear;
    delete but_clear_last;
    delete but_x;
    delete but_graph;
    delete but_credit;
    delete but_deposit;
    delete greed_for_buttons;
    delete label_symbols;
    delete label_sum_symbols;
    delete label_l_brecket;
    delete label_sum_l_brecket;
    delete label_r_brecket;
    delete label_sum_r_brecket;
    delete progress_bar;
    delete hor_layout;
    delete label_final_formule;
    delete textEdit_formule;
    delete ver_layout;
    delete ver_layout_for_layouts;
    delete centralwidget;
  }

  void setupUi(QMainWindow *MainWindow) {
    _Set_text_to_but_numbers();
    _Set_Object_Names_to_QWidgets();
    _SetCursor();
    _CreateGreed();
    _CreateHorLayout();
    _CreateVerLayout();
    _CreateVerLayoutForLayouts();
    _Creat_CentralWidget();

    MainWindow->setFixedSize(800, 600);
    MainWindow->setCentralWidget(centralwidget);
    MainWindow->setWindowTitle(QCoreApplication::translate(
        "MainCalc", "Smart Calc BlackWood Peregrin", nullptr));
  }

 private:
  void _DistribMemory() {
    buttons_num = new QPushButton[sum_numbers];
    but_sin = new QPushButton("sin");
    but_cos = new QPushButton("cos");
    but_tan = new QPushButton("tan");
    but_acos = new QPushButton("acos");
    but_asin = new QPushButton("asin");
    but_atan = new QPushButton("atan");
    but_ln = new QPushButton("ln");
    but_log = new QPushButton("log");
    but_sqrt = new QPushButton("√");
    but_plus = new QPushButton("+");
    but_minus = new QPushButton("-");
    but_mult = new QPushButton("*");
    but_div = new QPushButton("/");
    but_mod = new QPushButton("mod");
    but_pow = new QPushButton("^");
    but_l_brecket = new QPushButton("(");
    but_r_brecket = new QPushButton(")");
    but_dot = new QPushButton(".");
    but_equal = new QPushButton("=");
    but_clear = new QPushButton("AC");
    but_clear_last = new QPushButton("<--");
    but_x = new QPushButton("X");
    but_graph = new QPushButton("Graph");
    but_credit = new QPushButton("Credit");
    but_deposit = new QPushButton("Deposit");
    label_final_formule = new QLabel("= 0");
    label_symbols = new QLabel("Symbols:");
    label_sum_symbols = new QLabel("0");
    label_l_brecket = new QLabel("'(':");
    label_sum_l_brecket = new QLabel("0");
    label_r_brecket = new QLabel("')':");
    label_sum_r_brecket = new QLabel("0");
    progress_bar = new QProgressBar;
    textEdit_formule = new QTextEdit;
    ver_layout = new QVBoxLayout();
    hor_layout = new QHBoxLayout();
    ver_layout_for_layouts = new QVBoxLayout();
    greed_for_buttons = new QGridLayout();
    centralwidget = new QWidget;
  }

  void _Set_text_to_but_numbers() {
    for (size_t i = 0; i < sum_numbers; ++i) {
      QString name_button;
      name_button.setNum(i);
      buttons_num[i].setText(name_button);
    }
  }

  void _Set_Object_Names_to_QWidgets() {
    but_graph->setObjectName("Gradient_1");
    but_sin->setObjectName("Gradient_2");
    but_x->setObjectName("Gradient_2");
    but_asin->setObjectName("Gradient_3");
    but_clear_last->setObjectName("Gradient_3");
    but_cos->setObjectName("Gradient_3");
    but_tan->setObjectName("Gradient_4");
    but_acos->setObjectName("Gradient_4");
    but_ln->setObjectName("Gradient_4");
    but_l_brecket->setObjectName("Gradient_4");
    but_atan->setObjectName("Gradient_5");
    but_log->setObjectName("Gradient_5");
    but_r_brecket->setObjectName("Gradient_5");
    (buttons_num + 7)->setObjectName("Gradient_5");
    but_credit->setObjectName("Gradient_5");
    (buttons_num + 4)->setObjectName("Gradient_6");
    but_pow->setObjectName("Gradient_6");
    but_mod->setObjectName("Gradient_6");
    but_deposit->setObjectName("Gradient_6");
    (buttons_num + 8)->setObjectName("Gradient_6");
    (buttons_num + 1)->setObjectName("Gradient_7");
    (buttons_num + 5)->setObjectName("Gradient_7");
    (buttons_num + 9)->setObjectName("Gradient_7");
    but_clear->setObjectName("Gradient_7");
    but_sqrt->setObjectName("Gradient_7");
    (buttons_num + 0)->setObjectName("Gradient_8");
    (buttons_num + 2)->setObjectName("Gradient_8");
    (buttons_num + 6)->setObjectName("Gradient_8");
    but_div->setObjectName("Gradient_8");
    (buttons_num + 3)->setObjectName("Gradient_9");
    but_mult->setObjectName("Gradient_9");
    but_dot->setObjectName("Gradient_9");
    but_minus->setObjectName("Gradient_10");
    but_equal->setObjectName("Gradient_10");
    but_plus->setObjectName("Gradient_11");
    label_final_formule->setObjectName("LabelFormule");
    label_symbols->setObjectName("Label");
    label_sum_symbols->setObjectName("Label");
    label_l_brecket->setObjectName("Label");
    label_sum_l_brecket->setObjectName("Label");
    label_r_brecket->setObjectName("Label");
    label_sum_r_brecket->setObjectName("Label");
    progress_bar->setObjectName("ProgressBar");
    textEdit_formule->setObjectName("textEditFormule");
    ver_layout->setObjectName("VerLayout");
    hor_layout->setObjectName("HorLayout");
    ver_layout_for_layouts->setObjectName("VerLayout");
    greed_for_buttons->setObjectName("Greed");
    centralwidget->setObjectName("centralwidget");
  }

  void _SetCursor() {
    but_graph->setCursor(QCursor(Qt::OpenHandCursor));
    but_x->setCursor(QCursor(Qt::OpenHandCursor));
    but_clear_last->setCursor(QCursor(Qt::OpenHandCursor));
    but_l_brecket->setCursor(QCursor(Qt::OpenHandCursor));
    but_r_brecket->setCursor(QCursor(Qt::OpenHandCursor));
    but_mod->setCursor(QCursor(Qt::OpenHandCursor));
    but_clear->setCursor(QCursor(Qt::OpenHandCursor));
    but_sin->setCursor(QCursor(Qt::OpenHandCursor));
    but_asin->setCursor(QCursor(Qt::OpenHandCursor));
    but_ln->setCursor(QCursor(Qt::OpenHandCursor));
    (buttons_num + 7)->setCursor(QCursor(Qt::OpenHandCursor));
    (buttons_num + 8)->setCursor(QCursor(Qt::OpenHandCursor));
    (buttons_num + 9)->setCursor(QCursor(Qt::OpenHandCursor));
    but_div->setCursor(QCursor(Qt::OpenHandCursor));
    but_cos->setCursor(QCursor(Qt::OpenHandCursor));
    but_acos->setCursor(QCursor(Qt::OpenHandCursor));
    but_log->setCursor(QCursor(Qt::OpenHandCursor));
    (buttons_num + 4)->setCursor(QCursor(Qt::OpenHandCursor));
    (buttons_num + 5)->setCursor(QCursor(Qt::OpenHandCursor));
    (buttons_num + 6)->setCursor(QCursor(Qt::OpenHandCursor));
    but_mult->setCursor(QCursor(Qt::OpenHandCursor));
    but_tan->setCursor(QCursor(Qt::OpenHandCursor));
    but_atan->setCursor(QCursor(Qt::OpenHandCursor));
    but_pow->setCursor(QCursor(Qt::OpenHandCursor));
    (buttons_num + 1)->setCursor(QCursor(Qt::OpenHandCursor));
    (buttons_num + 2)->setCursor(QCursor(Qt::OpenHandCursor));
    (buttons_num + 3)->setCursor(QCursor(Qt::OpenHandCursor));
    but_minus->setCursor(QCursor(Qt::OpenHandCursor));
    but_credit->setCursor(QCursor(Qt::OpenHandCursor));
    but_deposit->setCursor(QCursor(Qt::OpenHandCursor));
    but_sqrt->setCursor(QCursor(Qt::OpenHandCursor));
    (buttons_num + 0)->setCursor(QCursor(Qt::OpenHandCursor));
    but_dot->setCursor(QCursor(Qt::OpenHandCursor));
    but_equal->setCursor(QCursor(Qt::OpenHandCursor));
    but_plus->setCursor(QCursor(Qt::OpenHandCursor));
  }

  void _CreateGreed() {
    greed_for_buttons->addWidget(but_graph, 0, 0);
    greed_for_buttons->addWidget(but_x, 0, 1);
    greed_for_buttons->addWidget(but_clear_last, 0, 2);
    greed_for_buttons->addWidget(but_l_brecket, 0, 3);
    greed_for_buttons->addWidget(but_r_brecket, 0, 4);
    greed_for_buttons->addWidget(but_mod, 0, 5);
    greed_for_buttons->addWidget(but_clear, 0, 6);

    greed_for_buttons->addWidget(but_sin, 1, 0);
    greed_for_buttons->addWidget(but_asin, 1, 1);
    greed_for_buttons->addWidget(but_ln, 1, 2);
    greed_for_buttons->addWidget((buttons_num + 7), 1, 3);
    greed_for_buttons->addWidget((buttons_num + 8), 1, 4);
    greed_for_buttons->addWidget((buttons_num + 9), 1, 5);
    greed_for_buttons->addWidget(but_div, 1, 6);

    greed_for_buttons->addWidget(but_cos, 2, 0);
    greed_for_buttons->addWidget(but_acos, 2, 1);
    greed_for_buttons->addWidget(but_log, 2, 2);
    greed_for_buttons->addWidget((buttons_num + 4), 2, 3);
    greed_for_buttons->addWidget((buttons_num + 5), 2, 4);
    greed_for_buttons->addWidget((buttons_num + 6), 2, 5);
    greed_for_buttons->addWidget(but_mult, 2, 6);

    greed_for_buttons->addWidget(but_tan, 3, 0);
    greed_for_buttons->addWidget(but_atan, 3, 1);
    greed_for_buttons->addWidget(but_pow, 3, 2);
    greed_for_buttons->addWidget((buttons_num + 1), 3, 3);
    greed_for_buttons->addWidget((buttons_num + 2), 3, 4);
    greed_for_buttons->addWidget((buttons_num + 3), 3, 5);
    greed_for_buttons->addWidget(but_minus, 3, 6);

    greed_for_buttons->addWidget(but_credit, 4, 0);
    greed_for_buttons->addWidget(but_deposit, 4, 1);
    greed_for_buttons->addWidget(but_sqrt, 4, 2);
    greed_for_buttons->addWidget((buttons_num + 0), 4, 3);
    greed_for_buttons->addWidget(but_dot, 4, 4);
    greed_for_buttons->addWidget(but_equal, 4, 5);
    greed_for_buttons->addWidget(but_plus, 4, 6);
  }

  void _CreateHorLayout() {
    hor_layout->addWidget(label_symbols);
    hor_layout->addWidget(label_sum_symbols);
    hor_layout->addWidget(progress_bar);
    hor_layout->addWidget(label_l_brecket);
    hor_layout->addWidget(label_sum_l_brecket);
    hor_layout->addWidget(label_r_brecket);
    hor_layout->addWidget(label_sum_r_brecket);
  }

  void _CreateVerLayout() {
    ver_layout->addLayout(hor_layout);
    ver_layout->addWidget(textEdit_formule);
    ver_layout->addWidget(label_final_formule);
  }

  void _CreateVerLayoutForLayouts() {
    ver_layout_for_layouts->addLayout(ver_layout);
    ver_layout_for_layouts->addLayout(greed_for_buttons);
  }

  void _Creat_CentralWidget() {
    centralwidget->setLayout(ver_layout_for_layouts);
  }

 private:
  size_t sum_numbers;  // summary buttons with number

 public:
  /*-----------------------BUTTONS-----------------------*/
  /*--buttons 0...9--*/
  QPushButton *buttons_num;
  /*--buttons funcs--*/
  QPushButton *but_sin;
  QPushButton *but_cos;
  QPushButton *but_tan;
  QPushButton *but_acos;
  QPushButton *but_asin;
  QPushButton *but_atan;
  QPushButton *but_ln;
  QPushButton *but_log;
  QPushButton *but_sqrt;
  /*--buttons signs--*/
  QPushButton *but_plus;
  QPushButton *but_minus;
  QPushButton *but_mult;
  QPushButton *but_div;
  QPushButton *but_mod;
  QPushButton *but_pow;
  QPushButton *but_l_brecket;
  QPushButton *but_r_brecket;
  /*other buttons--*/
  QPushButton *but_dot;
  QPushButton *but_equal;
  QPushButton *but_clear;
  QPushButton *but_clear_last;
  QPushButton *but_x;
  QPushButton *but_graph;
  QPushButton *but_credit;
  QPushButton *but_deposit;
  /*-----------------------LABELS in area-------------------*/
  QLabel *label_final_formule;
  QLabel *label_symbols;
  QLabel *label_sum_symbols;
  QLabel *label_l_brecket;
  QLabel *label_sum_l_brecket;
  QLabel *label_r_brecket;
  QLabel *label_sum_r_brecket;
  /*-----------------------PROGRESS BAR in area-------------*/
  QProgressBar *progress_bar;
  /*-----------------------TEXT EDIT in area----------------*/
  QTextEdit *textEdit_formule;
  /*-----------------------LAYOUTS in area------------------*/
  QVBoxLayout *ver_layout;
  QHBoxLayout *hor_layout;
  QVBoxLayout *ver_layout_for_layouts;
  /*----------------------GREED for all buttons in area-----*/
  QGridLayout *greed_for_buttons;
  /*----------------------Central Widget in Main Window result----------*/
  QWidget *centralwidget;
};

namespace Ui {
class MainCalc : public Ui_MainCalc {};
}  // namespace Ui

QT_END_NAMESPACE

