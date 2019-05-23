#include <QApplication>
#include <QFile>
#include <QtDebug>
#include <iostream>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QFile styleSheet("C:\\Users\\Alexandra\\Documents\\QT\\GOL\\stylesheet.qss"); //path where the file is stored

    QApplication a(argc, argv);
    a.setStyleSheet(styleSheet.readAll());


    MainWindow w;
    w.show();
    
    return a.exec();
}
