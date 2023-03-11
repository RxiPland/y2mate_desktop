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

    QString appVersion;
    QByteArray userAgent;

private slots:
    void on_action_menu1_1_triggered();
    void on_action_menu1_2_triggered();
    void on_action_menu1_3_triggered();
    void on_action_menu2_1_triggered();
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();

private:
    Ui::SearchVideoWindow *ui;
    QNetworkAccessManager manager;

    void disableWidgets(bool disable = true);

};
#endif // SEARCHVIDEOWINDOW_H
