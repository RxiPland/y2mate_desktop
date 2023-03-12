#include "downloaddialog.h"
#include "ui_downloaddialog.h"

downloadDialog::downloadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::downloadDialog)
{
    ui->setupUi(this);
}

downloadDialog::~downloadDialog()
{
    delete ui;
}
