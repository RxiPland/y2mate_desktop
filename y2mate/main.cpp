#include "searchvideowindow.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>


QString appVersion = "v2.0.0";

void checkSettings(){

    QFile dataFile("Data/data.json");

    if (dataFile.exists()){
        // everything OK

    } else{
        // create file with default content (settings)
        QDir directory;
        directory.mkdir("./Data");

        dataFile.open(QIODevice::WriteOnly | QIODevice::Text);

        QJsonObject objData;
        objData["app_version"] = appVersion;
        objData["user_agent"] = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/111.0.0.0 Safari/537.36";

        QJsonObject history;

        int i;
        for(i=1; i<6; i++){

            history[QString::number(i)] = "";
        }

        objData["search_history"] = history;

        QJsonDocument docData(objData);
        dataFile.write(docData.toJson());
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/y2mate.ico"));
    a.setQuitOnLastWindowClosed(true);

    checkSettings();

    SearchVideoWindow svw;
    svw.appVersion = appVersion;
    svw.show();

    return a.exec();
}
