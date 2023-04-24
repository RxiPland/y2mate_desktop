#include "searchvideowindow.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>


QString appVersion = "v2.2.4";

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

            } else if (loadedJson["app_version"] != appVersion){
                // version was manualy changed

                loadedJson["app_version"] = appVersion;

                QJsonDocument docData(loadedJson);

                // write settings to file
                dataFile.open(QIODevice::WriteOnly | QIODevice::Text);
                dataFile.write(docData.toJson());
                dataFile.close();

                return false;

            } else{
                // everything OK
                return false;
            }
        }

        jsonCorrupted = true;
    }

    // create folder
    QDir directory(QDir::currentPath());
    directory.mkdir("./Data");

    QJsonObject objData;
    objData["app_version"] = appVersion;
    objData["user_agent"] = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/111.0.0.0 Safari/537.36";
    objData["allow_history"] = true;
    objData["check_for_updates"] = true;
    objData["last_path"] = QDir::homePath();
    objData["enable_last_path"] = true;
    objData["replace_name_with_hash"] = false;
    objData["replace_name_with_underscores"] = false;
    objData["show_download_url_button"] = false;
    objData["download_finished_sound"] = true;

    QJsonObject history;

    int i;
    for(i=1; i<6; i++){

        history[QString::number(i)] = QJsonObject();
    }
    objData["search_history"] = history;

    QJsonDocument docData(objData);

    // write settings to file
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
    svw.checkUpdate();

    return a.exec();
}
