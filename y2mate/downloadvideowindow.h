#ifndef DOWNLOADVIDEOWINDOW_H
#define DOWNLOADVIDEOWINDOW_H

#include <QMainWindow>

namespace Ui {
class downloadVideoWindow;
}

class downloadVideoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit downloadVideoWindow(QWidget *parent = nullptr);
    ~downloadVideoWindow();

private:
    Ui::downloadVideoWindow *ui;
};

#endif // DOWNLOADVIDEOWINDOW_H
