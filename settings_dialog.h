#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QNetworkProxy>

namespace Ui {
class settings_dialog;
}

class settings_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit settings_dialog(QWidget *parent = nullptr);
    ~settings_dialog();
    void set_version(QString version);  // set app's version

private:
    Ui::settings_dialog *ui;
    QNetworkAccessManager manager;
    QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> reply;

private slots:
    void settings_changed(bool warning);
    void check_version(bool show_response);
    void load_settings();

    void on_pushButton_4_clicked();  // uložit nastavení
    void on_pushButton_5_clicked();
    void on_checkBox_2_stateChanged(int arg1);
    void on_checkBox_stateChanged(int arg1);
    void on_checkBox_3_stateChanged(int arg1);
    void on_pushButton_6_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_checkBox_4_stateChanged(int arg1);
    void on_pushButton_9_clicked();
    void on_checkBox_5_stateChanged(int arg1);
    void on_pushButton_10_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_11_clicked();
};

#endif // SETTINGS_DIALOG_H
