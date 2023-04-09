#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>

namespace Ui {
class settingsDialog;
}

class settingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit settingsDialog(QWidget *parent = nullptr);
    ~settingsDialog();

    void loadSettings();
    bool saveSettings();

    bool settingsChanged = false;

    bool running = false;

signals:
    void closed();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

    void on_checkBox_clicked();
    void on_checkBox_2_clicked();
    void on_checkBox_3_clicked();
    void on_checkBox_4_clicked();
    void on_checkBox_5_clicked();
    void on_checkBox_6_clicked();
    void on_checkBox_7_clicked();

    void on_toolButton_clicked();
    void on_toolButton_2_clicked();
    void on_toolButton_3_clicked();
    void on_toolButton_4_clicked();
    void on_toolButton_5_clicked();
    void on_toolButton_6_clicked();
    void on_toolButton_7_clicked();


private:
    Ui::settingsDialog *ui;
    QNetworkAccessManager manager;

    void closeEvent(QCloseEvent *bar = nullptr);
    void disableWidgets(bool disable = true);

    QString appVersion;
    QByteArray userAgent;

    bool checkForUpdates = true;
    bool allowHistory = true;
    QString lastSavePath;
    bool lastPathEnabled = true;
    bool replaceNameWithHash = false;
    bool replaceNameWithUnderscores = false;
    bool showDownloadUrlButton = false;
    bool downloadFinishedSound = true;
};

#endif // SETTINGSDIALOG_H
