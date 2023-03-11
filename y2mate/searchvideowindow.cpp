#include "searchvideowindow.h"
#include "./ui_searchvideowindow.h"
#include "settingsdialog.h"

#include <windows.h>


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

