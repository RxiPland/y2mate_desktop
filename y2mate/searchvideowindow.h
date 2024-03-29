#ifndef SEARCHVIDEOWINDOW_H
#define SEARCHVIDEOWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class SearchVideoWindow; }
QT_END_NAMESPACE

class searchVideoWindow : public QMainWindow
{
    Q_OBJECT

public:
    searchVideoWindow(QWidget *parent = nullptr, bool jsonCorrupted = false);
    ~searchVideoWindow();

    bool loadSettings();
    void checkUpdate();

    QString appVersion;
    QByteArray userAgent;
    bool allowHistory = true;
    bool checkForUpdates = true;

    bool lastPathEnabled = true;
    QString lastSavePath;
    bool replaceNameWithHash = false;
    bool replaceNameWithUnderscores = false;
    bool showDownloadUrlButton = false;

    bool running = false;

signals:
    void closed();

private slots:
    void on_action_menu1_1_triggered();
    void on_action_menu1_2_triggered();
    void on_action_menu1_3_triggered();
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();
    void on_action_menu2_6_triggered();
    void on_action_menu_2_1_1_triggered();
    void on_action_menu_2_1_2_triggered();
    void on_action_menu_2_2_1_triggered();
    void on_action_menu_2_2_2_triggered();
    void on_action_menu_2_3_1_triggered();
    void on_action_menu_2_3_2_triggered();
    void on_action_menu_2_4_1_triggered();
    void on_action_menu_2_4_2_triggered();
    void on_action_menu_2_5_1_triggered();
    void on_action_menu_2_5_2_triggered();
    void on_action_menu3_1_triggered();

private:
    Ui::SearchVideoWindow *ui;
    QNetworkAccessManager manager;

    void closeEvent(QCloseEvent *bar = nullptr);

    bool ffmpegExists();

    void disableWidgets(bool disable = true);
    void sortQualities(QStringList *list);
    bool saveToHistory(QString videoName, QString videoDuration, QString videoUrl);
    bool savePath(QString path);
    QJsonObject getVideoFromHistory(QString index);

};
#endif // SEARCHVIDEOWINDOW_H
