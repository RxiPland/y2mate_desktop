#ifndef DOWNLOADVIDEOWINDOW_H
#define DOWNLOADVIDEOWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QNetworkAccessManager>

namespace Ui {
class downloadVideoWindow;
}

class downloadVideoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit downloadVideoWindow(QWidget *parent = nullptr);
    ~downloadVideoWindow();

    void loadData();
    void loadSettings();

    bool closed = false;

    QString appVersion;
    QByteArray userAgent;

    QJsonObject mp3Qualities;
    QJsonObject mp4Qualities;

    QStringList mp3QualitiesKeysSorted;
    QStringList mp4QualitiesKeysSorted;

    QString videoName;
    QString videoID;
    QString ytChannel;
    qint64 videoDuration = 0;
    QString videoUrl;

    bool lastPathEnabled = true;
    QString lastSavePath;
    bool replaceNameWithHash = false;
    bool replaceNameWithUnderscores = false;

    bool exitApp = true;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_comboBox_2_currentTextChanged(const QString &arg1);

private:
    Ui::downloadVideoWindow *ui;
    QNetworkAccessManager manager;

    void closeEvent(QCloseEvent *bar = nullptr);

    void sortQualities(QStringList *list);
    void disableWidgets(bool disable = true);
    void savePath();
};

#endif // DOWNLOADVIDEOWINDOW_H
