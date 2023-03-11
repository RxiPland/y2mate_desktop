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
    SearchVideoWindow(QWidget *parent = nullptr);
    ~SearchVideoWindow();

    QString appVersion;
    QByteArray userAgent;

private:
    Ui::SearchVideoWindow *ui;
};
#endif // SEARCHVIDEOWINDOW_H
