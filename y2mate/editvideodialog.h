#ifndef EDITVIDEODIALOG_H
#define EDITVIDEODIALOG_H

#include <QDialog>
#include <QProcess>
#include <QRegExp>

namespace Ui {
class editVideoDialog;
}

class editVideoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editVideoDialog(QWidget *parent = nullptr, bool hidden = false);
    ~editVideoDialog();

    bool dataLoaded = false;
    void loadData();
    bool loadSettings();

    bool closed = false;

    bool startedFromSeachMenu = false;
    bool deleteOriginalFile = true;

    bool running = false;
    bool terminated = false;

    bool changed = false;
    QString newFilePath;

    QByteArray userAgent;
    bool showDownloadUrlButton = false;

    bool nameChanged;
    bool fileTypeChanged;
    QString originalPath;

    QString filePath;
    qint64 videoDurationMiliSec = 0;
    qint64 newVideoDurationMiliSec = 0;

private slots:
    void readyReadStandardOutput();
    void finished();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_lineEdit_returnPressed();

private:
    Ui::editVideoDialog *ui;

    void closeEvent(QCloseEvent *bar = nullptr);
    void disableWidgets(bool disable = true);

    QRegExp re = QRegExp("out_time_ms=(\\d+)");
    QString processOutput;
    qint64 microSeconds = 0;

    QProcess process;
    void startEdit();
    bool ffmpegExists();

};

#endif // EDITVIDEODIALOG_H
