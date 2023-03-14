#include "downloaddialog.h"
#include "ui_downloaddialog.h"
#include "editvideodialog.h"

#include <QFileInfo>
#include <QMessageBox>
#include <windows.h>

downloadDialog::downloadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::downloadDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowFlags(windowFlags() &(~Qt::WindowCloseButtonHint));
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
    ui->label_2->setText(downloadDialog::filePath.split('/').last());

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

        if(!reply.isNull()){
            reply->close();
            reply->deleteLater();
        }
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
    ui->pushButton->setText("Hotovo");
    ui->pushButton_2->setDisabled(false);
    ui->pushButton_4->setDisabled(false);

    this->setWindowFlags(this->windowFlags() | Qt::WindowCloseButtonHint);
    this->show();
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
    std::unique_ptr<QFile> file = std::make_unique<QFile>(fileName);

    file->open(QIODevice::WriteOnly);

    return file;
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

    editVideoDialog evd;
    evd.filePath = downloadDialog::filePath;
    evd.videoDuration = downloadDialog::videoDuration;
    evd.loadData();

    this->hide();
    evd.show();

    // wait for close
    while(!evd.isHidden()){
        qApp->processEvents();
    }

    // update label
    if(evd.changed){
        downloadDialog::filePath = evd.newFilePath;
        ui->label_2->setText(evd.newFilePath.split('/').last());
    }

    this->show();
}

