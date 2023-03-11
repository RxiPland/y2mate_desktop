#include "searchvideowindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SearchVideoWindow w;
    w.show();
    return a.exec();
}
