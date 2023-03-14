#ifndef EDITVIDEODIALOG_H
#define EDITVIDEODIALOG_H

#include <QDialog>
#include <QProcess>
#include <QRegExp>

namespace Ui {
class editVideoDialog;
}

class editVideoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editVideoDialog(QWidget *parent = nullptr);
    ~editVideoDialog();

    void startEdit();

private slots:
    void readyReadStandardOutput();

private:
    Ui::editVideoDialog *ui;

    void closeEvent(QCloseEvent *bar = nullptr);

    QRegExp re = QRegExp("out_time_ms=(\\d+)");
    QString outTimeMs;

    QProcess process;

};

#endif // EDITVIDEODIALOG_H
