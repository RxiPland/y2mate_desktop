#include "editvideodialog.h"
#include "ui_editvideodialog.h"
#include "downloaddialog.h"

#include <QProcess>
#include <QCloseEvent>
#include <QTime>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QCryptographicHash>
#include <QUuid>
#include <QJsonDocument>
#include <QJsonObject>
#include <QApplication>
#include <QTimer>


editVideoDialog::editVideoDialog(QWidget *parent, bool hidden) :
    QDialog(parent),
    ui(new Ui::editVideoDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowModality(Qt::ApplicationModal);

    ui->comboBox->setDuplicatesEnabled(false);

    if(!hidden){
        this->show();
    }
}

editVideoDialog::~editVideoDialog()
{
    delete ui;
}

void editVideoDialog::loadData()
{
    // load data to widgets and check for program if downloaded

    editVideoDialog::disableWidgets();
    if(!editVideoDialog::ffmpegExists()){
        this->close();
        return;
    }

    editVideoDialog::disableWidgets(false);


    QString fullVideoName = editVideoDialog::filePath.split('/').last();

    QStringList videoName = fullVideoName.split('.');
    videoName.pop_back();

    ui->lineEdit->setText(videoName.join('.'));

    QString fileType = '.' + fullVideoName.split('.').last();

    // allow only (audio -> audio) && (video -> video | audio) conversion
    if(fileType == ".mp4" && !dataLoaded){
        ui->comboBox->insertItem(1, ".mp4");
        dataLoaded = true;
    }

    ui->comboBox->setCurrentText(fileType);


    ui->timeEdit->setMinimumTime(QTime(0,0,0,0));
    ui->timeEdit->setMaximumTime(QTime(0,0,0,0).addMSecs(videoDurationMiliSec));
    ui->timeEdit->setTime(QTime(0,0,0,0));

    ui->timeEdit_2->setMinimumTime(QTime(0,0,0,0));
    ui->timeEdit_2->setMaximumTime(QTime(0,0,0,0).addMSecs(videoDurationMiliSec));
    ui->timeEdit_2->setTime(QTime(0,0,0,0).addMSecs(videoDurationMiliSec));
}

bool editVideoDialog::loadSettings()
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

                editVideoDialog::userAgent = loadedJson["user_agent"].toString().toUtf8();
                editVideoDialog::showDownloadUrlButton = loadedJson["show_download_url_button"].toBool();
            }
        }

    } else{
        // file with settings not found

        QMessageBox::critical(this, "Chyba", "Soubor s nastavením neexistuje! Program bude restartován pro opravu.");

        QProcess::startDetached(QApplication::applicationFilePath());
        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);

        return false;
    }

    return true;
}

void editVideoDialog::closeEvent(QCloseEvent *bar)
{
    // before close

    /*
    if(editVideoDialog::running){

        if(bar != nullptr){
            bar->ignore();
        }
        return;
    }
    */

    QEventLoop loop;
    terminated = true;

    if(process.state() == QProcess::Running){
        QProcess::startDetached("cmd", QStringList("/C taskkill /IM ffmpeg.exe /F"));
        process.kill();

        // wait for finished
        if(process.state() == QProcess::Running){
            QMetaObject::Connection finishedConn = QObject::connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)), &loop, SLOT(quit()));
            loop.exec();

            QObject::disconnect(finishedConn);
        }
    }

    if(bar != nullptr){
        bar->accept();
        emit closed();
    }
}

void editVideoDialog::disableWidgets(bool disable)
{
    // disable widgets

    editVideoDialog::running = disable;

    ui->comboBox->setDisabled(disable);
    ui->lineEdit->setDisabled(disable);
    ui->timeEdit->setDisabled(disable);
    ui->timeEdit_2->setDisabled(disable);
    ui->pushButton->setDisabled(disable);
    ui->pushButton_2->setDisabled(disable);
    ui->pushButton_3->setDisabled(disable);

    QTimer::singleShot(800, this, SLOT(update()));
}

bool editVideoDialog::ffmpegExists()
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
            dd.show();
        }

        dd.startDownload();

        // wait for close
        QEventLoop loop;
        QMetaObject::Connection closedConn = QObject::connect(&dd, SIGNAL(closed()), &loop, SLOT(quit()));
        loop.exec();

        QObject::disconnect(closedConn);

        // download was canceled
        if(dd.canceled){
           return false;

        } else{
            return true;
        }
    }

    return false;
}

void editVideoDialog::readyReadStandardOutput()
{
    // update progress bar

    processOutput = process.readAll();

    if(re.indexIn(processOutput) != -1){

        QString microSeconds = re.cap(1).trimmed();

        if(!microSeconds.isEmpty()){
            ui->progressBar->setValue(microSeconds.toULongLong() / 1000000);
        }

    }
}

void editVideoDialog::finished()
{
    // conversion was finished / interrupted

    if (terminated){
        QMessageBox::warning(this, "Oznámení", "Operace byla zrušena uživatelem!");
        return;
    }

    // set progress bar to 100 %
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(100);

    QString error = process.readAllStandardError();

    if(error.isEmpty()){
        changed = true;

        bool success = true;

        // keep or delete original file
        if(deleteOriginalFile){
            success = QFile::remove(editVideoDialog::filePath);
        }

        if(success){
            QMessageBox::information(this, "Oznámení", "Video bylo úspěšně překonvertováno");

        } else{
            QMessageBox::warning(this, "Oznámení", "Video bylo úspěšně překonvertováno, ale nepovedlo se odstranit původní soubor:\n" + editVideoDialog::filePath);
        }

        running = false;

    } else{

        if(error.contains("is not recognized as an internal or external command")){
            QMessageBox::critical(this, "Chyba", "FFmpeg.exe nebyl nalezen! Restartujte aplikaci.\n\nPředpokládané umístění:\n" + QDir::currentPath() + "/Data/ffmpeg.exe");

        } else{
            QMessageBox::critical(this, "Chyba", "Video se nepodařilo konvertovat. FFmpeg vrátil:\n\n" + error);
        }
        ui->progressBar->setValue(0);
    }


    this->close();
}

void editVideoDialog::on_pushButton_clicked()
{
    // reset values

    editVideoDialog::loadData();
}

void editVideoDialog::on_pushButton_2_clicked()
{
    // exit

    this->close();
}

void editVideoDialog::on_pushButton_3_clicked()
{
    // start ffpmeg.exe

    editVideoDialog::disableWidgets();

    QTime timeStart = ui->timeEdit->time();
    QTime timeEnd = ui->timeEdit_2->time();

    if (ui->lineEdit->text().isEmpty()){
        QMessageBox::warning(this, "Chyba", "Název nemůže být prázdný!");
        editVideoDialog::disableWidgets(false);
        return;

    } else if(timeStart >= timeEnd){
        QMessageBox::warning(this, "Chyba", "Vybraný časový úsek není validní! Čas začátku nemůže být větší nebo roven času konce!");
        editVideoDialog::disableWidgets(false);
        return;
    }


    quint64 totalMiliSecondsStart = 0;
    quint64 totalMiliSecondsEnd = 0;

    // start time
    totalMiliSecondsStart += timeStart.hour() * 3600000;
    totalMiliSecondsStart += timeStart.minute() * 60000;
    totalMiliSecondsStart += timeStart.second() * 1000;
    totalMiliSecondsStart += timeStart.msec();


    // end time
    totalMiliSecondsEnd += timeEnd.hour() * 3600000;
    totalMiliSecondsEnd += timeEnd.minute() * 60000;
    totalMiliSecondsEnd += timeEnd.second() * 1000;
    totalMiliSecondsEnd += timeEnd.msec();

    editVideoDialog::newVideoDurationMiliSec = totalMiliSecondsEnd - totalMiliSecondsStart;

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum((totalMiliSecondsEnd - totalMiliSecondsStart)/1000);
    ui->progressBar->setValue(0);


    QString fullVideoName = editVideoDialog::filePath.split('/').last();
    QStringList videoNameTemp = fullVideoName.split('.');
    videoNameTemp.pop_back();

    // original
    editVideoDialog::originalPath = editVideoDialog::filePath;
    QString originalVideoName = videoNameTemp.join('.');
    //QString originalVideoNameWithFileType = fullVideoName;
    QString originalFileType = '.' + editVideoDialog::filePath.split('.').last();

    // final
    QString finalVideoName = ui->lineEdit->text().trimmed();
    QString finalFileType = ui->comboBox->currentText();
    QString finalVideoNameWithFileType = finalVideoName + finalFileType;

    QStringList temp = editVideoDialog::filePath.split('/');
    temp.pop_back();
    QString finalPath = temp.join('/') + '/' + finalVideoNameWithFileType;


    // bool variables
    bool startTimeChanged = ui->timeEdit->time() != QTime(0,0,0,0);
    bool endTimeChanged = ui->timeEdit_2->time() != QTime(QTime(0,0,0,0).addMSecs(videoDurationMiliSec));
    editVideoDialog::nameChanged = finalVideoName != originalVideoName;
    editVideoDialog::fileTypeChanged = finalFileType != originalFileType;

    if(!nameChanged && !startTimeChanged && !endTimeChanged && !fileTypeChanged){
        // nothing changed

        QMessageBox msgBox;
        msgBox.setWindowTitle("Upozornění");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Nebyly provedeny žádné změny. Chcete odejít?");
        QAbstractButton* pButtonYes = msgBox.addButton(" Ano ", QMessageBox::YesRole);
        msgBox.addButton(" Ne ", QMessageBox::YesRole);
        msgBox.exec();

        if(msgBox.clickedButton() == pButtonYes){
            this->close();
            return;

        } else{
            editVideoDialog::disableWidgets(false);
            return;
        }

    } else if (nameChanged && !startTimeChanged && !endTimeChanged && !fileTypeChanged){
        // only rename

        QFile videoFile = QFile(editVideoDialog::filePath);
        bool success = videoFile.rename(finalPath);

        if (success){
            QMessageBox::information(this, "Oznámení", "Soubor byl úspěšně přejmenován");
            editVideoDialog::newFilePath = finalPath;

            deleteOriginalFile = false;
            changed = true;
            running = false;

            this->close();
            return;

        } else{
            // file with this name may already exist

            if(QFile(newFilePath).exists()){
                QMessageBox::warning(this, "Chyba", "Soubor s tímto názvem již ve složce existuje!");

            } else{
                QMessageBox::warning(this, "Chyba", "Kvůli neznámé chybě se soubor nepodařilo přejmenovat! Možná je soubor využíván jiným programem.");
            }

            editVideoDialog::disableWidgets(false);
            return;
        }
    }


    // ask if an original file can be kept
    if(editVideoDialog::startedFromSeachMenu){

        QMessageBox msgBox;
        msgBox.setWindowTitle("Oznámení");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Chcete ponechat původní soubor?");
        QAbstractButton* pButtonYes = msgBox.addButton(" Ano ", QMessageBox::YesRole);
        msgBox.addButton(" Ne ", QMessageBox::YesRole);
        msgBox.exec();

        if (msgBox.clickedButton() == pButtonYes){

            bool exists = QFile(finalPath).exists();

            if((originalVideoName == finalVideoName) && !fileTypeChanged){
                QMessageBox::warning(this, "Chyba", "Pokud chcete ponechat původní soubor, tak název nemůže být stejný!");
                editVideoDialog::disableWidgets(false);
                return;

            } else if(exists){
                QMessageBox::warning(this, "Chyba", "Soubor s tímto názvem již ve složce existuje!");
                editVideoDialog::disableWidgets(false);
                return;
            }
            deleteOriginalFile = false;
        }
    }

    editVideoDialog::running = true;

    if (!nameChanged && !fileTypeChanged){
        // replace file

        // generate random temp name
        QByteArray random = QUuid::createUuid().toByteArray(QUuid::WithoutBraces);

        QCryptographicHash hash(QCryptographicHash::Md5);
        hash.addData(random);

        random = hash.result().toHex();

        QStringList tempPath = editVideoDialog::filePath.split('/');
        tempPath.pop_back();
        QString tempFilePath = tempPath.join('/') + '/' + random + originalFileType;

        QFile tempFile(originalPath);
        bool renamed = tempFile.rename(tempFilePath);

        if(!renamed){
            QMessageBox::warning(this, "Chyba", "Soubor je pravděpodobně otevřen v jiném programu a nelze ho přejmenovat!");
            editVideoDialog::disableWidgets(false);
            return;
        }

        originalPath = tempFilePath;
    }

    QFile videoFile(finalPath);
    // file with this name may already exist
    if(videoFile.exists()){
        QMessageBox::warning(this, "Chyba", "Soubor s tímto názvem již ve složce existuje!");
        editVideoDialog::disableWidgets(false);
        return;
    }

    // preparation for convert
    QStringList arguments;
    arguments << "/C";
    arguments << "cd";
    arguments << "./Data";
    arguments << "&";
    arguments << "ffmpeg.exe";
    arguments << "-y";
    arguments << "-progress";
    arguments << "-";
    arguments << "-stats_period";
    arguments << "0.3";
    arguments << "-nostats";
    arguments << "-loglevel";
    arguments << "fatal";

    if(startTimeChanged){
        // add start time

        QString startTime = timeStart.toString("HH:mm:ss.zzz");
        arguments << "-ss";
        arguments << startTime;
    }

    if(endTimeChanged){
        // add end time

        QString endTime = timeEnd.toString("HH:mm:ss.zzz");
        arguments << "-to";
        arguments << endTime;
    }

    // add input file
    arguments << "-i";
    arguments << originalPath;

    // put path for original file deletion
    editVideoDialog::filePath = originalPath;


    if(finalFileType == ".mp4"){

        // nothing (reencode everything)

    } else{

        // take "only" audio
        arguments << "-map";
        arguments << "a";
    }

    // add destination (path + name + filetype)
    arguments << finalPath;

    editVideoDialog::newFilePath = finalPath;


    // start conversion
    process.start("cmd.exe", QStringList(arguments));

    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finished()));
}

void editVideoDialog::on_lineEdit_returnPressed()
{
    // return pressed

    editVideoDialog::on_pushButton_3_clicked();
}

