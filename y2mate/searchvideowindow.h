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

    void loadSettings();
    void checkUpdate();

    QString appVersion;
    QByteArray userAgent;
    bool allowHistory;
    bool checkForUpdates;
    QString lastSavePath;

private slots:
    void on_action_menu1_1_triggered();
    void on_action_menu1_2_triggered();
    void on_action_menu1_3_triggered();
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();
    void on_action_menu2_6_triggered();

private:
    Ui::SearchVideoWindow *ui;
    QNetworkAccessManager manager;

    void disableWidgets(bool disable = true);
    void sortQualities(QStringList *list);
    void saveToHistory(QString videoName, QString videoDuration, QString videoUrl);

};
#endif // SEARCHVIDEOWINDOW_H
