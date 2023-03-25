#include "searchvideowindow.h"
#include "./ui_searchvideowindow.h"
#include "settingsdialog.h"
#include "downloadvideowindow.h"
#include "editvideodialog.h"
#include "downloaddialog.h"

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
#include <QFileDialog>
#include <QApplication>


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
            QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
            return;

        } else{
            QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

            if(loadedJson.isEmpty()){
                // JSON is corrupted

                QMessageBox::critical(this, "Chyba", "JSON v souboru s nastavením je poškozený! Program bude restartován pro opravu.");

                QProcess::startDetached(QApplication::applicationFilePath());
                QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
                return;

            } else{
                // everything OK

                searchVideoWindow::appVersion = loadedJson["app_version"].toString();
                this->setWindowTitle("y2mate desktop  |  " + searchVideoWindow::appVersion);

                searchVideoWindow::userAgent = loadedJson["user_agent"].toString().toUtf8();
                searchVideoWindow::checkForUpdates = loadedJson["check_for_updates"].toBool();
                searchVideoWindow::allowHistory = loadedJson["allow_history"].toBool();
                searchVideoWindow::lastSavePath = loadedJson["last_path"].toString();
                searchVideoWindow::lastPathEnabled = loadedJson["enable_last_path"].toBool();
                searchVideoWindow::replaceNameWithHash = loadedJson["replace_name_with_hash"].toBool();
                searchVideoWindow::replaceNameWithUnderscores = loadedJson["replace_name_with_underscores"].toBool();
                searchVideoWindow::showDownloadUrlButton = loadedJson["show_download_url_button"].toBool();

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

                    } else{
                        ui->menu2_1->menuAction()->setText(history1["video_name"].toString());
                        ui->action_menu_2_1_3->setText("Délka: " + history1["video_duration"].toString());
                        ui->menu2_1->menuAction()->setVisible(true);
                    }

                    QJsonObject history2 = history["2"].toObject();
                    if(history2.isEmpty()){
                        ui->menu2_2->menuAction()->setVisible(false);

                    } else{
                        ui->menu2_2->menuAction()->setText(history2["video_name"].toString());
                        ui->action_menu_2_2_3->setText("Délka: " + history2["video_duration"].toString());
                        ui->menu2_2->menuAction()->setVisible(true);
                    }

                    QJsonObject history3 = history["3"].toObject();
                    if(history3.isEmpty()){
                        ui->menu2_3->menuAction()->setVisible(false);

                    } else{
                        ui->menu2_3->menuAction()->setText(history3["video_name"].toString());
                        ui->action_menu_2_3_3->setText("Délka: " + history3["video_duration"].toString());
                        ui->menu2_3->menuAction()->setVisible(true);
                    }

                    QJsonObject history4 = history["4"].toObject();
                    if(history4.isEmpty()){
                        ui->menu2_4->menuAction()->setVisible(false);

                    } else{
                        ui->menu2_4->menuAction()->setText(history4["video_name"].toString());
                        ui->action_menu_2_4_3->setText("Délka: " + history4["video_duration"].toString());
                        ui->menu2_4->menuAction()->setVisible(true);
                    }

                    QJsonObject history5 = history["5"].toObject();
                    if(history5.isEmpty()){
                        ui->menu2_5->menuAction()->setVisible(false);

                    } else{
                        ui->menu2_5->menuAction()->setText(history5["video_name"].toString());
                        ui->action_menu_2_5_3->setText("Délka: " + history5["video_duration"].toString());
                        ui->menu2_5->menuAction()->setVisible(true);
                    }

                    ui->action_menu2_6->setText("Smazat historii");
                    ui->action_menu2_6->setDisabled(false);
                    ui->action_menu2_6->setIconVisibleInMenu(true);
                }
            }
        }
    }

    ui->statusBar->removeWidget(label);
}

void searchVideoWindow::checkUpdate()
{

    if(!searchVideoWindow::checkForUpdates){
        return;
    }

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
    replyGet->deleteLater();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();

    QString newestVersion = jsonObject["tag_name"].toString();

    if (newestVersion != appVersion && newestVersion != ""){

        searchVideoWindow::disableWidgets(true);

        QMessageBox msgBox;
        msgBox.setWindowTitle("Aktualizace");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Je dostupná novější verze y2mate desktop.\n\nDostupná verze: " + newestVersion + "\nVaše verze: " + appVersion  +"\n\nPři instalaci nové verze se předchozí automaticky odstraní.");

        QAbstractButton* pButtonYes = msgBox.addButton("  Nainstalovat  ", QMessageBox::YesRole);
        msgBox.addButton("Zrušit", QMessageBox::NoRole);

        downloadDialog dd(nullptr, true);
        dd.otherDownload = true;
        dd.downloadLink = QString("https://github.com/RxiPland/y2mate_desktop/releases/download/%1/y2mate_setup.exe").arg(newestVersion);
        dd.customFinishMessage = "Nainstalovat";
        dd.loadSettings();

        QDir downloadFolder(QDir::homePath() + "/Downloads/");
        QString folderPath;
        bool folderWarningRaised = false;

        while(true){
            msgBox.exec();

            if (msgBox.clickedButton() == pButtonYes) {
                // download & run newer version

                if(!downloadFolder.exists()){

                    if(!folderWarningRaised){
                        QMessageBox::warning(this, "Oznámení", "Nepodařilo se najít složku pro stahování! Vyberte, kam se má instalační soubor stáhnout (po instalaci může být soubor vymazán).");
                        folderWarningRaised = true;
                    }

                    // select new path for download
                    folderPath = QFileDialog::getExistingDirectory(this, "Vybrat složku pro stažení", lastSavePath);

                    if(folderPath.isEmpty()){
                        continue;
                    }
                } else{
                    folderPath = downloadFolder.path();
                }

                if(!folderPath.endsWith('/')){
                    folderPath.append('/');
                }

                dd.filePath = folderPath + "y2mate_setup.exe";
                dd.show();

                dd.startDownload();

                // wait for close
                while(!dd.closed){
                    qApp->processEvents();
                }

                // download was canceled or closed by X
                if(dd.canceled || !dd.closedWithButton){
                    break;

                } else{
                    // download was successfull
                    // run setup file

                    QProcess::startDetached(dd.filePath);
                    QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
                    return;
                }

            } else{
                // exit update

                break;
            }
        }
    }

    searchVideoWindow::disableWidgets(false);
}

void searchVideoWindow::disableWidgets(bool disable)
{
    ui->lineEdit->setDisabled(disable);
    ui->lineEdit->setClearButtonEnabled(!disable);
    ui->pushButton->setDisabled(disable);

    ui->menu_1->menuAction()->setDisabled(disable);
    ui->menu_2->menuAction()->setDisabled(disable);
    ui->menu_3->menuAction()->setDisabled(disable);
}

void searchVideoWindow::saveToHistory(QString videoName, QString videoDuration, QString videoUrl)
{
    // save searched video to settings file

    QFile dataFile(QDir::currentPath() + "/Data/data.json");

    if (dataFile.exists()){
        dataFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QByteArray fileContent = dataFile.readAll();
        dataFile.close();

        if(fileContent.isEmpty()){
            // File is empty

            QMessageBox::critical(this, "Chyba", "Soubor s nastavením je prázdný! Při příštím zapnutí programu bude problém vyřešen.");
            return;

        } else{
            QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

            if(loadedJson.isEmpty()){
                // JSON is corrupted

                QMessageBox::critical(this, "Chyba", "JSON v souboru s nastavením je poškozený! Při příštím zapnutí programu bude problém vyřešen.");
                return;

            } else{
                // make space for new record
                QJsonObject history = loadedJson["search_history"].toObject();

                if(history["1"].toObject()["video_url"] != videoUrl){

                    history["5"] = history["4"];
                    history["4"] = history["3"];
                    history["3"] = history["2"];
                    history["2"] = history["1"];

                    QJsonObject videoInfo;
                    videoInfo["video_name"] = videoName;
                    videoInfo["video_duration"] = videoDuration;
                    videoInfo["video_url"] = videoUrl;

                    history["1"] = videoInfo;
                    loadedJson["search_history"] = history;


                    QJsonDocument docData(loadedJson);

                    dataFile.open(QIODevice::WriteOnly | QIODevice::Text);
                    int status = dataFile.write(docData.toJson());
                    dataFile.close();

                    if (status == -1){
                        QMessageBox::critical(this, "Chyba", "Nastala neznámá chyba při zapisování do souboru s nastavením!\n\n" + dataFile.fileName());

                        return;
                    }
                }
            }
        }

    } else{
        // file with settings not found

        QMessageBox::critical(this, "Chyba", "Soubor s nastavením neexistuje! Při příštím zapnutí programu bude problém vyřešen.");
        return;
    }
}

void searchVideoWindow::savePath(QString path)
{
    // save path to settings

    QFile dataFile(QDir::currentPath() + "/Data/data.json");

    if (dataFile.exists()){
        dataFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QByteArray fileContent = dataFile.readAll();
        dataFile.close();

        if(fileContent.isEmpty()){
            // File is empty

            QMessageBox::critical(this, "Chyba", "Soubor s nastavením je prázdný! Program bude restartován pro opravu.");

            QProcess::startDetached(QApplication::applicationFilePath());

            QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
            return;

        } else{
            QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

            if(loadedJson.isEmpty()){
                // JSON is corrupted

                QMessageBox::critical(this, "Chyba", "JSON v souboru s nastavením je poškozený! Program bude restartován pro opravu.");

                QProcess::startDetached(QApplication::applicationFilePath());

                QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
                return;

            } else{

                path.replace('\\', '/');

                while(path.endsWith('/')){
                    QStringList temp;
                    temp = path.split('/');
                    temp.pop_back();
                    path = temp.join('/');
                }

                loadedJson["last_path"] = path;
                QJsonDocument docData(loadedJson);

                dataFile.open(QIODevice::WriteOnly | QIODevice::Text);
                int status = dataFile.write(docData.toJson());
                dataFile.close();

                if (status == -1){
                    QMessageBox::critical(this, "Chyba", "Nastala neznámá chyba při zapisování do souboru s nastavením!\n\n" + dataFile.fileName());

                    return;
                }

                if(lastPathEnabled){
                    lastSavePath = path;
                }
            }
        }

    } else{
        // file with settings not found

        QMessageBox::critical(this, "Chyba", "Soubor s nastavením neexistuje! Program bude restartován pro opravu.");

        QProcess::startDetached(QApplication::applicationFilePath());

        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
        return;
    }
}

QJsonObject searchVideoWindow::getVideoFromHistory(QString index)
{
    QFile dataFile(QDir::currentPath() + "/Data/data.json");

    if (dataFile.exists()){
        dataFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QByteArray fileContent = dataFile.readAll();
        dataFile.close();

        if(fileContent.isEmpty()){
            // File is empty

            QMessageBox::critical(this, "Chyba", "Soubor s nastavením je prázdný! Při příštím zapnutí programu bude problém vyřešen.");
            return QJsonObject();

        } else{
            QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

            if(loadedJson.isEmpty()){
                // JSON is corrupted

                QMessageBox::critical(this, "Chyba", "JSON v souboru s nastavením je poškozený! Při příštím zapnutí programu bude problém vyřešen.");
                return QJsonObject();

            } else{
                // read video info
                QJsonObject history = loadedJson["search_history"].toObject();

                return history[index].toObject();
            }
        }

    } else{
        // file with settings not found

        QMessageBox::critical(this, "Chyba", "Soubor s nastavením neexistuje! Při příštím zapnutí programu bude problém vyřešen.");
        return QJsonObject();
    }
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
    sd.exec();

    while(!sd.closed){
        qApp->processEvents();
    }

    searchVideoWindow::loadSettings();
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

        QMessageBox::critical(this, "Chyba", "Zadejte kompletní URL adresu!\n\nPř. https://www.youtube.com/watch?v=MNeX4EGtR5Y");

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

    if(error == QNetworkReply::HostNotFoundError || error == QNetworkReply::UnknownNetworkError){
        // no internet connection available

        disableWidgets(false);
        QMessageBox::critical(this, "Chyba", QString("Nelze se připojit k internetu nebo server (%1) není dostupný!").arg("y2mate.com"));
        return;

    } else if (error != QNetworkReply::NetworkError::NoError){
        // an unknown error occured

        disableWidgets(false);
        const QString &errorString = replyPost->errorString();
        QMessageBox::warning(this, "Chyba", QString("Nastala chyba při komunikaci s webem!\n\nChyba: %1").arg(errorString));
        return;
    }

    QByteArray response = replyPost->readAll();
    replyPost->deleteLater();

    QJsonObject loadedJson = QJsonDocument::fromJson(response).object();

    QString status = loadedJson["status"].toString().toLower();
    QString message = loadedJson["mess"].toString();


    if (status != "ok"){

        QMessageBox::warning(this, "Chyba", QString("Nastala chyba! y2mate vrátil:\n\n%1").arg(response));
        disableWidgets(false);
        return;

    } else if (message.contains("Please enter valid video URL.") || message.contains("Sorry! An error has occurred.")){

        QMessageBox::warning(this, "Chyba", "Video pod tímto odkazem neexistuje!");
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

    qint64 videoDuration = loadedJson["t"].toInt();
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
    videoName = videoName.trimmed();

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
    videoName = tempName.trimmed();

    // convert to %hh:%mm:%ss format
    int hours = videoDuration/(60*60);
    int minutes = (videoDuration/60)-(hours*60);
    int seconds = videoDuration-(hours*(60*60)+minutes*60);

    QString timeDuration;
    if(hours < 10){
        timeDuration.append('0');
    }
    timeDuration.append(QString("%1:").arg(hours));

    if (minutes < 10){
        timeDuration.append('0');
    }
    timeDuration.append(QString("%1:").arg(minutes));

    if (seconds < 10){
        timeDuration.append('0');
    }
    timeDuration.append(QString("%1").arg(seconds));


    // save to history if enabled
    if(searchVideoWindow::allowHistory){
        searchVideoWindow::saveToHistory(videoName, timeDuration, videoUrl);
    }

    downloadVideoWindow dvw(nullptr);
    dvw.ytChannel = ytChannel;
    dvw.videoDuration = videoDuration;
    dvw.videoName = videoName;
    dvw.videoID = videoId;
    dvw.videoUrl = videoUrl;

    dvw.mp3Qualities = mp3Qualities;
    dvw.mp4Qualities = mp4Qualities;

    this->hide();
    // set data to widgets
    dvw.loadData();

    // wait until closed
    while(!dvw.closed){
        qApp->processEvents();
    }

    // exit if pressed X
    if(dvw.exitApp){
        qApp->setQuitOnLastWindowClosed(true);
        this->close();
        return;
    }

    searchVideoWindow::loadSettings();

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
    QAbstractButton* pButtonYes = msgBox.addButton("Ano", QMessageBox::YesRole);
    msgBox.addButton("Zrušit", QMessageBox::YesRole);
    msgBox.exec();

    if (msgBox.clickedButton() != pButtonYes) {
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
            QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
            return;
        }

        QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

        if(loadedJson.isEmpty()){
            // JSON cannot be loaded

            QMessageBox::critical(this, "Chyba", "JSON v souboru s nastavením je poškozený! Program bude restartován pro opravu.");

            QProcess::startDetached(QApplication::applicationFilePath());
            QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
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
            QMessageBox::critical(this, "Chyba", "Nastala neznámá chyba při zapisování do souboru s nastavením!\n\n" + dataFile.fileName());

            return;
        }

        QMessageBox::information(this, "Oznámení", "Historie byla úspěšně smazána");

    } else{
        // file with settings not found

        QMessageBox::critical(this, "Chyba", "Soubor s nastavením neexistuje! Program bude restartován pro opravu.");

        QProcess::startDetached(QApplication::applicationFilePath());
        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
        return;
    }

    searchVideoWindow::loadSettings();
}

void searchVideoWindow::on_action_menu3_1_triggered()
{
    // open video/audio file for edit

    searchVideoWindow::disableWidgets();

    QString filePath;
    filePath = QFileDialog::getOpenFileName(this, "Otevřít soubor", lastSavePath, "Soubory (*.mp3 *.mp4 *.wav *.ogg *.flac);;Všechny soubory (*.*)").replace("\\", "/");

    if(filePath.isEmpty()){
        searchVideoWindow::disableWidgets(false);
        return;
    }

    QStringList validFileTypes = {".mp3", ".mp4", ".wav", ".ogg", ".flac"};
    QString fileType = '.' + filePath.split('.').last();

    if(!validFileTypes.contains(fileType)){
        // invalid file type

        QMessageBox::critical(this, "Chyba", QString("Koncovka %1 není v tuto chvíli podporována!").arg(fileType));
        searchVideoWindow::disableWidgets(false);
        return;
    }

    QLabel *label = new QLabel("Získávám délku videa ...   ");
    ui->statusBar->addWidget(label);

    // preparation for getting video duration
    QStringList arguments;
    arguments << "/C";
    arguments << "cd";
    arguments << "./Data";
    arguments << "&";
    arguments << "ffmpeg.exe";
    arguments << "-i";
    arguments << filePath;

    QProcess process;
    process.start("cmd.exe", QStringList(arguments));

    while(process.state() == QProcess::Running){
        qApp->processEvents();
    }
    ui->statusBar->removeWidget(label);

    // ffmpeg will make error output (because output is missing)
    QString processOutput = process.readAllStandardError();
    QRegExp re = QRegExp("Duration: (\\d+):(\\d+):(\\d+).(\\d+)");

    qint64 totalMiliSeconds = 0;

    // get duration
    if(re.indexIn(processOutput) != -1){
        totalMiliSeconds += re.cap(1).toInt() * 3600000;
        totalMiliSeconds += re.cap(2).toInt() * 60000;
        totalMiliSeconds += re.cap(3).toInt() * 1000;

        int miliSeconds = re.cap(4).toInt();

        while(miliSeconds<100 && miliSeconds != 0){
            miliSeconds *= 10;
        }
        totalMiliSeconds += miliSeconds;
    }

    if(totalMiliSeconds == 0){
        QMessageBox::critical(this, "Chyba", "Nastala neznámá chyba! Nepodařilo se získat délku videa!");
        searchVideoWindow::disableWidgets(false);
        return;
    }

    editVideoDialog evd;
    evd.startedFromSeachMenu = true;
    evd.filePath = filePath;
    evd.videoDurationMiliSec = totalMiliSeconds;
    evd.loadSettings();
    evd.loadData();

    // wait for close
    while(!evd.closed){
        qApp->processEvents();
    }

    if(evd.changed && lastPathEnabled){
        QStringList path = evd.originalPath.replace('\\', '/').split('/');
        path.pop_back();

        searchVideoWindow::savePath(path.join('/'));
    }

    if(evd.running){
        QFile::remove(evd.newFilePath);

        if(!evd.nameChanged && !evd.fileTypeChanged){
            QFile temp(evd.originalPath);
            temp.rename(evd.newFilePath);
        }
    }

    searchVideoWindow::disableWidgets(false);
}


void searchVideoWindow::on_action_menu_2_1_1_triggered()
{
    // #1 video - apply

    QJsonObject videoInfo = searchVideoWindow::getVideoFromHistory("1");

    ui->lineEdit->setText(videoInfo["video_url"].toString());
    searchVideoWindow::on_pushButton_clicked();
}


void searchVideoWindow::on_action_menu_2_1_2_triggered()
{
    // #1 video - open in browser

    QJsonObject videoInfo = searchVideoWindow::getVideoFromHistory("1");
    std::wstring videoUrl = videoInfo["video_url"].toString().toStdWString();

    ShellExecute(0, 0, videoUrl.c_str(), 0, 0, SW_HIDE);
}


void searchVideoWindow::on_action_menu_2_2_1_triggered()
{
    // #2 video - apply

    QJsonObject videoInfo = searchVideoWindow::getVideoFromHistory("2");

    ui->lineEdit->setText(videoInfo["video_url"].toString());
    searchVideoWindow::on_pushButton_clicked();
}

void searchVideoWindow::on_action_menu_2_2_2_triggered()
{
    // #2 video - open in browser

    QJsonObject videoInfo = searchVideoWindow::getVideoFromHistory("2");
    std::wstring videoUrl = videoInfo["video_url"].toString().toStdWString();

    ShellExecute(0, 0, videoUrl.c_str(), 0, 0, SW_HIDE);
}


void searchVideoWindow::on_action_menu_2_3_1_triggered()
{
    // #3 video - apply

    QJsonObject videoInfo = searchVideoWindow::getVideoFromHistory("3");

    ui->lineEdit->setText(videoInfo["video_url"].toString());
    searchVideoWindow::on_pushButton_clicked();
}


void searchVideoWindow::on_action_menu_2_3_2_triggered()
{
    // #3 video - open in browser

    QJsonObject videoInfo = searchVideoWindow::getVideoFromHistory("3");
    std::wstring videoUrl = videoInfo["video_url"].toString().toStdWString();

    ShellExecute(0, 0, videoUrl.c_str(), 0, 0, SW_HIDE);
}


void searchVideoWindow::on_action_menu_2_4_1_triggered()
{
    // #4 video - apply

    QJsonObject videoInfo = searchVideoWindow::getVideoFromHistory("4");

    ui->lineEdit->setText(videoInfo["video_url"].toString());
    searchVideoWindow::on_pushButton_clicked();
}


void searchVideoWindow::on_action_menu_2_4_2_triggered()
{
    // #4 video - open in browser

    QJsonObject videoInfo = searchVideoWindow::getVideoFromHistory("4");
    std::wstring videoUrl = videoInfo["video_url"].toString().toStdWString();

    ShellExecute(0, 0, videoUrl.c_str(), 0, 0, SW_HIDE);
}


void searchVideoWindow::on_action_menu_2_5_1_triggered()
{
    // #5 video - apply

    QJsonObject videoInfo = searchVideoWindow::getVideoFromHistory("5");

    ui->lineEdit->setText(videoInfo["video_url"].toString());
    searchVideoWindow::on_pushButton_clicked();
}


void searchVideoWindow::on_action_menu_2_5_2_triggered()
{
    // #5 video - open in browser

    QJsonObject videoInfo = searchVideoWindow::getVideoFromHistory("5");
    std::wstring videoUrl = videoInfo["video_url"].toString().toStdWString();

    ShellExecute(0, 0, videoUrl.c_str(), 0, 0, SW_HIDE);
}
