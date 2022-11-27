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
    void store_window_parameters(int left=0, int top=0);

public slots:
    void get(QString url, QString koncovka);
    void post(QString location, QByteArray data, int druh_promenne);
    static void load_settings();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void disable_widgets(bool vypnout);
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_lineEdit_returnPressed();
    void center_window();

    void on_actiony2mate_com_triggered();
    void on_actionzdrojovy_kod_triggered();
    void on_actionNastaven_triggered();
    void on_actionSmazat_historii_triggered();

    std::unique_ptr<QFile> openFileForWrite(const QString &fileName);

    void httpFinished();
    void httpReadyRead();
    void get_headers(QString location);
    void get_nazev();
    void downloadProgress(qint64 ist, qint64 max);

    QStringList history_soubor(QString operace, QString data_k_ulozeni);
    void load_history();
    void check_version();
    void open_yt_video(int row_order);
    void apply_yt_video(int row_order);
    void save_last_path();

    // open videos in browser
    void on_actionOtev_t_triggered();
    void on_actionOtev_t_2_triggered();
    void on_actionOtev_t_3_triggered();
    void on_actionOtev_t_4_triggered();
    void on_actionOtev_t_5_triggered();

    // apply videos to y2mate desktop
    void on_actionPou_t_triggered();
    void on_actionPou_t_2_triggered();
    void on_actionPou_t_3_triggered();
    void on_actionPou_t_4_triggered();
    void on_actionPou_t_5_triggered();

    void on_actionOtev_t_soubor_triggered();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager;
    QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> reply;
    std::unique_ptr<QFile> file;

};
#endif // MAINWINDOW_H
