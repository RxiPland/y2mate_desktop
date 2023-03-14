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

    outTimeMs = process.readAll();

    if(re.indexIn(outTimeMs) != -1){
        qInfo() << re.cap(1).trimmed();
    }
}

void editVideoDialog::startEdit()
{
    // start process

    process.start("cmd", QStringList("/C ffmpeg.exe -y -progress - -nostats -loglevel error -i test.mp4 -ss 0:0:0 -to 0:1:10 test2.mp4"));

    connect(&process,SIGNAL(readyReadStandardOutput()),this,SLOT(readyReadStandardOutput()));
}

