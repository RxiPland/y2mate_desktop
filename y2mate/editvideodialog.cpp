#include "editvideodialog.h"
#include "ui_editvideodialog.h"

#include <QProcess>
#include <QCloseEvent>
#include <QTime>
#include <QMessageBox>


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

    } else if(timeStart > timeEnd){
        QMessageBox::warning(this, "Chyba", "Vybraný časový úsek není validní! Nemůže být čas začátku větší, jak čas konce");
    }

    return;

    editVideoDialog::startHours = timeStart.hour();
    editVideoDialog::startMinutes = timeStart.minute();
    editVideoDialog::startSeconds = timeStart.second();

    editVideoDialog::endHours = timeEnd.hour();
    editVideoDialog::endMinutes = timeEnd.minute();
    editVideoDialog::endSeconds = timeEnd.second();


    qint64 totalMicroSecondsStart = 0;
    qint64 totalMicroSecondsEnd = 0;

    // start time
    totalMicroSecondsStart += editVideoDialog::startHours * 3600000000;
    totalMicroSecondsStart += editVideoDialog::startMinutes * 60000000;
    totalMicroSecondsStart += editVideoDialog::startSeconds * 1000000;

    // end time
    totalMicroSecondsEnd += editVideoDialog::endHours * 3600000000;
    totalMicroSecondsEnd += editVideoDialog::endMinutes * 60000000;
    totalMicroSecondsEnd += editVideoDialog::endSeconds * 1000000;

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(totalMicroSecondsEnd - totalMicroSecondsStart);
    ui->progressBar->setValue(0);


    QString startTime = QString("%1:%2:%3").arg(QString::number(startHours), QString::number(startMinutes), QString::number(startSeconds));
    QString endTime = QString("%1:%2:%3").arg(QString::number(endHours), QString::number(endMinutes), QString::number(endSeconds));

    QString command = QString("/C ffmpeg.exe -y -progress - -nostats -loglevel error -i test.mp4 -ss %1 -to %2 test2.mp4").arg(startTime, endTime);

    process.start("cmd", QStringList(command));

    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finished()));
}
