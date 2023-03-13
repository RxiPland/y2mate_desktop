#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <windows.h>

settingsDialog::settingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsDialog)
{
    ui->setupUi(this);
}

settingsDialog::~settingsDialog()
{
    delete ui;
}

void settingsDialog::closeEvent(QCloseEvent *bar)
{
    // Before application close

    if(!settingsChanged){

        QMessageBox msgBox;
        msgBox.setWindowTitle("Upozornění");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Bylo zjištěno neuložené nastavení! Opravdu chcete zahodit změny?");
        msgBox.addButton(" Ano ", QMessageBox::YesRole);
        QAbstractButton* pButtonNo = msgBox.addButton(" Ne ", QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton() == pButtonNo) {
            bar->ignore();
            return;
        }
    }

    this->close();

    if(bar != nullptr){
        bar->accept();
    }
}


void settingsDialog::on_checkBox_3_clicked()
{
    bool isChecked = ui->checkBox_3->isChecked();

    if(isChecked){
        ui->pushButton->setDisabled(false);

    } else{
        ui->pushButton->setDisabled(true);
    }
}


void settingsDialog::on_pushButton_3_clicked()
{
    this->close();
}

