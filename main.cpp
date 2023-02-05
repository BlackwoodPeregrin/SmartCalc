#include <QApplication>
#include <QFile>
#include <QDir>

#include "viewer/viewerCalc.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QDir dir("./style.css");
  QString systemCommand = "cp " + dir.path() + " " + QCoreApplication::applicationDirPath();
  system(systemCommand.toStdString().c_str());

  QString path = QCoreApplication::applicationDirPath() + "/style.css";
  QFile file(path);

  qDebug() << dir.path();
  file.open(QFile::ReadOnly);
  a.setStyleSheet(file.readAll());
  s21_SmartCalc::ViewerCalc ww;
  ww.show();
  return a.exec();
}
