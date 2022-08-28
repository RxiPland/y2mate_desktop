#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/resource/images/y2mate.ico"));
    MainWindow w;
    w.show();

    return a.exec();
}
