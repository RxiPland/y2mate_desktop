#include "searchvideowindow.h"
#include "./ui_searchvideowindow.h"
#include "settingsdialog.h"

#include <Windows.h>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>


SearchVideoWindow::SearchVideoWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SearchVideoWindow)
{
    ui->setupUi(this);
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

        QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

        if(loadedJson.isEmpty()){
            // JSON will not be loaded

            QMessageBox::critical(this, "Chyba", "Nastala chyba při načítání JSONu ze souboru s nastavením!\n\n" + dataFile.fileName());
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
        dataFile.write(docData.toJson());
        dataFile.close();

        QMessageBox::information(this, "Oznámení", "Historie byla úspěšně vymazána");
    }
}

