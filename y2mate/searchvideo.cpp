#include "searchvideo.h"
#include "./ui_searchvideo.h"

searchVideo::searchVideo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::searchVideo)
{
    ui->setupUi(this);
}

searchVideo::~searchVideo()
{
    delete ui;
}

