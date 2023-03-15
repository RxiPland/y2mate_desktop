#ifndef DOWNLOADDIALOG_H
#define DOWNLOADDIALOG_H

#include <QDialog>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class downloadDialog;
}

class downloadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit downloadDialog(QWidget *parent = nullptr);
    ~downloadDialog();

    void startDownload();

    QByteArray userAgent;

    QString downloadLink;
    QString filePath;
    qint64 videoDurationMiliSec = 0;

    bool canceled = false;

private slots:
    std::unique_ptr<QFile> openFileForWrite(const QString &fileName);

    void httpFinished();
    void httpReadyRead();
    void downloadProgress(qint64 ist, qint64 max);

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::downloadDialog *ui;
    std::unique_ptr<QFile> file;
    QNetworkAccessManager manager;
    QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> reply;

};

#endif // DOWNLOADDIALOG_H
