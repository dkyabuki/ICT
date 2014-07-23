#include "mainwindow.h"
#include <QApplication>
#include "config.h"

Registers Config::reg;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
