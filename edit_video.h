#ifndef EDIT_VIDEO_H
#define EDIT_VIDEO_H

#include <QDialog>

namespace Ui {
class edit_video;
}

class edit_video : public QDialog
{
    Q_OBJECT

public:
    explicit edit_video(QWidget *parent = nullptr);
    ~edit_video();
    void set_info(QString name, QString length, QString path);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();

    void disable_widgets(bool disable);

private:
    Ui::edit_video *ui;
};

#endif // EDIT_VIDEO_H
