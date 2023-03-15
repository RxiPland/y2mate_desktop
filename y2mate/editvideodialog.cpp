#include "editvideodialog.h"
#include "ui_editvideodialog.h"

#include <QProcess>
#include <QCloseEvent>
#include <QTime>
#include <QMessageBox>
#include <QFile>
#include <QCryptographicHash>
#include <QUuid>


editVideoDialog::editVideoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editVideoDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowModality(Qt::ApplicationModal);

    this->show();
}

editVideoDialog::~editVideoDialog()
{
    delete ui;
}

void editVideoDialog::loadData()
{
    // load data to widgets

    QString fullVideoName = editVideoDialog::filePath.split('/').last();

    QStringList videoName = fullVideoName.split('.');
    videoName.pop_back();

    ui->lineEdit->setText(videoName.join('.'));
    ui->comboBox->setCurrentText('.' + fullVideoName.split('.').last());


    int hours = videoDuration/(60*60);
    int minutes = (videoDuration/60)-(hours*60);
    int seconds = videoDuration-(hours*(60*60)+minutes*60);

    ui->timeEdit->setMinimumTime(QTime(0,0,0,0));
    ui->timeEdit->setMaximumTime(QTime(hours, minutes, seconds));
    ui->timeEdit->setTime(QTime(0,0,0,0));

    ui->timeEdit_2->setMinimumTime(QTime(0,0,0,0));
    ui->timeEdit_2->setMaximumTime(QTime(hours, minutes, seconds));
    ui->timeEdit_2->setTime(QTime(hours, minutes, seconds));
}

void editVideoDialog::closeEvent(QCloseEvent *bar)
{
    // before close

    terminated = true;

    if(process.state() == QProcess::Running){
        QProcess::startDetached("cmd", QStringList("/C taskkill /IM ffmpeg.exe /F"));
        process.kill();
    }


    while(process.state() == QProcess::Running){
        qApp->processEvents();
    }

    this->close();

    if(bar != nullptr){
        bar->accept();
    }
}

void editVideoDialog::disableWidgets(bool disable)
{
    // disable widgets

    ui->comboBox->setDisabled(disable);
    ui->lineEdit->setDisabled(disable);
    ui->timeEdit->setDisabled(disable);
    ui->timeEdit_2->setDisabled(disable);
    ui->pushButton->setDisabled(disable);
    ui->pushButton_2->setDisabled(disable);
    ui->pushButton_3->setDisabled(disable);
}

void editVideoDialog::readyReadStandardOutput()
{
    // update progress bar

    processOutput = process.readAll();

    if(re.indexIn(processOutput) != -1){
        editVideoDialog::microSeconds = re.cap(1).trimmed().toInt();
        ui->progressBar->setValue(editVideoDialog::microSeconds);
    }
}

void editVideoDialog::finished()
{
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

        bool success = QFile::remove(editVideoDialog::filePath);

        if(success){
            QMessageBox::information(this, "Oznámení", "Video bylo úspěšně překonvertováno");

        } else{
            QMessageBox::warning(this, "Oznámení", "Video bylo úspěšně překonvertováno, ale nepovedlo se odstranit původní soubor:\n" + editVideoDialog::filePath);
        }

        running = false;

    } else{

        if(error.contains("is not recognized as an internal or external command")){
            QMessageBox::critical(this, "Chyba", "FFmpeg.exe nebyl nalezen! Reinstalujte program.");

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

    editVideoDialog::running = true;

    editVideoDialog::disableWidgets();

    QTime timeStart = ui->timeEdit->time();
    QTime timeEnd = ui->timeEdit_2->time();

    if (ui->lineEdit->text().isEmpty()){
        QMessageBox::warning(this, "Chyba", "Název nemůže být prázdný!");
        editVideoDialog::disableWidgets(false);
        return;

    } else if(timeStart > timeEnd){
        QMessageBox::warning(this, "Chyba", "Vybraný časový úsek není validní! Čas začátku nemůže být větší, jak čas konce.");
        editVideoDialog::disableWidgets(false);
        return;
    }


    qint64 totalMicroSecondsStart = 0;
    qint64 totalMicroSecondsEnd = 0;

    // start time
    totalMicroSecondsStart += timeStart.hour() * 3600000000;
    totalMicroSecondsStart += timeStart.minute() * 60000000;
    totalMicroSecondsStart += timeStart.second() * 1000000;
    totalMicroSecondsStart += timeStart.msec() * 1000;

    // end time
    totalMicroSecondsEnd += timeEnd.hour() * 3600000000;
    totalMicroSecondsEnd += timeEnd.minute() * 60000000;
    totalMicroSecondsEnd += timeEnd.second() * 1000000;
    totalMicroSecondsEnd += timeEnd.msec() * 1000;

    editVideoDialog::newVideoDuration = (totalMicroSecondsEnd - totalMicroSecondsStart)/1000000;

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(totalMicroSecondsEnd - totalMicroSecondsStart);
    ui->progressBar->setValue(0);


    int hours = videoDuration/(60*60);
    int minutes = (videoDuration/60)-(hours*60);
    int seconds = videoDuration-(hours*(60*60)+minutes*60);

    QString fullVideoName = editVideoDialog::filePath.split('/').last();
    QStringList videoNameTemp = fullVideoName.split('.');
    videoNameTemp.pop_back();

    // original
    editVideoDialog::originalPath = editVideoDialog::filePath;
    QString originalVideoName = videoNameTemp.join('.');
    QString originalVideoNameWithFileType = fullVideoName;
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
    bool endTimeChanged = ui->timeEdit_2->time() != QTime(hours, minutes, seconds);
    editVideoDialog::nameChanged = finalVideoName != originalVideoName;
    editVideoDialog::fileTypeChanged = finalFileType != originalFileType;

    if(!nameChanged && !startTimeChanged && !endTimeChanged && !fileTypeChanged){
        // nothing changed

        QMessageBox msgBox;
        msgBox.setWindowTitle("Upozornění");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Nebyly provedeny žádné změny. Chcete odejít?");
        msgBox.addButton(" Ano ", QMessageBox::YesRole);
        QAbstractButton* pButtonNo = msgBox.addButton(" Ne ", QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton() == pButtonNo){
            editVideoDialog::disableWidgets(false);
            return;

        } else{
            // exit

            this->close();
            return;
        }

    } else if (nameChanged && !startTimeChanged && !endTimeChanged && !fileTypeChanged){
        // only rename

        QFile videoFile = QFile(editVideoDialog::filePath);
        bool success = videoFile.rename(finalPath);

        if (success){
            QMessageBox::information(this, "Oznámení", "Soubor byl úspěšně přejmenován");
            editVideoDialog::newFilePath = finalPath;

            changed = true;

            this->close();
            return;

        } else{
            // file with this name may already exist

            if(videoFile.exists()){
                QMessageBox::warning(this, "Chyba", "Soubor s tímto názvem již ve složce existuje!");

            } else{
                QMessageBox::warning(this, "Chyba", "Nastala neznámá chyba! Nepodařilo se přejmenovat soubor");
            }

            return;
        }

    } else if (!nameChanged && !fileTypeChanged){
        // replace file

        // generate random name
        QByteArray random = QUuid::createUuid().toByteArray(QUuid::WithoutBraces);

        QCryptographicHash hash(QCryptographicHash::Md5);
        hash.addData(random);

        random = hash.result().toHex();

        QStringList tempPath = editVideoDialog::filePath.split('/');
        tempPath.pop_back();
        QString tempFilePath = tempPath.join('/') + '/' + random + originalFileType;

        QFile tempFile(originalPath);
        tempFile.rename(tempFilePath);

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
    arguments << "-nostats";
    arguments << "-loglevel";
    arguments << "error";
    arguments << "-i";
    arguments << originalPath;

    // put path for original file deletion
    editVideoDialog::filePath = originalPath;

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

    if(fileTypeChanged){
        QString currentFileType = ui->comboBox->currentText();

        if (currentFileType == ".ogg"){

            arguments << "-c:a";
            arguments << "libvorbis";

        } else if (currentFileType == ".mp4"){
            arguments << "-c:a";
            arguments << "libmp3lame";

        } else{
            arguments << "-c:a";
            arguments << "copy";
        }

    } else{
        arguments << "-c:a";
        arguments << "copy";
    }

    arguments << "-hide_banner";
    arguments << finalPath;

    editVideoDialog::newFilePath = finalPath;


    process.start("cmd.exe", QStringList(arguments));

    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finished()));
}

void editVideoDialog::on_lineEdit_returnPressed()
{
    // return pressed

    editVideoDialog::on_pushButton_3_clicked();
}

