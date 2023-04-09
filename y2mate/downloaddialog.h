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
    explicit downloadDialog(QWidget *parent = nullptr, bool hidden = false, QString fileName = "");
    ~downloadDialog();

    void startDownload();
    bool otherDownload = false;

    bool loadSettings();

    QByteArray userAgent;
    bool showDownloadUrlButton = false;
    bool downloadFinishedSound = true;

    QString downloadLink;
    QString filePath;
    qint64 videoDurationMiliSec = 0;

    QString customFinishMessage;

    bool canceled = false;
    bool running = false;
    bool closedWithButton = false; // (install / complete) button

signals:
    void closed();

private slots:
    std::unique_ptr<QFile> openFileForWrite(const QString &fileName);

    void httpFinished();
    void httpReadyRead();
    void downloadProgress(qint64 ist, qint64 max);

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::downloadDialog *ui;
    std::unique_ptr<QFile> file;
    QNetworkAccessManager manager;
    QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> reply;

    void closeEvent(QCloseEvent *bar = nullptr);

    bool ffmpegExists();

};

#endif // DOWNLOADDIALOG_H
