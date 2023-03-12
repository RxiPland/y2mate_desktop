#ifndef DOWNLOADDIALOG_H
#define DOWNLOADDIALOG_H

#include <QDialog>

namespace Ui {
class downloadDialog;
}

class downloadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit downloadDialog(QWidget *parent = nullptr);
    ~downloadDialog();

    QString appVersion;
    QByteArray userAgent;

    QString downloadLink;

private:
    Ui::downloadDialog *ui;
};

#endif // DOWNLOADDIALOG_H
