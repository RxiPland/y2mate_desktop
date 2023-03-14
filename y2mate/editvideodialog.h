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

    void loadData();

    bool converted = false;

    QString filePath;

    // start time
    int startHours = 0;
    int startMinutes = 0;
    float startSeconds = 0.0;

    // end time
    int endHours = 0;
    int endMinutes = 0;
    float endSeconds = 0.0;


private slots:
    void readyReadStandardOutput();
    void finished();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::editVideoDialog *ui;

    void closeEvent(QCloseEvent *bar = nullptr);

    QRegExp re = QRegExp("out_time_ms=(\\d+)");
    QString processOutput;
    qint64 microSeconds = 0;

    QProcess process;
    void startEdit();

};

#endif // EDITVIDEODIALOG_H
