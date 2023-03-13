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

    QString appVersion;
    QByteArray userAgent;

    QJsonObject mp3Qualities;
    QJsonObject mp4Qualities;

    QStringList mp3QualitiesKeysSorted;
    QStringList mp4QualitiesKeysSorted;

    QString videoName;
    QString videoID;
    QString ytChannel;
    int videoDuration=0;
    QString videoUrl;

    QString lastSavePath;

    bool exitApp = true;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_comboBox_2_currentTextChanged(const QString &arg1);

private:
    Ui::downloadVideoWindow *ui;
    QNetworkAccessManager manager;

    void sortQualities(QStringList *list);
    void disableWidgets(bool disable = true);
    void saveLastPath(QString lastpath);
};

#endif // DOWNLOADVIDEOWINDOW_H
