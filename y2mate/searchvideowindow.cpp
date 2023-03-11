#include "searchvideowindow.h"
#include "./ui_searchvideowindow.h"
#include "settingsdialog.h"

#include <Windows.h>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QProcess>


SearchVideoWindow::SearchVideoWindow(QWidget *parent, bool jsonCorrupted)
    : QMainWindow(parent)
    , ui(new Ui::SearchVideoWindow)
{
    ui->setupUi(this);
    this->show();

    if(jsonCorrupted){
        QMessageBox::warning(this, "Oznámení", "Soubor s nastavením byl poškozen. Nastavení bylo přepsáno do defaultního stavu, aby program mohl fungovat.");
    }
}

SearchVideoWindow::~SearchVideoWindow()
{
    delete ui;
}


void SearchVideoWindow::on_action_menu1_1_triggered()
{
    // open y2mate's website

    ShellExecute(0, 0, L"https://www.y2mate.com", 0, 0, SW_HIDE);
}


void SearchVideoWindow::on_action_menu1_2_triggered()
{
    // open source code on github

    ShellExecute(0, 0, L"https://github.com/RxiPland/y2mate_desktop", 0, 0, SW_HIDE);
}


void SearchVideoWindow::on_action_menu1_3_triggered()
{
    // open settings window

    settingsDialog sd;
    sd.setModal(true);

    this->hide();
    sd.exec();
    this->show();
}


void SearchVideoWindow::on_action_menu2_1_triggered()
{
    // delete history from JSON file

    QFile dataFile(QDir::currentPath() + "/Data/data.json");

    if (dataFile.exists()){

        dataFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QByteArray fileContent = dataFile.readAll();
        dataFile.close();

        if(fileContent.isEmpty()){

            QMessageBox::critical(this, "Chyba", "Soubor s nastavením je prázdný! Program bude restartován pro opravu.");

            QProcess::startDetached(QApplication::applicationFilePath());

            this->close();
            return;
        }

        QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

        if(loadedJson.isEmpty()){
            // JSON cannot be loaded

            QMessageBox::critical(this, "Chyba", "JSON v souboru s nastavením je poškozený! Program bude restartován pro opravu.");

            QProcess::startDetached(QApplication::applicationFilePath());

            this->close();
            return;
        }

        QJsonObject history;

        int i;
        for(i=1; i<6; i++){

            history[QString::number(i)] = "";
        }
        loadedJson["search_history"] = history;

        QJsonDocument docData(loadedJson);

        dataFile.open(QIODevice::WriteOnly | QIODevice::Text);
        int status = dataFile.write(docData.toJson());
        dataFile.close();

        if (status == -1){
            QMessageBox::critical(this, "Chyba", "Nastala chyba při zapisování do souboru s nastavením!\n\n" + dataFile.fileName());

            return;
        }

        QMessageBox::information(this, "Oznámení", "Historie byla úspěšně smazána");

    } else{
        // file with settings not found

        QMessageBox::critical(this, "Chyba", "Soubor s nastavením neexistuje! Program bude restartován pro opravu.");

        QProcess::startDetached(QApplication::applicationFilePath());

        this->close();
        return;
    }
}


void SearchVideoWindow::on_pushButton_clicked()
{
    // search video button



}


void SearchVideoWindow::on_lineEdit_returnPressed()
{
    // return pressed when writing URL

    SearchVideoWindow::on_pushButton_clicked();
}

