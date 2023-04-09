#include "downloaddialog.h"
#include "ui_downloaddialog.h"
#include "editvideodialog.h"

#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <windows.h>
#include <QClipboard>
#include <QCloseEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSoundEffect>
#include <QApplication>


downloadDialog::downloadDialog(QWidget *parent, bool hidden, QString fileName) :
    QDialog(parent),
    ui(new Ui::downloadDialog)
{
    ui->setupUi(this);

    ui->label_2->setText(fileName);

    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowFlags(windowFlags() &(~Qt::WindowMinimizeButtonHint));
    this->setWindowFlags(windowFlags() &(~Qt::WindowMaximizeButtonHint));

    this->setWindowModality(Qt::ApplicationModal);

    if(!hidden){
        this->show();
    }
}

downloadDialog::~downloadDialog()
{
    delete ui;
}

void downloadDialog::startDownload()
{
    if(!showDownloadUrlButton){
        ui->pushButton_5->setHidden(true);
    }

    downloadDialog::running = true;

    if(otherDownload){
        ui->pushButton_2->setHidden(true);
        ui->pushButton_4->setHidden(true);
    }


    ui->label_2->setText(downloadDialog::filePath.split('/').last());

    file = openFileForWrite(downloadDialog::filePath);
    if (!file){
        QMessageBox::critical(this, "Problém", "Nastal problém při otevírání souboru.\n\n" + downloadDialog::filePath);

        downloadDialog::running = false;
        return;
    }

    QNetworkRequest request;
    request.setUrl(QUrl(downloadDialog::downloadLink));
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);

    if(!otherDownload){
        request.setRawHeader("Referer", "https://www.y2mate.com/");
    }

    reply.reset(manager.get(request));

    connect(reply.get(), &QNetworkReply::finished, this, &downloadDialog::httpFinished);
    connect(reply.get(), &QIODevice::readyRead, this, &downloadDialog::httpReadyRead);
    connect(reply.get(), &QNetworkReply::downloadProgress,this, &downloadDialog::downloadProgress);
}

bool downloadDialog::loadSettings()
{
    // load settings to variables

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
            return false;

        } else{
            QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

            if(loadedJson.isEmpty()){
                // JSON is corrupted

                QMessageBox::critical(this, "Chyba", "JSON v souboru s nastavením je poškozený! Program bude restartován pro opravu.");

                QProcess::startDetached(QApplication::applicationFilePath());
                QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
                return false;

            } else{
                // everything OK

                downloadDialog::userAgent = loadedJson["user_agent"].toString().toUtf8();
                downloadDialog::showDownloadUrlButton = loadedJson["show_download_url_button"].toBool();
                downloadDialog::downloadFinishedSound = loadedJson["download_finished_sound"].toBool();

                return true;
            }
        }

    } else{
        // file with settings not found

        QMessageBox::critical(this, "Chyba", "Soubor s nastavením neexistuje! Program bude restartován pro opravu.");

        QProcess::startDetached(QApplication::applicationFilePath());
        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
        return false;
    }
}

void downloadDialog::on_pushButton_clicked()
{
    // cancel or complete download button

    QString buttonText = ui->pushButton->text();

    if(!buttonText.contains("Zrušit")){
        // everything OK

        downloadDialog::closedWithButton = true;

    } else{
        downloadDialog::canceled = true;

        if(!reply.isNull()){
            reply->close();
            reply->deleteLater();
        }
    }

    running = false;
    this->close();
}

void downloadDialog::httpReadyRead()
{
    // This slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if(file){
        file->write(reply->readAll());
    }
}

void downloadDialog::httpFinished()
{
    // http request was finished

    QEventLoop loop;

    QFileInfo fi;
    if (file){
        fi.setFile(file->fileName());
        file->close();
        file->deleteLater();
        file.reset();
    }

    QNetworkReply::NetworkError error = reply->error();
    const QString &errorString = reply->errorString();

    reply.reset();
    reply->deleteLater();

    if (error != QNetworkReply::NoError){

        if(!canceled){

            if(errorString == "Connection closed"){
                QMessageBox::critical(this, "Chyba", "Stahování bylo zrušeno, protože se nelze připojit k síti!");

            } else{
                QMessageBox::critical(this, "Chyba", "Nastala chyba při stahování souboru! Chyba: " + errorString);
            }
        }
        QFile::remove(fi.absoluteFilePath());

        if(!canceled){
            downloadDialog::on_pushButton_clicked();
        }

        return;
    }

    this->setWindowTitle("Stahování - dokončeno");

    if(customFinishMessage.isEmpty()){
        ui->pushButton->setText("Hotovo");

    } else{
        ui->pushButton->setText(customFinishMessage);
    }

    if(!otherDownload){
        ui->pushButton_2->setDisabled(false);
        ui->pushButton_4->setDisabled(false);
    }


    // play sound if enabled
    if(downloadFinishedSound && canceled != true){

        QFile soundFile = QDir::currentPath() + "/Data/notification_sound.wav";

        if(soundFile.exists()){

            // load sound
            QSoundEffect effect;
            effect.setSource(QUrl::fromLocalFile(soundFile.fileName()));
            effect.setVolume(0.5f);

            // wait for loaded
            if(!effect.isLoaded()){
                QMetaObject::Connection loadedConn = QObject::connect(&effect, SIGNAL(loadedChanged()), &loop, SLOT(quit()));
                loop.exec();

                QObject::disconnect(loadedConn);
            }

            // play sound
            effect.play();

            // wait for played
            if(!effect.isPlaying()){
                QMetaObject::Connection playedConn = connect(&effect, SIGNAL(playingChanged()), &loop, SLOT(quit()));
                loop.exec();

                QObject::disconnect(playedConn);
            }
        }
    }

    downloadDialog::running = false;
}

void downloadDialog::downloadProgress(qint64 ist, qint64 max)
{
    // set progress to progress bar

    ui->progressBar->setRange(0,max);
    ui->progressBar->setValue(ist);

    ui->label->setText(QString::number(ist/1000000) + "." + QString::number(ist/100000).back() + " / " + QString::number(max/1000000) + "." + QString::number(max/100000).back() + " MB");
}

std::unique_ptr<QFile> downloadDialog::openFileForWrite(const QString &fileName)
{
    // open file

    std::unique_ptr<QFile> file = std::make_unique<QFile>(fileName);

    file->open(QIODevice::WriteOnly);

    return file;
}

void downloadDialog::closeEvent(QCloseEvent *bar)
{
    if(downloadDialog::running && !downloadDialog::canceled){

        if(bar != nullptr){
            bar->ignore();
        }
        return;
    }


    if(bar != nullptr){
        bar->accept();
        emit closed();
    }
}

void downloadDialog::on_pushButton_2_clicked()
{
    // open downloaded file

    ShellExecute(0, L"open", filePath.toStdWString().c_str(), 0, 0, SW_RESTORE);

    if(ui->pushButton->text() == "Hotovo"){
        downloadDialog::on_pushButton_clicked();
    }
}

void downloadDialog::on_pushButton_3_clicked()
{
    // open folder with downloaded file

    QString path = filePath;
    path.replace('/', '\\');

    QString folderPathCommand = "/select, \"" + path + "\"";

    ShellExecute(0, L"open", L"explorer.exe", folderPathCommand.toStdWString().c_str(), 0, SW_RESTORE);

    if(ui->pushButton->text() == "Hotovo"){
        downloadDialog::on_pushButton_clicked();
    }
}

void downloadDialog::on_pushButton_4_clicked()
{
    // edit video button

    if(!ffmpegExists()){
        running = false;
        return;
    }

    editVideoDialog evd(nullptr, true);
    evd.filePath = downloadDialog::filePath;
    evd.videoDurationMiliSec = downloadDialog::videoDurationMiliSec;

    bool loaded = evd.loadSettings();
    if (!loaded){
        running = false;
        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
        return;

    } else{
        evd.show();
    }

    this->hide();
    evd.loadData();

    // wait for close
    QEventLoop loop;
    QMetaObject::Connection closedConn = QObject::connect(&evd, SIGNAL(closed()), &loop, SLOT(quit()));
    loop.exec();

    QObject::disconnect(closedConn);

    // rename back and delete temp if canceled
    if(evd.running){
        QFile::remove(evd.newFilePath);

        if(!evd.nameChanged && !evd.fileTypeChanged){
            QFile temp(evd.originalPath);
            temp.rename(evd.newFilePath);
        }
    }

    // update label & disable further editing
    if(evd.changed){
        downloadDialog::filePath = evd.newFilePath;
        downloadDialog::videoDurationMiliSec = evd.newVideoDurationMiliSec;
        ui->label_2->setText(evd.newFilePath.split('/').last());
        ui->pushButton_4->setDisabled(true);
    }

    this->show();
}

void downloadDialog::on_pushButton_5_clicked()
{
    // show URL of downloaded file

    QMessageBox msgBox;
    msgBox.setWindowTitle("Odkaz stahovaného souboru");

    QString formatedDownloadLink;
    int i;

    // add every 60th character new line
    for(i=0; i<downloadDialog::downloadLink.length(); i++){

        if(i % 60 == 0){
            formatedDownloadLink.append("\n");
        }
        formatedDownloadLink.append(downloadLink[i]);
    }

    msgBox.setText(formatedDownloadLink);
    QAbstractButton* pButtonCopy = msgBox.addButton(" Kopírovat ", QMessageBox::NoRole);
    QAbstractButton* pButtonOk = msgBox.addButton(" Ok ", QMessageBox::NoRole);

    pButtonCopy->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    pButtonOk->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    msgBox.exec();

    if (msgBox.clickedButton() == pButtonCopy){
        // copy to clipboard

        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setText(downloadDialog::downloadLink);
    }
}

bool downloadDialog::ffmpegExists()
{

    QString ffmpegPath = QDir::currentPath() + "/Data/ffmpeg.exe";

    if (QFile::exists(ffmpegPath)){
        // OK
        return true;

    } else{
        QMessageBox msgBox;
        msgBox.setWindowTitle("Upozornění");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Program FFmpeg.exe pro úpravu videí nebyl nalezen. Chcete jej stáhnout?");
        QAbstractButton* pButtonYes = msgBox.addButton(" Ano ", QMessageBox::YesRole);
        msgBox.addButton(" Odejít ", QMessageBox::YesRole);
        msgBox.exec();

        if (msgBox.clickedButton() != pButtonYes){
            // exit / cancel
            return false;
        }

        // open download dialog
        downloadDialog dd(nullptr, true);
        dd.otherDownload = true;
        dd.downloadLink = "https://github.com/RxiPland/y2mate_desktop/releases/download/v1.8.0/ffmpeg.exe";
        dd.filePath = ffmpegPath;

        bool loaded = dd.loadSettings();
        if (!loaded){
            running = false;
            return false;

        } else{
            this->hide();
            dd.show();
        }

        dd.startDownload();

        // wait for close
        QEventLoop loop;
        QMetaObject::Connection closedConn = QObject::connect(&dd, SIGNAL(closed()), &loop, SLOT(quit()));
        loop.exec();

        QObject::disconnect(closedConn);

        this->show();

        // download was canceled
        if(dd.canceled){
           return false;

        } else{
            return true;
        }
    }

    return false;
}

