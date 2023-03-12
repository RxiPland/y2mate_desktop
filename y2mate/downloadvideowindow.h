#ifndef DOWNLOADVIDEOWINDOW_H
#define DOWNLOADVIDEOWINDOW_H

#include <QMainWindow>
#include <QJsonObject>

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

    QJsonObject mp3Qualities;
    QJsonObject mp4Qualities;

    QString videoName;
    QString videoID;
    QString ytChannel;
    int videoDuration=0;
    QString videoUrl;

private:
    Ui::downloadVideoWindow *ui;
};

#endif // DOWNLOADVIDEOWINDOW_H
