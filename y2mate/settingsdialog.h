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

    bool closed = false;


private:
    Ui::settingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
