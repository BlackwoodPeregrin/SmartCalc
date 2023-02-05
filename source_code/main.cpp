#include <QApplication>
#include <QDir>
#include <QFile>

#include "viewer/viewerCalc.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21_SmartCalc::ViewerCalc ww;
  ww.show();
  return a.exec();
}
