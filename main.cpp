#include "mainwindow.h"
#include <QApplication>
//#include <iostream>
#include <core/Statistics.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QIcon icon("./images/app.png");
    if (icon.isNull()) {
        qDebug() << "图标加载失败！请检查资源路径";
    } else {
        qDebug() << "图标加载成功";
        app.setWindowIcon(icon);
    }
    MainWindow w;
    w.show();
    Statistics stats;
    stats.printAllCities();

    return app.exec();
}


