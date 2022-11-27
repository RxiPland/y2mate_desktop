#ifndef EDITVIDEOWINDOW_H
#define EDITVIDEOWINDOW_H

#include <QMainWindow>

namespace Ui {
class EditVideoWindow;
}

class EditVideoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditVideoWindow(QWidget *parent = nullptr);
    ~EditVideoWindow();

    void set_info(QString name, QString length, QString path);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();

    void disable_widgets(bool disable);

    void on_timeEdit_userTimeChanged(const QTime &time);
    void on_timeEdit_2_userTimeChanged(const QTime &time2);

private:
    Ui::EditVideoWindow *ui;
};

#endif // EDITVIDEOWINDOW_H
