#include "downloaddialog.h"
#include "ui_downloaddialog.h"

downloadDialog::downloadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::downloadDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint| Qt::WindowMaximizeButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowFlags(windowFlags() &(~Qt::WindowMinimizeButtonHint));
    this->setWindowFlags(windowFlags() &(~Qt::WindowMaximizeButtonHint));

}

downloadDialog::~downloadDialog()
{
    delete ui;
}

void downloadDialog::on_pushButton_clicked()
{
    downloadDialog::canceled = true;
    this->close();
}

