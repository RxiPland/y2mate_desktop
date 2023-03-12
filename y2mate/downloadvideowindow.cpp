#include "downloadvideowindow.h"
#include "ui_downloadvideowindow.h"

downloadVideoWindow::downloadVideoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::downloadVideoWindow)
{
    ui->setupUi(this);
}

downloadVideoWindow::~downloadVideoWindow()
{
    delete ui;
}

void downloadVideoWindow::loadData()
{
    // set data to widgets

    ui->lineEdit->setText(downloadVideoWindow::videoUrl);
    ui->label->setText(QString("Název: %1").arg(downloadVideoWindow::videoName));

    int hours = videoDuration/(60*60);
    int minutes = (videoDuration/60)-(hours*60);
    int seconds = videoDuration-(hours*(60*60)+minutes*60);

    QString timeDuration;

    /*
    if(hours != 0){
        timeDuration.append(QString("%1h ").arg(hours));
        timeDuration.append(QString("%1min ").arg(minutes));

    } else if (minutes != 0){
        timeDuration.append(QString("%1min ").arg(minutes));
    }

    timeDuration.append(QString("%1s").arg(seconds));
    */

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

    ui->label_2->setText(QString("Délka: %1").arg(timeDuration));
    ui->label_3->setText(QString("Kanál: %1").arg(downloadVideoWindow::ytChannel));
}
