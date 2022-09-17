#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QNetworkProxy>
#include <QFile>

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
    void get(QString url, QString koncovka);
    void post(QString location, QByteArray data, int druh_promenne);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void disable_widgets(bool vypnout);
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_lineEdit_returnPressed();
    void on_actiony2mate_com_triggered();
    void on_actionzdrojovy_kod_triggered();

    std::unique_ptr<QFile> openFileForWrite(const QString &fileName);

    void httpFinished();
    void httpReadyRead();
    void get_headers(QString location);
    void get_nazev();
    void downloadProgress(qint64 ist, qint64 max);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager;
    QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> reply;
    std::unique_ptr<QFile> file;
};
#endif // MAINWINDOW_H
