#include <QApplication>
#include <QFile>

#include "viewer/viewerCalc.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QString path = QCoreApplication::applicationDirPath() + "/style.css";
  QFile file(path);
  file.open(QFile::ReadOnly);
  a.setStyleSheet(file.readAll());
  s21_SmartCalc::ViewerCalc ww;
  ww.show();
  return a.exec();
}
