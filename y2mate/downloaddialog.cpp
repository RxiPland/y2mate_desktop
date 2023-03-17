#include "downloaddialog.h"
#include "ui_downloaddialog.h"
#include "editvideodialog.h"

#include <QFileInfo>
#include <QMessageBox>
#include <windows.h>
#include <QClipboard>

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

    this->show();
}

downloadDialog::~downloadDialog()
{
    delete ui;
}

void downloadDialog::startDownload()
{
    if(ffmpegDownload){
        ui->pushButton_2->setHidden(true);
        ui->pushButton_4->setHidden(true);
    }


    ui->label_2->setText(downloadDialog::filePath.split('/').last());

    file = openFileForWrite(downloadDialog::filePath);
    if (!file){
        QMessageBox::critical(this, "Problém", "Nastal problém při otevírání souboru.\n\n" + downloadDialog::filePath);
        return;
    }

    QNetworkRequest request;
    request.setUrl(QUrl(downloadDialog::downloadLink));
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);

    if(!ffmpegDownload){
        request.setRawHeader("Referer", "https://www.y2mate.com/");
    }

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

    if(!ffmpegDownload){
        ui->pushButton_2->setDisabled(false);
        ui->pushButton_4->setDisabled(false);
    }

    downloadDialog::finished = true;
    if(!downloadDialog::dialogOpen){
        this->setWindowFlags(this->windowFlags() | Qt::WindowCloseButtonHint);
        this->show();
    }

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
    // open file

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
    evd.videoDurationMiliSec = downloadDialog::videoDurationMiliSec;
    evd.userAgent = downloadDialog::userAgent;
    this->hide();
    evd.loadData();

    // wait for close
    while(!evd.isHidden()){
        qApp->processEvents();
    }

    // rename back and delete temp
    if(evd.running){
        QFile::remove(evd.newFilePath);

        if(!evd.nameChanged && !evd.fileTypeChanged){
            QFile temp(evd.originalPath);
            temp.rename(evd.newFilePath);
        }
    }

    // update label & disable further editing
    if(evd.changed){
        downloadDialog::filePath = evd.newFilePath;
        downloadDialog::videoDurationMiliSec = evd.newVideoDurationMiliSec;
        ui->label_2->setText(evd.newFilePath.split('/').last());
        ui->pushButton_4->setDisabled(true);
    }

    this->show();
}

void downloadDialog::on_pushButton_5_clicked()
{
    // show URL of downloaded file

    downloadDialog::dialogOpen = true;

    QMessageBox msgBox;
    msgBox.setWindowTitle("Odkaz stahovaného souboru");

    QString formatedDownloadLink;
    int i;

    // add every 60th character new line
    for(i=0; i<downloadDialog::downloadLink.length(); i++){

        if(i % 60 == 0){
            formatedDownloadLink.append("\n");
        }
        formatedDownloadLink.append(downloadLink[i]);
    }

    msgBox.setText(formatedDownloadLink);
    QAbstractButton* pButtonCopy = msgBox.addButton(" Kopírovat ", QMessageBox::NoRole);
    QAbstractButton* pButtonOk = msgBox.addButton(" Ok ", QMessageBox::NoRole);

    pButtonCopy->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    pButtonOk->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    msgBox.exec();

    if (msgBox.clickedButton() == pButtonCopy){
        // copy to clipboard

        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setText(downloadDialog::downloadLink);
    }

    downloadDialog::dialogOpen = false;

    downloadDialog::finished = true;
    if (downloadDialog::finished){
        this->setWindowFlags(this->windowFlags() | Qt::WindowCloseButtonHint);
        this->show();
    }
}

