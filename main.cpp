#include "addstu.h"
#include <QApplication>
#include "mainwindow.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    m.show();

    return a.exec();    // 主运行循环
}
