#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/y2mate.ico"));
    MainWindow w;
    w.resize(495,0);
    w.show();

    return a.exec();
}
