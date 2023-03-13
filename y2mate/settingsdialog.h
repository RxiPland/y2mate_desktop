#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

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
    void saveSettings();

    bool settingsChanged = false;

private slots:
    void on_checkBox_3_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_checkBox_clicked();
    void on_checkBox_2_clicked();
    void on_checkBox_4_clicked();
    void on_checkBox_5_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::settingsDialog *ui;

    void closeEvent(QCloseEvent *bar = nullptr);

    QString appVersion;
    bool checkForUpdates = true;
    bool allowHistory = true;
    QString lastSavePath;
    bool lastPathEnabled = true;
    bool replaceNameWithHash = false;
    bool replaceNameWithUnderscores = false;
};

#endif // SETTINGSDIALOG_H
