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
    void finished();

private:
    Ui::editVideoDialog *ui;

    void closeEvent(QCloseEvent *bar = nullptr);

    QRegExp re = QRegExp("out_time_ms=(\\d+)");
    QString processOutput;
    qint64 microSeconds = 0;

    QProcess process;

};

#endif // EDITVIDEODIALOG_H
