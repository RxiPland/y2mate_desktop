#ifndef SEARCHVIDEOWINDOW_H
#define SEARCHVIDEOWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SearchVideoWindow; }
QT_END_NAMESPACE

class SearchVideoWindow : public QMainWindow
{
    Q_OBJECT

public:
    SearchVideoWindow(QWidget *parent = nullptr, bool jsonCorrupted = false);
    ~SearchVideoWindow();

    QString appVersion;
    QByteArray userAgent;

private slots:
    void on_action_menu1_1_triggered();
    void on_action_menu1_2_triggered();
    void on_action_menu1_3_triggered();
    void on_action_menu2_1_triggered();

private:
    Ui::SearchVideoWindow *ui;
};
#endif // SEARCHVIDEOWINDOW_H
