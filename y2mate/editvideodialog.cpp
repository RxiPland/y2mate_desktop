#include "editvideodialog.h"
#include "ui_editvideodialog.h"

#include <QProcess>
#include <QCloseEvent>
#include <QTime>
#include <QMessageBox>
#include <QFile>


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

void editVideoDialog::readyReadStandardOutput()
{
    // update progress bar

    processOutput = process.readAll();

    if(re.indexIn(processOutput) != -1){
        editVideoDialog::microSeconds = re.cap(1).trimmed().toInt();
        ui->progressBar->setValue(editVideoDialog::microSeconds);
        qInfo() << microSeconds;
    }
}

void editVideoDialog::finished()
{
    // set progress bar to 100 %

    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(100);
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

    QTime timeStart = ui->timeEdit->time();
    QTime timeEnd = ui->timeEdit_2->time();

    if (ui->lineEdit->text().isEmpty()){
        QMessageBox::warning(this, "Chyba", "Název nemůže být prázdný!");
        return;

    } else if(timeStart > timeEnd){
        QMessageBox::warning(this, "Chyba", "Vybraný časový úsek není validní! Čas začátku nemůže být větší, jak čas konce.");
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

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(totalMicroSecondsEnd - totalMicroSecondsStart);
    ui->progressBar->setValue(0);


    int hours = videoDuration/(60*60);
    int minutes = (videoDuration/60)-(hours*60);
    int seconds = videoDuration-(hours*(60*60)+minutes*60);

    QString fullVideoName = editVideoDialog::filePath.split('/').last();
    QStringList videoNameTemp = fullVideoName.split('.');
    videoNameTemp.pop_back();
    QString videoName = videoNameTemp.join('.');

    // bool variables
    bool startTimeChanged = ui->timeEdit->time() != QTime(hours, minutes, seconds);
    bool endTimeChanged = ui->timeEdit->time() != QTime(hours, minutes, seconds);
    bool nameChanged = ui->lineEdit->text().trimmed() != videoName;
    bool formatChanged = ui->comboBox->currentText() != '.' + videoNameTemp.last();


    if(!nameChanged && !startTimeChanged && !endTimeChanged && !formatChanged){
        // nothing changed

        QMessageBox msgBox;
        msgBox.setWindowTitle("Upozornění");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Nebyly provedeny žádné změny. Chcete odejít?");
        msgBox.addButton(" Ano ", QMessageBox::YesRole);
        QAbstractButton* pButtonNo = msgBox.addButton(" Ne ", QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton() == pButtonNo){
            return;

        } else{
            // exit

            this->close();
            return;
        }

    } else if (nameChanged && !startTimeChanged && !endTimeChanged && !formatChanged){
        // only rename

        QFile videoFile = QFile(editVideoDialog::filePath);

        bool success = videoFile.rename(ui->lineEdit->text().trimmed());

        if (success){
            QMessageBox::information(this, "Oznámení", "Soubor byl úspěšně přejmenován");

            converted = true;

            this->close();
            return;

        } else{
            QMessageBox::warning(this, "Chyba", "Nastala neznámá chyba! Nepodařilo se přejmenovat soubor");
            return;
        }
    }

    // preparation for convert

    QString command = "/C cd ./Data & ffmpeg.exe -y -progress - -nostats -loglevel error -i ";
    command += '\"' + editVideoDialog::filePath + '\"' + ' ';

    if(startTimeChanged){
        // add start time

        QString startTime = timeStart.toString("HH:mm:ss.zzz");
        command += QString("-ss %1 ").arg(startTime);
    }

    if(endTimeChanged){
        // add end time

        QString endTime = timeEnd.toString("HH:mm:ss.zzz");
        command += QString("-to %1 ").arg(endTime);
    }

    // command += "-c:a copy ";



    // filename + format (.mp4 / .mp3 ...)
    command += ui->lineEdit->text().trimmed() + ui->comboBox->currentText();




    process.start("cmd", QStringList(command));

    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finished()));
}
