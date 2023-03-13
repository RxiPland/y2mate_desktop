#include "downloaddialog.h"
#include "ui_downloaddialog.h"

#include <QFileInfo>
#include <QMessageBox>

downloadDialog::downloadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::downloadDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint| Qt::WindowMaximizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowFlags(windowFlags() &(~Qt::WindowMinimizeButtonHint));
    this->setWindowFlags(windowFlags() &(~Qt::WindowMaximizeButtonHint));

    this->setWindowModality(Qt::ApplicationModal);
}

downloadDialog::~downloadDialog()
{
    delete ui;
}

void downloadDialog::startDownload()
{
    file = openFileForWrite(downloadDialog::filePath);
    if (!file){
        QMessageBox::critical(this, "Problém", "Nastal problém při otevírání souboru.\n\n" + downloadDialog::filePath);
        return;
    }


    QNetworkRequest request;
    request.setUrl(QUrl(downloadDialog::downloadLink));
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);
    request.setRawHeader("Referer", "https://www.y2mate.com/");

    reply.reset(manager.get(request));

    connect(reply.get(), &QNetworkReply::finished, this, &downloadDialog::httpFinished);
    connect(reply.get(), &QIODevice::readyRead, this, &downloadDialog::httpReadyRead);
    connect(reply.get(), &QNetworkReply::downloadProgress,this, &downloadDialog::downloadProgress);
}

void downloadDialog::on_pushButton_clicked()
{
    // cancel or complete download button

    QString buttonText = ui->pushButton->text();

    if(buttonText == "Hotovo"){
        // everything OK

    } else{
        downloadDialog::canceled = true;

        reply->close();
        //reply.reset();
        //reply->deleteLater();
    }

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
            QMessageBox::critical(this, "Chyba", "Nastala chyba při stahování souboru! Chyba: " + errorString);
        }
        QFile::remove(fi.absoluteFilePath());

        return;
    }

    this->setWindowTitle("Stahování - dokončeno");
    ui->pushButton->setText("Hotovo");
}

void downloadDialog::downloadProgress(qint64 ist, qint64 max)
{

    ui->progressBar->setRange(0,max);
    ui->progressBar->setValue(ist);

    ui->label->setText(QString::number(ist/1000000) + "." + QString::number(ist/100000).back() + " / " + QString::number(max/1000000) + "." + QString::number(max/100000).back() + " MB");
}

std::unique_ptr<QFile> downloadDialog::openFileForWrite(const QString &fileName)
{
    std::unique_ptr<QFile> file = std::make_unique<QFile>(fileName);

    file->open(QIODevice::WriteOnly);

    return file;
}
