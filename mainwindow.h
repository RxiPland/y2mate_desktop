#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QNetworkProxy>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    //void get(QString location);
    void post(QString location, QByteArray data);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_lineEdit_returnPressed();
    void on_actiony2mate_com_triggered();
    void on_actionzdrojovy_kod_triggered();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager;
};
#endif // MAINWINDOW_H
