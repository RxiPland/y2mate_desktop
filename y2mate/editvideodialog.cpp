#include "editvideodialog.h"
#include "ui_editvideodialog.h"

#include <QProcess>
#include <QCloseEvent>
#include <QThread>

editVideoDialog::editVideoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editVideoDialog)
{
    ui->setupUi(this);
    this->show();
}

editVideoDialog::~editVideoDialog()
{
    delete ui;
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
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(100);
}

void editVideoDialog::startEdit()
{
    // start process

    qint64 totalMicrosecondsStart = 0;
    qint64 totalMicrosecondsEnd = 0;

    // start time
    int startHours = 0;
    totalMicrosecondsStart += startHours * 3600000000;

    int startMinutes = 0;
    totalMicrosecondsStart += startMinutes * 60000000;

    float startSeconds = 0.0;
    totalMicrosecondsStart += startSeconds * 1000000;

    // end time
    int endHours = 0;
    totalMicrosecondsEnd += endHours * 3600000000;

    int endMinutes = 1;
    totalMicrosecondsEnd += endMinutes * 60000000;

    float endSeconds = 1.5;
    totalMicrosecondsEnd += endMinutes * 1000000;


    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(totalMicrosecondsEnd - totalMicrosecondsStart);


    QString startTime = QString("%1:%2:%3").arg(QString::number(startHours), QString::number(startMinutes), QString::number(startSeconds));
    QString endTime = QString("%1:%2:%3").arg(QString::number(endHours), QString::number(endMinutes), QString::number(endSeconds));

    QString command = QString("/C ffmpeg.exe -y -progress - -nostats -loglevel error -i test.mp4 -ss %1 -to %2 test2.mp4").arg(startTime, endTime);

    process.start("cmd", QStringList(command));

    connect(&process, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finished()));
}

