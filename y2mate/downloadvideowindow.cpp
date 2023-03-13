#include "downloadvideowindow.h"
#include "ui_downloadvideowindow.h"
#include "downloaddialog.h"

#include <QRegularExpression>
#include <QMessageBox>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>


downloadVideoWindow::downloadVideoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::downloadVideoWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(windowFlags() &(~Qt::WindowMaximizeButtonHint));
}

downloadVideoWindow::~downloadVideoWindow()
{
    delete ui;
}

void downloadVideoWindow::sortQualities(QStringList *list)
{
    QStringList tempList = list->toList();

    int i;
    static QRegularExpression re("(kbps|p)");

    for(i=0; i<tempList.length(); i++){

        tempList[i] = tempList[i].replace(re, "");
    }

    // source: https://stackoverflow.com/questions/65061873/sorting-a-qstring-list-by-numbers-c
    std::sort(tempList.begin(), tempList.end(), [](const QString &lhs, const QString &rhs)
    {
        int num_lhs = lhs.toInt();
        int num_rhs = rhs.toInt();
        return num_lhs < num_rhs;
    });

    *list = tempList;
}

void downloadVideoWindow::disableWidgets(bool disable)
{
    ui->comboBox->setDisabled(disable);
    ui->comboBox_2->setDisabled(disable);

    ui->pushButton->setDisabled(disable);
    ui->pushButton_2->setDisabled(disable);
}

void downloadVideoWindow::loadData()
{
    // set data to widgets

    ui->comboBox_2->setDisabled(true);
    ui->comboBox_2->clear();
    ui->pushButton->setDisabled(true);

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


    downloadVideoWindow::mp3QualitiesKeysSorted = mp3Qualities.keys();
    downloadVideoWindow::mp4QualitiesKeysSorted = mp4Qualities.keys();

    sortQualities(&mp3QualitiesKeysSorted);
    sortQualities(&mp4QualitiesKeysSorted);
}

void downloadVideoWindow::on_pushButton_2_clicked()
{
    exitApp = false;
    this->close();
}

void downloadVideoWindow::on_pushButton_clicked()
{
    // download video

    downloadVideoWindow::disableWidgets();

    QString format = ui->comboBox->currentText().split(' ').first();
    QString quality = ui->comboBox_2->currentText().split(' ').first();

    QString downloadToken;
    QString fileExtension;

    if (format == "mp3"){
        fileExtension = "Zvukový soubor (*.mp3)";
        downloadToken = mp3Qualities[quality].toString();

    } else if (format == "mp4"){
        fileExtension = "Video (*.mp4)";
        downloadToken = mp4Qualities[quality].toString();
    }

    if (downloadToken.isEmpty()){

        QMessageBox::critical(this, "Chyba", "Nepodařilo se najít token pro stažení videa!");
        downloadVideoWindow::disableWidgets(false);
        return;
    }


    if(!lastSavePath.endsWith('/')){
        lastSavePath.append('/');
    }

    // remove forbidden characters
    QList<QChar> forbiddenChars = {'<', '>', ':', '\"', '/', '\\', '|', '?', '*'};
    QString temp;
    int i;

    for(i=0; i<videoName.length(); i++){

        if(forbiddenChars.contains(videoName[i])){
            temp.append(' ');

        } else{
            temp.append(videoName[i]);
        }
    }
    videoName = temp.trimmed();

    // remove double whitespaces
    temp = "";
    QChar c;
    bool whitespace = false;
    for(i=0; i<videoName.length(); i++){

        c = videoName[i];

        if(c == ' ' && !whitespace){
            whitespace = true;
            temp.append(c);

        } else if (c != ' '){
            whitespace = false;
            temp.append(c);
        }
    }
    videoName = temp.trimmed();


    // get path for saving file
    QString filePath;
    filePath = QFileDialog::getSaveFileName(this, "Uložit soubor", lastSavePath + videoName, fileExtension);

    if(filePath.isEmpty()){
        downloadVideoWindow::disableWidgets(false);
        return;
    }

    // request for URL with file
    QNetworkRequest request;
    request.setUrl(QUrl("https://www.y2mate.com/mates/convertV2/index"));
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded; charset=UTF-8");
    request.setRawHeader("Referer", "https://www.y2mate.com/youtube-mp3/" + videoID.toUtf8());

    QByteArray data;

    data.append("vid=");
    data.append(QUrl::toPercentEncoding(downloadVideoWindow::videoID).toStdString());
    data.append("&");
    data.append("k=");
    data.append(QUrl::toPercentEncoding(downloadToken).toStdString());

    QLabel *label = new QLabel("Čekám na zpracování videa...   ");
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

    QString downloadLink;

    if(loadedJson["c_status"] == "CONVERTED"){
        downloadLink = loadedJson["dlink"].toString();
    }

    if(downloadLink.isEmpty()){
        disableWidgets(false);
        QMessageBox::critical(this, "Chyba", QString("Nepodařilo se získat odkaz na stažení souboru! Server vrátil:\n\n%1").arg(response));
        return;
    }

    downloadDialog dd;
    dd.setModal(true);

    dd.appVersion = downloadVideoWindow::appVersion;
    dd.userAgent = downloadVideoWindow::userAgent;
    dd.downloadLink = downloadLink;
    dd.filePath = filePath;

    dd.startDownload();
    dd.exec();

    // download was canceled
    if(dd.canceled){
       disableWidgets(false);
       return;
    }

    exitApp = false;
    this->close();
}

void downloadVideoWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    int i;

    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("<Vyberte kvalitu>");

    if(arg1.contains("mp3")){

        QString a;

        for(i=mp3QualitiesKeysSorted.length()-1; 0<=i; i--){

            a = mp3QualitiesKeysSorted[i];

            if (a.contains("128")){
                ui->comboBox_2->addItem(a + "kbps (standard)");

            } else{
                ui->comboBox_2->addItem(a + "kbps");
            }
        }

    } else if (arg1.contains("mp4")){

        for(i=mp4QualitiesKeysSorted.length()-1; 0<=i; i--){
            ui->comboBox_2->addItem(mp4QualitiesKeysSorted[i] + "p");
        }

    } else{
        ui->comboBox_2->setDisabled(true);
        ui->comboBox_2->clear();
        ui->pushButton->setDisabled(true);
        return;
    }

    if(ui->comboBox_2->currentText() == "<Vyberte kvalitu>"){
        ui->pushButton->setDisabled(true);

    } else{
        ui->pushButton->setDisabled(false);
    }

    ui->comboBox_2->setDisabled(false);
}


void downloadVideoWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if(arg1 == "<Vyberte kvalitu>"){
        ui->pushButton->setDisabled(true);

    } else{
        ui->pushButton->setDisabled(false);
    }
}

