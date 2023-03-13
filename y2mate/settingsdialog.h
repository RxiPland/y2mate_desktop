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

    bool settingsChanged = false;

private slots:
    void on_checkBox_3_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::settingsDialog *ui;

    void closeEvent(QCloseEvent *bar = nullptr);
};

#endif // SETTINGSDIALOG_H
