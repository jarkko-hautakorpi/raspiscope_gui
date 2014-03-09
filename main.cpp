
#include <QtGui/QApplication>

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "mainwindow.h"
#include "scopesetupwindow.h"

using namespace std;
QT_USE_NAMESPACE



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
