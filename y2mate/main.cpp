#include "searchvideowindow.h"

#include <QApplication>


QString app_version = "v2.0.0";
QByteArray user_agent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/111.0.0.0 Safari/537.36";


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/y2mate.ico"));
    a.setQuitOnLastWindowClosed(true);

    SearchVideoWindow svw;
    svw.show();

    return a.exec();
}
