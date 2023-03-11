#include "searchvideowindow.h"
#include "./ui_searchvideowindow.h"
#include "settingsdialog.h"
#include "downloadvideowindow.h"

#include <Windows.h>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QProcess>
#include <QRegExp>
#include <QNetworkRequest>
#include <QNetworkReply>


searchVideoWindow::searchVideoWindow(QWidget *parent, bool jsonCorrupted)
    : QMainWindow(parent)
    , ui(new Ui::SearchVideoWindow)
{
    ui->setupUi(this);
    this->show();

    if(jsonCorrupted){
        QMessageBox::warning(this, "Oznámení", "Soubor s nastavením byl poškozen. Nastavení bylo přepsáno do defaultního stavu, aby program mohl fungovat.");
    }

    searchVideoWindow::loadSettings();
}

searchVideoWindow::~searchVideoWindow()
{
    delete ui;
}

void searchVideoWindow::loadSettings()
{
    QFile dataFile(QDir::currentPath() + "/Data/data.json");

    if (dataFile.exists()){
        dataFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QByteArray fileContent = dataFile.readAll();
        dataFile.close();

        if(fileContent.isEmpty()){
            // File is empty

            QMessageBox::critical(this, "Chyba", "Soubor s nastavením je prázdný! Program bude restartován pro opravu.");

            QProcess::startDetached(QApplication::applicationFilePath());

            this->close();
            return;

        } else{
            QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

            if(loadedJson.isEmpty()){
                // JSON is corrupted

                QMessageBox::critical(this, "Chyba", "JSON v souboru s nastavením je poškozený! Program bude restartován pro opravu.");

                QProcess::startDetached(QApplication::applicationFilePath());

                this->close();
                return;

            } else{
                // everything OK

                searchVideoWindow::appVersion = loadedJson["app_version"].toString().toUtf8();
                searchVideoWindow::userAgent = loadedJson["user_agent"].toString().toUtf8();
            }
        }
    }
}

void searchVideoWindow::disableWidgets(bool disable)
{
    ui->lineEdit->setDisabled(disable);
    ui->pushButton->setDisabled(disable);
}


void searchVideoWindow::sortQualities(QStringList *list)
{
    QStringList tempList = list->toList();

    int i;
    static QRegularExpression re("(kbps|p)");

    for(i=0; i<tempList.length(); i++){

        tempList[i] = tempList[i].replace(re, "");
    }

    // source: https://stackoverflow.com/questions/65061873/sorting-a-qstring-list-by-numbers-c
    std::sort(tempList.begin(), tempList.end(), [](const QString &lhs, const QString &rhs)
    {
        int num_lhs = lhs.toInt();
        int num_rhs = rhs.toInt();
        return num_lhs < num_rhs;
    });

    *list = tempList;
}



void searchVideoWindow::on_action_menu1_1_triggered()
{
    // open y2mate's website

    ShellExecute(0, 0, L"https://www.y2mate.com", 0, 0, SW_HIDE);
}


void searchVideoWindow::on_action_menu1_2_triggered()
{
    // open source code on github

    ShellExecute(0, 0, L"https://github.com/RxiPland/y2mate_desktop", 0, 0, SW_HIDE);
}


void searchVideoWindow::on_action_menu1_3_triggered()
{
    // open settings window

    settingsDialog sd;
    sd.setModal(true);

    this->hide();
    sd.exec();
    this->show();
}


void searchVideoWindow::on_action_menu2_1_triggered()
{
    // delete history from JSON file

    QMessageBox::StandardButton replyBox = QMessageBox::information(this, "Oznámení", "Opravdu chcete smazat historii?", QMessageBox::Yes | QMessageBox::No);

    if (replyBox == QMessageBox::No){
        return;
    }

    QFile dataFile(QDir::currentPath() + "/Data/data.json");

    if (dataFile.exists()){

        dataFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QByteArray fileContent = dataFile.readAll();
        dataFile.close();

        if(fileContent.isEmpty()){

            QMessageBox::critical(this, "Chyba", "Soubor s nastavením je prázdný! Program bude restartován pro opravu.");

            QProcess::startDetached(QApplication::applicationFilePath());

            this->close();
            return;
        }

        QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

        if(loadedJson.isEmpty()){
            // JSON cannot be loaded

            QMessageBox::critical(this, "Chyba", "JSON v souboru s nastavením je poškozený! Program bude restartován pro opravu.");

            QProcess::startDetached(QApplication::applicationFilePath());

            this->close();
            return;
        }

        QJsonObject history;

        int i;
        for(i=1; i<6; i++){

            history[QString::number(i)] = "";
        }
        loadedJson["search_history"] = history;

        QJsonDocument docData(loadedJson);

        dataFile.open(QIODevice::WriteOnly | QIODevice::Text);
        int status = dataFile.write(docData.toJson());
        dataFile.close();

        if (status == -1){
            QMessageBox::critical(this, "Chyba", "Nastala chyba při zapisování do souboru s nastavením!\n\n" + dataFile.fileName());

            return;
        }

        QMessageBox::information(this, "Oznámení", "Historie byla úspěšně smazána");

    } else{
        // file with settings not found

        QMessageBox::critical(this, "Chyba", "Soubor s nastavením neexistuje! Program bude restartován pro opravu.");

        QProcess::startDetached(QApplication::applicationFilePath());

        this->close();
        return;
    }
}


void searchVideoWindow::on_pushButton_clicked()
{
    // search video button

    searchVideoWindow::disableWidgets();
    QString videoUrl = ui->lineEdit->text().trimmed();

    // source: https://regex101.com/r/kM8eW3/1
    QRegExp rx("(^$|(http(s)?://)([\\w-]+\\.)+[\\w-]+([\\w- ;,./?%&=]*))");

    // validate URL
    if(videoUrl == ""){

        QMessageBox::critical(this, "Chyba", "Pole pro URL adresu nemůže být prázdné!");

        searchVideoWindow::disableWidgets(false);
        ui->lineEdit->setFocus();
        return;

    } else if (!rx.exactMatch(videoUrl)){

        QMessageBox::critical(this, "Chyba", "Zadejte kompletní URL adresu!\n\nPř. https://www.google.com");

        searchVideoWindow::disableWidgets(false);
        ui->lineEdit->setFocus();
        return;
    }


    // request

    QByteArray data;

    data.append("k_query=");
    data.append(QUrl::toPercentEncoding(videoUrl).toStdString());
    data.append("&");
    data.append("k_page=mp3");
    data.append("&");
    data.append("hl=en");
    data.append("&");
    data.append("q_auto=1");


    QNetworkRequest request;
    request.setUrl(QUrl("https://www.y2mate.com/mates/analyzeV2/ajax"));
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded; charset=UTF-8");

    QNetworkReply *replyPost = manager.post(request, data);

    while (!replyPost->isFinished())
    {
        qApp->processEvents();
    }

    QByteArray response = replyPost->readAll();
    QJsonObject loadedJson = QJsonDocument::fromJson(response).object();

    QString status = loadedJson["status"].toString().toLower();

    if (status != "ok"){

        QMessageBox::warning(this, "Chyba", QString("Nastala chyba! Y2mate vrátil: {\"status\": \"%1\"").arg(status));
        return;
    }

    QJsonObject formats = loadedJson["links"].toObject();

    // capture mp3 qualities
    QJsonObject mp3Files = formats["mp3"].toObject();
    QStringList mp3Qualities;

    foreach(QJsonValueConstRef x, mp3Files){

        if(x.toObject()["f"] == "mp3"){
            mp3Qualities.append(x.toObject()["q"].toString());
        }
    }
    sortQualities(&mp3Qualities);

    // capture mp4 qualities
    QJsonObject mp4Files = formats["mp4"].toObject();
    QStringList mp4Qualities;

    foreach(QJsonValueConstRef x, mp4Files){

        if(x.toObject()["f"] == "mp4"){
            mp4Qualities.append(x.toObject()["q"].toString());
        }
    }
    sortQualities(&mp4Qualities);


    QString ytChannel = loadedJson["a"].toString();
    int videoDuration = loadedJson["t"].toInt();
    QString videoName = loadedJson["title"].toString();


    downloadVideoWindow dvw;
    this->hide();
    dvw.show();

    while(!dvw.isHidden()){
        qApp->processEvents();
    }

    disableWidgets(false);
    this->show();
}

void searchVideoWindow::on_lineEdit_returnPressed()
{
    // return pressed when writing URL

    searchVideoWindow::on_pushButton_clicked();
}
