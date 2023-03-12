#include "downloadvideowindow.h"
#include "ui_downloadvideowindow.h"

downloadVideoWindow::downloadVideoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::downloadVideoWindow)
{
    ui->setupUi(this);

}

downloadVideoWindow::~downloadVideoWindow()
{
    delete ui;
}

void downloadVideoWindow::loadData()
{
    // set data to widgets
}
