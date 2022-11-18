#include "mainwindow.h"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/y2mate.ico"));

    MainWindow w;
    w.resize(495,0);
    w.show();

    w.store_window_parameters(w.geometry().left(), w.geometry().top()-35);

    return a.exec();
}
