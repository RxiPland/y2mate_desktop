#include "searchvideowindow.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>


QString appVersion = "v2.0.0";

bool checkSettings(){

    // variable if json will be repaired/fixed
    bool jsonCorrupted = false;


    QFile dataFile(QDir::currentPath() + "/Data/data.json");

    if (dataFile.exists()){
        dataFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QByteArray fileContent = dataFile.readAll();
        dataFile.close();

        if(fileContent.isEmpty()){
            // File is empty

        } else{
            QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

            if(loadedJson.isEmpty()){
                // JSON is corrupted

            } else{
                // everything OK
                return jsonCorrupted;
            }
        }

        jsonCorrupted = true;
    }

    // create file with default content (settings)
    QDir directory;
    directory.mkdir("./Data");

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

    dataFile.open(QIODevice::WriteOnly | QIODevice::Text);
    dataFile.write(docData.toJson());
    dataFile.close();

    return jsonCorrupted;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/y2mate.ico"));
    a.setQuitOnLastWindowClosed(true);

    bool jsonCorrupted = checkSettings();

    searchVideoWindow svw(nullptr, jsonCorrupted);
    svw.appVersion = appVersion;
    svw.show();

    return a.exec();
}
