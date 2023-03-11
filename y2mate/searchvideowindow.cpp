#include "searchvideowindow.h"
#include "./ui_searchvideowindow.h"

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

