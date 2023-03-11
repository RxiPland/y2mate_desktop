#ifndef SEARCHVIDEO_H
#define SEARCHVIDEO_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class searchVideo; }
QT_END_NAMESPACE

class searchVideo : public QMainWindow
{
    Q_OBJECT

public:
    searchVideo(QWidget *parent = nullptr);
    ~searchVideo();

private:
    Ui::searchVideo *ui;
};
#endif // SEARCHVIDEO_H
