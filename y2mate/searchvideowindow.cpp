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
#include <QLabel>


searchVideoWindow::searchVideoWindow(QWidget *parent, bool jsonCorrupted)
    : QMainWindow(parent)
    , ui(new Ui::SearchVideoWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(windowFlags() &(~Qt::WindowMaximizeButtonHint));
    this->show();

    if(jsonCorrupted){
        QMessageBox::warning(this, "Oznámení", "Soubor s nastavením byl poškozen. Nastavení bylo přepsáno do defaultního stavu, aby program mohl fungovat.");
    }

    searchVideoWindow::loadSettings();

    if(searchVideoWindow::checkForUpdates){
        searchVideoWindow::checkUpdate();
    }
}

searchVideoWindow::~searchVideoWindow()
{
    delete ui;
}

void searchVideoWindow::loadSettings()
{
    QLabel *label = new QLabel("Načítám nastavení ...   ");
    ui->statusBar->addWidget(label);

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
                this->setWindowTitle("y2mate desktop  |  " + searchVideoWindow::appVersion);

                searchVideoWindow::userAgent = loadedJson["user_agent"].toString().toUtf8();
                searchVideoWindow::checkForUpdates = loadedJson["check_for_updates"].toBool();
                searchVideoWindow::allowHistory = loadedJson["allow_history"].toBool();

                // disable/enable history tab

                if(!allowHistory){
                    ui->menu2_1->menuAction()->setVisible(false);
                    ui->menu2_2->menuAction()->setVisible(false);
                    ui->menu2_3->menuAction()->setVisible(false);
                    ui->menu2_4->menuAction()->setVisible(false);
                    ui->menu2_5->menuAction()->setVisible(false);

                    ui->action_menu2_6->setText("Historie není povolena");
                    ui->action_menu2_6->setDisabled(true);
                    ui->action_menu2_6->setIconVisibleInMenu(false);

                } else{
                    QJsonObject history = loadedJson["search_history"].toObject();

                    QJsonObject history1 = history["1"].toObject();
                    if(history1.isEmpty()){
                        ui->menu2_1->menuAction()->setVisible(false);
                    }

                    QJsonObject history2 = history["2"].toObject();
                    if(history2.isEmpty()){
                        ui->menu2_2->menuAction()->setVisible(false);
                    }

                    QJsonObject history3 = history["3"].toObject();
                    if(history3.isEmpty()){
                        ui->menu2_3->menuAction()->setVisible(false);
                    }

                    QJsonObject history4 = history["4"].toObject();
                    if(history4.isEmpty()){
                        ui->menu2_4->menuAction()->setVisible(false);
                    }

                    QJsonObject history5 = history["5"].toObject();
                    if(history5.isEmpty()){
                        ui->menu2_5->menuAction()->setVisible(false);
                    }

                    ui->action_menu2_6->setText("Smazat historii");
                }
            }
        }
    }

    ui->statusBar->removeWidget(label);
}

void searchVideoWindow::checkUpdate()
{

    QNetworkRequest request;
    request.setUrl(QUrl("https://api.github.com/repos/RxiPland/y2mate_desktop/releases/latest"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);

    QNetworkReply *replyGet = manager.get(request);

    while (!replyGet->isFinished())
    {
        qApp->processEvents();
    }

    if(replyGet->error() != QNetworkReply::NoError){
        return;
    }

    QByteArray response = replyGet->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();

    QString newestVersion = jsonObject["tag_name"].toString();

    if (newestVersion != appVersion && newestVersion != ""){

        QMessageBox msgBox;
        msgBox.setWindowTitle("Aktualizace");
        msgBox.setText("Je dostupná novější verze y2mate desktop: " + newestVersion + "\nVaše verze: " + appVersion  +"\n\nPři instalaci nové verze se předchozí automaticky odstraní.");
        QAbstractButton* pButtonYes = msgBox.addButton("  Otevřít odkaz  ", QMessageBox::YesRole);
        msgBox.addButton("Zrušit", QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton()==pButtonYes) {
            ShellExecute(0, 0, L"https://github.com/RxiPland/y2mate_desktop", 0, 0, SW_HIDE);
        }
    }
}

void searchVideoWindow::disableWidgets(bool disable)
{
    ui->lineEdit->setDisabled(disable);
    ui->lineEdit->setClearButtonEnabled(!disable);
    ui->pushButton->setDisabled(disable);
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

    QLabel *label = new QLabel("Hledám video...   ");
    ui->statusBar->addWidget(label);

    QNetworkReply *replyPost = manager.post(request, data);

    while (!replyPost->isFinished())
    {
        qApp->processEvents();
    }

    ui->statusBar->removeWidget(label);

    QNetworkReply::NetworkError error = replyPost->error();

    if(error == QNetworkReply::HostNotFoundError){
        // no internet connection available

        disableWidgets(false);
        QMessageBox::critical(this, "Chyba", "Nelze se připojit k internetu nebo server není dostupný!");
        return;

    } else if (error != QNetworkReply::NetworkError::NoError){
        // an unknown error occured

        disableWidgets(false);
        const QString &errorString = replyPost->errorString();
        QMessageBox::warning(this, "Chyba", QString("Nastala chyba při komunikaci s webem!\n\nChyba: %1").arg(errorString));
        return;
    }

    QByteArray response = replyPost->readAll();
    QJsonObject loadedJson = QJsonDocument::fromJson(response).object();

    QString status = loadedJson["status"].toString().toLower();
    QString message = loadedJson["mess"].toString();


    if (status != "ok"){

        QMessageBox::warning(this, "Chyba", QString("Nastala chyba! Y2mate vrátil: {\"status\": \"%1\"}").arg(status));
        disableWidgets(false);
        return;

    } else if (message.contains("Please enter valid video URL.")){

        QMessageBox::warning(this, "Chyba", "Video pod tímto odkazem neexistuje!");
        disableWidgets(false);
        return;

    } else if (!message.isEmpty()){

        QMessageBox::warning(this, "Chyba", QString("Nastala chyba! Y2mate vrátil: {\"message\": \"%1\"}").arg(message));
        disableWidgets(false);
        return;

    } else if (message.isEmpty()){
        // OK

    } else{
        QMessageBox::warning(this, "Chyba", QString("Nastala neznámá chyba! Server vrátil:\n\n%1").arg(response));
        disableWidgets(false);
        return;
    }

    QJsonObject formats = loadedJson["links"].toObject();

    // capture mp3 qualities
    QJsonObject mp3Files = formats["mp3"].toObject();
    QJsonObject mp3Qualities;

    foreach(QJsonValueConstRef x, mp3Files){

        if(x.toObject()["f"] == "mp3"){
            mp3Qualities[x.toObject()["q"].toString()] = x.toObject()["k"].toString();
        }
    }

    // capture mp4 qualities
    QJsonObject mp4Files = formats["mp4"].toObject();
    QJsonObject mp4Qualities;

    foreach(QJsonValueConstRef x, mp4Files){

        if(x.toObject()["f"] == "mp4"){
            mp4Qualities[x.toObject()["q"].toString()] = x.toObject()["k"].toString();
        }
    }


    QString ytChannel = loadedJson["a"].toString();
    if(ytChannel.isEmpty()){
        QMessageBox::warning(this, "Chyba", "Nepodařilo se získat název youtube kanálu z odpovědi serveru!");
        disableWidgets(false);
        return;
    }

    int videoDuration = loadedJson["t"].toInt();
    if(videoDuration == 0){
        QMessageBox::warning(this, "Chyba", "Nepodařilo se získat délku videa z odpovědi serveru!");
        disableWidgets(false);
        return;
    }

    QString videoId = loadedJson["vid"].toString();
    if(videoId.isEmpty()){
        QMessageBox::warning(this, "Chyba", "Nepodařilo se získat ID videa z odpovědi serveru!");
        disableWidgets(false);
        return;
    }

    QString videoName = loadedJson["title"].toString();
    if(videoId.isEmpty()){
        QMessageBox::warning(this, "Chyba", "Nepodařilo se získat název videa z odpovědi serveru!");
        disableWidgets(false);
        return;
    }

    // remove duplicated whitespaces
    QString tempName;
    QChar c;
    bool whitespace = false;
    int i;
    for(i=0; i<videoName.length(); i++){

        c = videoName[i];

        if(c == ' ' && !whitespace){
            whitespace = true;
            tempName.append(c);

        } else if (c != ' '){
            whitespace = false;
            tempName.append(c);
        }
    }
    videoName = tempName;

    downloadVideoWindow dvw(nullptr);
    dvw.appVersion = searchVideoWindow::appVersion;
    dvw.userAgent = searchVideoWindow::userAgent;
    dvw.ytChannel = ytChannel;
    dvw.videoDuration = videoDuration;
    dvw.videoName = videoName;
    dvw.videoID = videoId;
    dvw.videoUrl = videoUrl;

    dvw.mp3Qualities = mp3Qualities;
    dvw.mp4Qualities = mp4Qualities;

    // set data to widgets
    dvw.loadData();

    dvw.show();
    this->hide();

    // wait until closed
    while(!dvw.isHidden()){
        qApp->processEvents();
    }

    // exit if pressed X
    if(dvw.exitApp){
        qApp->setQuitOnLastWindowClosed(true);
        this->close();
        return;
    }

    disableWidgets(false);
    ui->lineEdit->clear();
    this->show();
}


void searchVideoWindow::on_lineEdit_returnPressed()
{
    // return pressed when typing URL

    searchVideoWindow::on_pushButton_clicked();
}

void searchVideoWindow::on_action_menu2_6_triggered()
{
    // delete history from JSON file

    QMessageBox msgBox;
    msgBox.setWindowTitle("Upozornění");
    msgBox.setText("Opravdu chcete smazat historii?");
    msgBox.addButton("Ano", QMessageBox::YesRole);
    QAbstractButton* pButtonNo = msgBox.addButton("Zrušit", QMessageBox::NoRole);
    msgBox.exec();

    if (msgBox.clickedButton() == pButtonNo) {
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

            history[QString::number(i)] = QJsonObject();
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

    searchVideoWindow::loadSettings();
}

