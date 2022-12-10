#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings_dialog.h"
#include "editvideowindow.h"
#include "threadfunctions.h"

#include <QMessageBox>
#include <stdio.h>
#include <QDebug>
#include <iostream>
#include <unistd.h>
#include <QRegExp>
#include <windows.h>
#include <QList>
#include <QByteArray>
#include <QFileDialog>
#include <QTextCodec>
#include <QJsonDocument>
#include <QJsonObject>

using namespace std;

QString response = "", response_najit_formaty = "";     // různé proměnné pro různé ukládání http responsů
QString nalezene_formaty_mp3[6] = {"nic", "nic", "nic", "nic", "nic", "nic"}; // zde se přepíše "nic" nalezenými formáty (128kbps, 192kbps, ...)
QString nalezene_formaty_mp4[6] = {"nic", "nic", "nic", "nic", "nic", "nic"};

QString nazev_souboru = "";  // název yt videa
QString nazev_souboru_hash = ""; // náhodný hash přijatý z requestu
QString cesta_k_souboru = "/";  // úplná cesta k uloženému souboru
QString video_duration = "";  // délka videa xx:xx:xx
QString yt_video_link = "";  // odkaz na youtube video
QString last_location_path = "/"; // poslední cesta uloženého souboru
QString selected_video_quality = "128 kbps";

QString app_version = "v1.8.4";  // actual version of app
bool hodnoty_nastaveni[5] = {}; // {REPLACE_VIDEO_NAME, UNDERSCORE_REPLACE, AUTO_CHECK_UPDATE, SAVE_HISTORY, LAST_LOCATION}
bool downloading_ffmpeg = false;
bool downloading_ffmpeg_menubar = false;
int window_parameters[2] = {0, 0};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    if (QSslSocket::supportsSsl() == false){

        QMessageBox msgBox;
        msgBox.setWindowTitle("Problém | y2mate desktop - by RxiPland");
        msgBox.setText("Verze OpenSSL není platná!<br>Bez ní program nemůže přistupovat na zabezpečené weby s protokolem HTTPs<br><br>Nainstalování verze \"" + QSslSocket::sslLibraryBuildVersionString() + "\", nebo velmi podobné, problém opraví<br>Odkaz na stažení: <a href=\"https://www.filehorse.com/download-openssl-64\">https://www.filehorse.com/download-openssl-64</a><br><br>Před stažením je důležité označit správnou verzi!<br>Vaše aktuální nainstalovaná verze: \"" + QSslSocket::sslLibraryVersionString() + "\"");
        QAbstractButton* pButtonYes = msgBox.addButton("Otevřít odkaz", QMessageBox::YesRole);
        msgBox.addButton("Odejít", QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton()==pButtonYes) {
            ShellExecute(0, 0, L"https://www.filehorse.com/download-openssl-64", 0, 0, SW_HIDE);
        }

        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
        return;
    }

    ui->setupUi(this);
    this->setWindowTitle("y2mate desktop");
    this->setWindowFlags(windowFlags() &(~Qt::WindowMaximizeButtonHint));

    ui->lineEdit->setFocus();

    ui->comboBox->setHidden(true);
    ui->comboBox_2->setHidden(true);
    ui->pushButton_2->setHidden(true);
    ui->label->setHidden(true);  // délka videa
    ui->label_2->setHidden(true);  // název videa

    ui->label_3->setHidden(true);  // informace o postupu
    ui->label_4->setHidden(true);  // postup stahování

    ui->progressBar->setHidden(true);  // progress bar stahování
    ui->progressBar->setValue(0);

    ui->horizontalSpacer->changeSize(250, 35);

    ui->statusBar->addPermanentWidget(ui->label_3, 1);  // informace o requestu
    ui->statusBar->addPermanentWidget(ui->label_4, 1);  // staženo mb z celkového počtu
    ui->statusBar->addPermanentWidget(ui->progressBar, 2);  // progress bar stahování

    ui->label_4->clear();

    // načtení nastavení ze souboru
    MainWindow::load_settings();

    // automatická kontrola verze
    if (hodnoty_nastaveni[2]){
        MainWindow::check_version();
    }

    MainWindow::load_history();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::store_window_parameters(int left, int top){

    window_parameters[0] = left;
    window_parameters[1] = top;
}

void MainWindow::center_window(){

    this->move(window_parameters[0], window_parameters[1]);
}

QStringList MainWindow::history_soubor(QString operace="load", QString data_k_ulozeni=""){
    // operace = save/delete/load

    QFile file_history("history.txt");

    if(operace == "save" && data_k_ulozeni != ""){
        // uložit do souboru

        if (file_history.exists()){
            file_history.open(QIODevice::ReadOnly);

            QByteArray obsah = file_history.readAll();
            file_history.close();

            QString obsah_souboru = QTextCodec::codecForMib(106)->toUnicode(obsah);
            QStringList rows_history = obsah_souboru.split("\r\n");

            int pocet_rows = rows_history.count();

            for(int i=0; i < 5-pocet_rows; i++){
                rows_history.append("");
            }

            // do not write if the previous search in history is equal to this search
            if (data_k_ulozeni != rows_history[0]){

                file_history.open(QIODevice::WriteOnly | QIODevice::Text);
                QTextStream out(&file_history);

                for(int i=0; i<5; i++){
                    if (i==0){
                        out << data_k_ulozeni << "\n";

                    } else{
                        if (rows_history[i-1] != ""){
                            out << rows_history[i-1] << "\n";
                        }
                    }
                }
                file_history.close();
            }
        }

    }else if(operace == "delete"){
        // odstranit soubor

        if (file_history.exists()){
            file_history.remove();
        }

    } else{
        // získat data ze souboru (operace == "load")

        if (file_history.exists()){
            file_history.open(QIODevice::ReadOnly);

            QByteArray obsah = file_history.readAll();
            file_history.close();

            QString obsah_souboru = QTextCodec::codecForMib(106)->toUnicode(obsah);
            QStringList rows_history = obsah_souboru.split("\r\n");

            return rows_history;
        }
    }

    return QStringList();
}

void MainWindow::load_history(){
    // načíst posledně hledaná videa ze souboru history.txt

    if (hodnoty_nastaveni[3]){
        // hodnoty_nastaveni[3] -> určuje, zda je historie povolena

        QFile file_history("history.txt");

        if (file_history.exists()){

            ui->actionSmazat_historii->setIconVisibleInMenu(true);
            ui->actionSmazat_historii->setEnabled(true);
            ui->actionSmazat_historii->setText("Smazat historii");

            QStringList rows = MainWindow::history_soubor("load");
            int pocet_rows = rows.count();

            for(int i=0; i < 5-pocet_rows; i++){
                rows.append("");
            }

            QStringList values;
            // 1.
            if (rows[0] != "" && rows[0].count(" /;/ ") == 2){
                values = rows[0].split(" /;/ ");

                ui->menu1->setTitle("1. " + values[0]);
                ui->actionD_lka->setText("Délka: " + values[1]);

                ui->actionPou_t->setVisible(true);
                ui->actionOtev_t->setVisible(true);
                ui->actionD_lka->setVisible(true);
                ui->menu1->menuAction()->setVisible(true);

            }else if (rows[0] != ""){
                ui->menu1->setTitle("1. [Chyba v souboru s historií]");
                ui->actionPou_t->setVisible(false);
                ui->actionOtev_t->setVisible(false);
                ui->actionD_lka->setVisible(false);
                ui->menu1->menuAction()->setVisible(true);

            }else{
                ui->menu1->menuAction()->setVisible(false);
            }

            // 2.
            if (rows[1] != "" && rows[1].count(" /;/ ") == 2){
                values = rows[1].split(" /;/ ");

                ui->menu2->setTitle("2. " + values[0]);
                ui->actionD_lka_2->setText("Délka: " + values[1]);

                ui->actionPou_t_2->setVisible(true);
                ui->actionOtev_t_2->setVisible(true);
                ui->actionD_lka_2->setVisible(true);
                ui->menu2->menuAction()->setVisible(true);

            }else if (rows[1] != ""){
                ui->menu2->setTitle("2. [Chyba v souboru s historií]");
                ui->actionPou_t_2->setVisible(false);
                ui->actionOtev_t_2->setVisible(false);
                ui->actionD_lka_2->setVisible(false);
                ui->menu2->menuAction()->setVisible(true);

            }else{
                ui->menu2->menuAction()->setVisible(false);
            }

            // 3.
            if (rows[2] != "" && rows[2].count(" /;/ ") == 2){
                values = rows[2].split(" /;/ ");

                ui->menu3->setTitle("3. " + values[0]);
                ui->actionD_lka_3->setText("Délka: " + values[1]);

                ui->actionPou_t_3->setVisible(true);
                ui->actionOtev_t_3->setVisible(true);
                ui->actionD_lka_3->setVisible(true);
                ui->menu3->menuAction()->setVisible(true);

            }else if (rows[2] != ""){
                ui->menu3->setTitle("3. [Chyba v souboru s historií]");
                ui->actionPou_t_3->setVisible(false);
                ui->actionOtev_t_3->setVisible(false);
                ui->actionD_lka_3->setVisible(false);
                ui->menu3->menuAction()->setVisible(true);

            }else{
                ui->menu3->menuAction()->setVisible(false);
            }

            // 4.
            if (rows[3] != "" && rows[3].count(" /;/ ") == 2){
                values = rows[3].split(" /;/ ");

                ui->menu4->setTitle("4. " + values[0]);
                ui->actionD_lka_4->setText("Délka: " + values[1]);

                ui->actionPou_t_4->setVisible(true);
                ui->actionOtev_t_4->setVisible(true);
                ui->actionD_lka_4->setVisible(true);
                ui->menu4->menuAction()->setVisible(true);

            }else if (rows[3] != ""){
                ui->menu4->setTitle("4. [Chyba v souboru s historií]");
                ui->actionPou_t_4->setVisible(false);
                ui->actionOtev_t_4->setVisible(false);
                ui->actionD_lka_4->setVisible(false);
                ui->menu4->menuAction()->setVisible(true);

            }else{
                ui->menu4->menuAction()->setVisible(false);
            }

            // 5.
            if (rows[4] != "" && rows[4].count(" /;/ ") == 2){
                values = rows[4].split(" /;/ ");

                ui->menu5->setTitle("5. " + values[0]);
                ui->actionD_lka_5->setText("Délka: " + values[1]);

                ui->actionPou_t_5->setVisible(true);
                ui->actionOtev_t_5->setVisible(true);
                ui->actionD_lka_5->setVisible(true);
                ui->menu5->menuAction()->setVisible(true);

            }else if (rows[4] != ""){
                ui->menu5->setTitle("5. [Chyba v souboru s historií]");
                ui->actionPou_t_5->setVisible(false);
                ui->actionOtev_t_5->setVisible(false);
                ui->actionD_lka_5->setVisible(false);
                ui->menu5->menuAction()->setVisible(true);

            }else{
                ui->menu5->menuAction()->setVisible(false);
            }

        }else{

            // create blank txt
            file_history.open(QIODevice::WriteOnly | QIODevice::Text);
            file_history.close();

            ui->menu1->menuAction()->setVisible(false);
            ui->menu2->menuAction()->setVisible(false);
            ui->menu3->menuAction()->setVisible(false);
            ui->menu4->menuAction()->setVisible(false);
            ui->menu5->menuAction()->setVisible(false);

            ui->actionSmazat_historii->setIconVisibleInMenu(true);
            ui->actionSmazat_historii->setEnabled(true);
            ui->actionSmazat_historii->setText("Smazat historii");
        }

    } else{
        ui->menu1->menuAction()->setVisible(false);
        ui->menu2->menuAction()->setVisible(false);
        ui->menu3->menuAction()->setVisible(false);
        ui->menu4->menuAction()->setVisible(false);
        ui->menu5->menuAction()->setVisible(false);

        ui->actionSmazat_historii->setIconVisibleInMenu(false);
        ui->actionSmazat_historii->setEnabled(false);
        ui->actionSmazat_historii->setText("Historie není povolena");
    }
}

void MainWindow::check_version(){
    // zkontrolovat verzi, jestli nebyla vydána nová

    QUrl api_url = QUrl("https://api.github.com/repos/RxiPland/y2mate_desktop/releases/latest");

    QNetworkRequest request = QNetworkRequest(api_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.102 Safari/537.36");

    QNetworkReply *reply_check = manager.get(request);

    ui->label_3->setHidden(false);
    ui->label_4->setHidden(true);
    ui->label_3->setText("Kontroluji verzi");

    connect(reply_check, &QNetworkReply::downloadProgress,this, &MainWindow::downloadProgress);

    while (!reply_check->isFinished())
    {
        qApp->processEvents();
    }

    // zpracování response
    QString strReply = (QString)reply_check->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    QString newest_version = jsonObject["tag_name"].toString();

    if (newest_version != app_version && newest_version != ""){

        QMessageBox msgBox;
        msgBox.setWindowTitle("Aktualizace");
        msgBox.setText("Je dostupná novější verze y2mate desktop: " + newest_version + "\nVaše verze: " + app_version  +"\n\nPři instalaci nové verze se předchozí automaticky odstraní.");
        QAbstractButton* pButtonYes = msgBox.addButton("Otevřít odkaz", QMessageBox::YesRole);
        msgBox.addButton("Zrušit", QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton()==pButtonYes) {
            ShellExecute(0, 0, L"https://github.com/RxiPland/y2mate_desktop", 0, 0, SW_HIDE);
        }
    }

    reply_check->reset();
    reply_check->deleteLater();
}

void MainWindow::get_headers(QString location)
{
    // head request method & read headers
    // najde název souboru z headru a zapíše ho do globální proměnné
    // parametr location je URL k souboru na y2mate

    QNetworkRequest request;
    request.setUrl(QUrl(location));
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.102 Safari/537.36");

    QNetworkReply *reply_headers = manager.head(request);

    while (!reply_headers->isFinished())
    {
        qApp->processEvents();
    }

    // url is not working -> replace https with http
    if (reply_headers->error() != QNetworkReply::NoError){

        request.setUrl(QUrl(location.replace("https", "http")));
        reply_headers = manager.head(request);

        while (!reply_headers->isFinished())
        {
            qApp->processEvents();
        }
    }

    QString header = reply_headers->header(QNetworkRequest::ContentDispositionHeader).toString();
    nazev_souboru = "[Název nenalezen]";

    if(header.contains("filename")){

        QRegExp rx("filename=\\\"(.+)\\\";");
        int pos = rx.indexIn(header);
        int pozice = pos;   // nebude fungovat pokud se proměnná pos nevyužije

        if (pozice > -1) {
            nazev_souboru = rx.cap(1); // "y2mate.com%20-%20LAmour%20Toujours%20Hardstyle.mp3"
            nazev_souboru = QUrl::fromPercentEncoding(nazev_souboru.toUtf8());

            nazev_souboru.replace("y2mate.com - ", "");      // remove watermarku from video name
            nazev_souboru.replace("  ", " ");   // remove double spaces

            QString formaty_mp4[] = {"1080p", "720p", "480p", "360p", "240p", "144p"};
            QString formaty_mp3[] = {"320kbps", "256kbps", "192kbps", "128kbps", "96kbps", "64kbps"};

            for (int i=0; i<6; i++){
                nazev_souboru.replace("_" + formaty_mp4[i], "");    // odebrání kvality z názvu souboru
                nazev_souboru.replace("_" + formaty_mp3[i], "");
            }
        }
    }

    // free memory space
    reply_headers->reset();
    reply_headers->deleteLater();
}

void MainWindow::httpReadyRead()
{
    // This slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if (file){
        file->write(reply->readAll());
    }
}

void MainWindow::httpFinished()
{
    // http request byl dokončen

    QFileInfo fi;
    if (file){

        fi.setFile(file->fileName());
        file->close();
        file->deleteLater();
        file.reset();

        QStringList list_dir_path = cesta_k_souboru.split("/");
        list_dir_path.pop_back();
        QString dir_path = list_dir_path.join("\\") + "\\";

        if (!downloading_ffmpeg){

            disable_widgets(false);

            QMessageBox msgBox;
            msgBox.setWindowTitle("V pořádku");
            msgBox.setText("Soubor byl úspěšně stažen.");
            msgBox.addButton("Ok", QMessageBox::YesRole);
            QAbstractButton* pButtonOpen = msgBox.addButton("Otevřít soubor", QMessageBox::NoRole);
            QAbstractButton* pButtonEdit = msgBox.addButton("Upravit video", QMessageBox::NoRole);
            msgBox.exec();


            if (msgBox.clickedButton() == pButtonOpen) {
                // otevřít soubor

                cesta_k_souboru = "\"" + cesta_k_souboru + "\"";
                std::wstring command = cesta_k_souboru.toStdWString();

                ShellExecute(0, L"open", command.c_str(), 0, 0, SW_RESTORE);

            } else if(msgBox.clickedButton() == pButtonEdit){

                QFile file_settings("tools/ffmpeg.exe");

                if (!file_settings.exists()){
                    // ffmpeg doesn't exist

                    QMessageBox msgBox;
                    msgBox.setWindowTitle("ffmpeg");
                    msgBox.setText("Nepodařilo se najít FFmpeg!\nKliknutím na stáhnout se automaticky vloží do složky s programem");
                    QAbstractButton* pButtonDownload = msgBox.addButton("Stáhnout", QMessageBox::YesRole);
                    msgBox.addButton("Zrušit úpravu videa", QMessageBox::NoRole);
                    msgBox.exec();


                    if (msgBox.clickedButton() == pButtonDownload) {
                        // download ffmpeg to tools/ffmpeg.exe

                        MainWindow::disable_widgets(true);

                        ui->progressBar->setHidden(false);

                        ui->label_3->setHidden(false);
                        ui->label_4->setHidden(false);
                        ui->label_3->setText("Stahuji ffmpeg.exe");


                        // create directory tools
                        ThreadFunctions shellThread;
                        shellThread.operace = 2;  // Thread func

                        shellThread.ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
                        shellThread.ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
                        shellThread.ShExecInfo.hwnd = NULL;
                        shellThread.ShExecInfo.lpVerb = L"open";
                        shellThread.ShExecInfo.lpFile = L"cmd.exe";
                        shellThread.ShExecInfo.lpParameters = L"/C mkdir tools";
                        shellThread.ShExecInfo.lpDirectory = (QDir::currentPath()).toStdWString().c_str();
                        shellThread.ShExecInfo.nShow = SW_HIDE;
                        shellThread.ShExecInfo.hInstApp = NULL;

                        shellThread.start();

                        // wait for thread to complete
                        while(shellThread.isRunning()){
                            qApp->processEvents();
                        }


                        file = openFileForWrite("tools/ffmpeg.exe");
                        if (!file){
                            QMessageBox::critical(this, "Problém", "Nastal problém při vytváření souboru.\n\n" + cesta_k_souboru);
                            return;
                        }

                        QNetworkRequest request = QNetworkRequest(QUrl("https://github.com/RxiPland/y2mate_desktop/releases/download/v1.8.0/ffmpeg.exe"));
                        request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.102 Safari/537.36");

                        reply.reset();
                        reply.reset(manager.get(request));

                        downloading_ffmpeg = true;

                        connect(reply.get(), &QNetworkReply::finished, this, &MainWindow::httpFinished);
                        connect(reply.get(), &QIODevice::readyRead, this, &MainWindow::httpReadyRead);
                        connect(reply.get(), &QNetworkReply::downloadProgress,this, &MainWindow::downloadProgress);

                        return;
                    }

                } else{

                    QString koncovka = "." + (ui->comboBox->currentText()).split(" ")[0];

                    QStringList video_name_list = cesta_k_souboru.split("/").back().split(".");
                    video_name_list.pop_back();
                    QString video_name = video_name_list.join(".");

                    EditVideoWindow edit_window;
                    edit_window.set_info(video_name + koncovka, video_duration, dir_path);
                    this->hide();
                    edit_window.show();

                    // wait until edit_window is closed
                    while (!edit_window.isHidden())
                    {
                        qApp->processEvents();
                    }

                    MainWindow::center_window();
                    this->show();
                }
            }

        } else {
            // open edit video window after ffmpeg download

            downloading_ffmpeg = false;

            QFile file_settings("tools/ffmpeg.exe");

            if (file_settings.exists()){

                QMessageBox::about(this, "V pořádku", "FFmpeg byl úspěšně stažen. Nyní můžete začít upravovat videa.");

                if(!downloading_ffmpeg_menubar){

                    QString koncovka = "." + (ui->comboBox->currentText()).split(" ")[0];

                    QStringList video_name_list = cesta_k_souboru.split("/").back().split(".");
                    video_name_list.pop_back();
                    QString video_name = video_name_list.join(".");

                    EditVideoWindow edit_window;
                    edit_window.set_info(video_name + koncovka, video_duration, dir_path);
                    this->hide();
                    edit_window.show();

                    // wait until edit_window is closed
                    while (!edit_window.isHidden())
                    {
                        qApp->processEvents();
                    }

                    MainWindow::center_window();
                    this->show();

                } else {

                    downloading_ffmpeg_menubar = false;
                }

            } else{

                QMessageBox::about(this, "Chyba", "ffmpeg.exe se nepodařilo stáhnout!\n\nMožné chyby:\n1) Internet není dostupný\n2) github.com není dostupný");
            }
        }
    }

    QNetworkReply::NetworkError error = reply->error();
    const QString &errorString = reply->errorString();

    reply.reset();
    reply->deleteLater();

    if (error != QNetworkReply::NoError) {
        QFile::remove(fi.absoluteFilePath());
    }


    if(!downloading_ffmpeg){

        nazev_souboru = "";
        video_duration = "";

        disable_widgets(false);
        on_pushButton_2_clicked();
    }
}

std::unique_ptr<QFile> MainWindow::openFileForWrite(const QString &fileName)
{
    std::unique_ptr<QFile> file = std::make_unique<QFile>(fileName);

    file->open(QIODevice::WriteOnly);

    return file;
}

void MainWindow::get(QString url, QString koncovka)
{
    // GET

    MainWindow::disable_widgets(true);

    QString upraveny_nazev_souboru = "";

    int nazev_videa_hash = hodnoty_nastaveni[0];
    if (nazev_videa_hash){

        // název bude nahrazen hashem
        upraveny_nazev_souboru = nazev_souboru_hash;

    } else{

        // odstranit mezeru na konci
        if (nazev_souboru.endsWith(" ")){
            int pos = nazev_souboru.lastIndexOf(QChar(' '));
            nazev_souboru = nazev_souboru.left(pos);
        }

        bool nahradit_podtrzitkem = hodnoty_nastaveni[1];
        if (nahradit_podtrzitkem){
            upraveny_nazev_souboru = nazev_souboru;
            upraveny_nazev_souboru.replace(" ", "_");

        } else{
            upraveny_nazev_souboru = nazev_souboru;
        }
    }

    QString temp_cesta_k_souboru = QFileDialog::getSaveFileName(this, "Uložit soubor", last_location_path + upraveny_nazev_souboru, koncovka);

    if (temp_cesta_k_souboru != ""){

        cesta_k_souboru = temp_cesta_k_souboru;
        MainWindow::save_last_path();

        ui->progressBar->setHidden(false);

        ui->label_3->setHidden(false);
        ui->label_4->setHidden(false);
        ui->label_3->setText("Stahuji soubor");

        file = openFileForWrite(cesta_k_souboru);
        if (!file){
            QMessageBox::critical(this, "Problém", "Nastal problém při otevírání souboru.\n\n" + cesta_k_souboru);
            return;
        }

        QNetworkRequest request;
        request.setUrl(QUrl(url));
        request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.102 Safari/537.36");    

        // check if url is working
        QNetworkReply *reply_headers = manager.head(request);

        while (!reply_headers->isFinished())
        {
            qApp->processEvents();
        }

        // url is not working -> replace https with http
        if(reply_headers->error() != QNetworkReply::NoError){

            request.setUrl(QUrl(url.replace("https", "http")));
        }

        reply.reset();
        reply.reset(manager.get(request));

        connect(reply.get(), &QNetworkReply::finished, this, &MainWindow::httpFinished);
        connect(reply.get(), &QIODevice::readyRead, this, &MainWindow::httpReadyRead);
        connect(reply.get(), &QNetworkReply::downloadProgress,this, &MainWindow::downloadProgress);

    } else {
        disable_widgets(false);
    }
}

void MainWindow::post(QString location, QByteArray data, int druh_promenne)
{
    // POST

    QNetworkRequest request;
    request.setUrl(QUrl(location));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded; charset=UTF-8");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.102 Safari/537.36");

    // check if url is working
    QNetworkReply *reply_headers = manager.head(request);

    while (!reply_headers->isFinished())
    {
        qApp->processEvents();
    }

    // url is not working -> replace https with http
    if(reply_headers->error() != QNetworkReply::NoError){

        request.setUrl(QUrl(location.replace("https", "http")));
    }
    reply_headers->reset();
    reply_headers->deleteLater();

    QNetworkReply *reply_post = manager.post(request, data);

    if (druh_promenne == 1){
        ui->label_3->setText("Hledám dostupné formáty");

    } else if (druh_promenne == 2){
        ui->label_3->setText("Získávám odkaz na stažení souboru");

    } else if (druh_promenne == 3){
        ui->label_3->setText("Získávám název videa");

    } else if (druh_promenne == 4){
        ui->label_3->setText("Čekám na y2mate [10s]");
    }

    ui->label_3->setHidden(false);

    if (druh_promenne != 4){
        ui->progressBar->setHidden(false);
    }

    connect(reply_post, &QNetworkReply::downloadProgress,this, &MainWindow::downloadProgress);


    while (!reply_post->isFinished())
    {
        qApp->processEvents();
    }

    QString response_data = reply_post->readAll();

    if (druh_promenne == 1){
        response_najit_formaty = response_data;

    } else if (druh_promenne == 2 || druh_promenne == 3 || druh_promenne == 4){

        response = response_data;
    }

    reply_post->reset();
    reply_post->deleteLater();
}

bool MainWindow::checkdone_y2mate(QString url, QByteArray post_data){
    // when y2mate returns: it may take a few minutes

    MainWindow::post(url, post_data, 4);

    if(response.contains("it may take a few minutes")){
        return true;

    } else{
        return false;
    }
}

QList<QString> najit_data(){
    // najít data [_id, video_id]  z response

    QList<QString> udaje; // prvni: _id; druhy: video_id

    QString _id = "error";
    QString video_id = "error";

    QRegExp rx("k__id = \\\\\\\"(\\w+)");
    int pos = rx.indexIn(response_najit_formaty);
    int pozice = pos;   // nebude fungovat pokud se proměnná pos nevyužije

    if (pozice > -1) {
        _id = rx.cap(1); // "62fd01c3f1a87588248b45ba"
    }
    udaje.append(_id);

    QRegExp rx2("k_data_vid = \\\\\\\"(.+)\\\\\\\"; var k_data_vtitle");
    pos = rx2.indexIn(response_najit_formaty);
    pozice = pos;   // nebude fungovat pokud se proměnná pos nevyužije

    if (pozice > -1) {
        video_id = rx2.cap(1); // "H10SQesAcwE"
    }
    udaje.append(video_id);

    return udaje; // [_id, video_id]
}

bool MainWindow::get_nazev(){
    // get video name
    // using function get_headers()
    // return true, if y2mate response is: it may take a few minutes

    QString video_quality_post;

    if(!(response_najit_formaty.contains(selected_video_quality) || response_najit_formaty.contains(selected_video_quality))){

        QMessageBox::information(this, "Oznámení", "Nepovedlo se najít video s vámi přednastavenou kvalitou \"" + selected_video_quality + "\" a tudíž pro hledání názvu bude použita defaultní 128 kbps");
        video_quality_post = "128 kbps";

    } else{
        video_quality_post = selected_video_quality;
    }

    QList<QString> udaje;
    udaje = najit_data();

    QString _id = udaje[0];
    QString k_data_vid = udaje[1];

    if ((_id != "error") && (k_data_vid != "error")){

        QByteArray data;

        data.append("type=youtube");
        data.append("&");
        data.append("_id=");
        data.append(QUrl::toPercentEncoding(_id).toStdString());
        data.append("&");
        data.append("v_id=");
        data.append(QUrl::toPercentEncoding(k_data_vid).toStdString());
        data.append("&");
        data.append("ajax=1");
        data.append("&");
        data.append("token=");
        data.append("&");

        std::string quality_int;

        if(video_quality_post.contains("kbps")){

            quality_int = video_quality_post.replace(" kbps", "").toStdString();

            data.append("ftype=mp3");
            data.append("&");
            data.append("fquality=" + quality_int);

            MainWindow::post("https://www.y2mate.com/mates/mp3Convert", data, 2);     // post request na získání odkazu ke stažení

        } else if(video_quality_post.back() == 'p'){

            quality_int = video_quality_post.replace("p", "").toStdString();

            data.append("ftype=mp4");
            data.append("&");
            data.append("fquality=" + quality_int);

            MainWindow::post("https://www.y2mate.com/mates/convert", data, 2);     // post request na získání odkazu ke stažení

        } else{
            QMessageBox::warning(this, "Chyba", "video_quality_post není \'p\' ani \'kbps\' !");
            return false;
        }

        QRegExp rx("href=\\\\\\\"(.+)\\\\\\\" rel=");
        int pos = rx.indexIn(response);
        int pozice = pos;   // nebude fungovat pokud se proměnná pos nevyužije

        if (response.contains("it may take a few minutes")){

            ui->label_3->setText("Čekám na y2mate [10s]");
            ui->label_3->setHidden(false);
            return true;
        }

        QString odkaz_na_stazeni = "error";
        if (pozice > -1) {
            odkaz_na_stazeni = rx.cap(1); // download link (https://)
        }


        if (odkaz_na_stazeni != "error"){

            odkaz_na_stazeni.replace("\\", "");
            get_headers(odkaz_na_stazeni);

            if (nazev_souboru == ""){
                QMessageBox::critical(this, "Chyba", "Název se napoprvé nepodařilo získat. Program to zkusí znovu.");
                get_headers(odkaz_na_stazeni);
            }
        }

    } else {
        nazev_souboru = "[Název nenalezen]";
    }


    nazev_souboru = nazev_souboru.trimmed();  // remove whitespaces from start and end

    return false;
}

void MainWindow::on_pushButton_clicked(){
    // pushButton je najít/stáhnout

    QString text_tlacitka = ui->pushButton->text();
    yt_video_link = ui->lineEdit->text();

    disable_widgets(true);

    if (text_tlacitka == "Najít"){

        QStringList prvky = {"http", "://", "youtu"};
        bool chyba_url = false;

        // kontrola správnosti url
        for (int i=0; i<3; i++){

            if (!yt_video_link.contains(prvky[i])) {

                QMessageBox::critical(this, "Problém", "Zadejte kompletní URL adresu\n\nPříklady:\n1. https://www.youtube.com/watch?v=DMtFhACPnTY\n2. https://youtu.be/DMtFhACPnTY");

                chyba_url = true;
                break;
            }
        }

        if (chyba_url == false){

            // post request na získání informací o url
            // dostupné kvality u mp4/mp3, délka videa

            ui->lineEdit->setClearButtonEnabled(false);

            QByteArray data;

            data.append("url=");
            data.append(QUrl::toPercentEncoding(yt_video_link).toStdString());
            data.append("&");
            data.append("q_auto=1");
            data.append("&");
            data.append("ajax=1");

            MainWindow::post("https://www.y2mate.com/mates/mp3/ajax", data, 1);     // post request na získání informací o videu


            if (response_najit_formaty == "error"){

                QMessageBox::critical(this, "Chyba", "[kód 1] Problém v post requestu!");
                ui->lineEdit->setClearButtonEnabled(true);
            }
            else if (response_najit_formaty.contains("Video not found")) {

                QMessageBox::critical(this, "Chyba", "Video pod tímto odkazem neexistuje!");
                ui->lineEdit->setClearButtonEnabled(true);
            }
            else if (response_najit_formaty != ""){

                ui->lineEdit->setReadOnly(true);        // read only na line edit s URL videa
                ui->label->setHidden(false);
                ui->label_2->setHidden(false);

                QRegExp rx("Duration: (..:..:..)");
                int pos = rx.indexIn(response_najit_formaty);
                int pozice = pos;   // nebude fungovat pokud se proměnná pos nevyužije

                if (pozice > -1) {
                    video_duration = rx.cap(1); // xx:xx:xx čas

                    ui->label->setText("Délka videa: " + video_duration);
                }

                ui->pushButton->setText("Stáhnout");    // změna najít na stáhnout
                ui->horizontalSpacer->changeSize(20, 35);   // tlačítko "stáhnout" se vyrovná s boxem s kvalitou

                ui->comboBox->setHidden(false);     // formát (mp3, mp4)
                ui->pushButton_2->setHidden(false); // tlačítko zrušit
                ui->lineEdit->setClearButtonEnabled(false);

                // vyresetování arrayů

                for (int i=0; i<6; i++){
                    nalezene_formaty_mp3[i] = "nic";
                    nalezene_formaty_mp4[i] = "nic";
                }

                // najít dostupné formáty (z response)

                QString formaty_mp3[] = {"320 kbps", "256 kbps", "192 kbps", "128 kbps", "96 kbps", "64 kbps"};

                for (int i=0; i<6; i++){

                    if (response_najit_formaty.contains(formaty_mp3[i])){
                        if (formaty_mp3[i] == "128 kbps"){
                            nalezene_formaty_mp3[i] = formaty_mp3[i] + " (Standard)";
                        } else {
                            nalezene_formaty_mp3[i] = formaty_mp3[i];
                        }
                    }
                }

                QString formaty_mp4[] = {"1080p", "720p", "480p", "360p", "240p", "144p"};

                for (int i=0; i<6; i++){

                    if (response_najit_formaty.contains(formaty_mp4[i])) {
                        nalezene_formaty_mp4[i] = formaty_mp4[i];
                    }
                }

                // získat název videa
                while(MainWindow::get_nazev()){

                    ThreadFunctions sleep_thread;
                    sleep_thread.operace = 1;
                    sleep_thread.sleep_time = 10;
                    sleep_thread.start();

                    while(sleep_thread.isRunning()){

                        qApp->processEvents();
                    }
                }

                nazev_souboru.replace(".mp3", "");
                nazev_souboru.replace(".mp4", "");
                nazev_souboru.replace(".webm", "");
                ui->label_2->setText("Název videa: " + nazev_souboru);    // název videa do labelu

                // získat náhodný hash
                QList<QString> udaje;
                udaje = najit_data();
                nazev_souboru_hash = udaje[0];    // např. "62fd01c3f1a87588248b45ba"


                // save searched video to history
                if (hodnoty_nastaveni[3]){
                    MainWindow::history_soubor("save", nazev_souboru + " /;/ " + video_duration + " /;/ " + yt_video_link);
                    MainWindow::load_history();
                }

            } else{

                qInfo() << response_najit_formaty;

                QMessageBox::critical(this, "Chyba", "[kód 2] Nastala neznámá chyba\n\n1) Zkontrolujte připojení k síti");
                ui->lineEdit->setClearButtonEnabled(true);
            }
        }

    }else if(text_tlacitka == "Stáhnout"){

        disable_widgets(true);

        QString text_format = ui->comboBox->currentText();
        QString text_kvalita = ui->comboBox_2->currentText();

        if (text_format == "<Vyberte formát>"){

            QMessageBox::critical(this, "Chyba", "Vyberte formát!");

        } else if (text_kvalita == "<Vyberte kvalitu>"){

            QMessageBox::critical(this, "Chyba", "Vyberte kvalitu!");

        } else {
            // v pořádku

            if (text_format == "mp3 (pouze zvuk)"){

                // stáhnutí zvuku

                QList<QString> udaje;

                udaje = najit_data();   // return [_id, video_id]

                QString _id = udaje[0];
                QString k_data_vid = udaje[1];

                if ((_id != "error") && (k_data_vid != "error")){

                    QByteArray data;

                    data.append("type=youtube");
                    data.append("&");
                    data.append("_id=");
                    data.append(QUrl::toPercentEncoding(_id).toStdString());
                    data.append("&");
                    data.append("v_id=");
                    data.append(QUrl::toPercentEncoding(k_data_vid).toStdString());
                    data.append("&");
                    data.append("ajax=1");
                    data.append("&");
                    data.append("token=");
                    data.append("&");
                    data.append("ftype=mp3");
                    data.append("&");
                    data.append("fquality=");

                    QStringList splitted_kvalita = text_kvalita.split(" ");
                    data.append(splitted_kvalita[0].toStdString());

                    MainWindow::post("https://www.y2mate.com/mates/mp3Convert", data, 2);     // post request na získání odkazu ke stažení

                    bool error = false;

                    if (response == "error"){
                        QMessageBox::critical(this, "Chyba", "[kód 3] Problém v post requestu!");
                        error = true;

                    } else if(response.contains("it may take a few minutes")){
                        // y2mate response: it may take a few minutes

                        while(MainWindow::checkdone_y2mate("https://www.y2mate.com/mates/mp3Convert", data)){

                            ThreadFunctions sleep_thread;
                            sleep_thread.operace = 1;
                            sleep_thread.sleep_time = 10;
                            sleep_thread.start();

                            while(sleep_thread.isRunning()){

                                qApp->processEvents();
                            }
                        }

                    } else if (!response.contains("Download")) {
                        // negace

                        QMessageBox::critical(this, "Chyba", "[kód 4] Nepovedlo se stáhnout mp3, zkuste to znovu");
                        error = true;
                    }


                    if (response.contains("Download") && !error){

                        QString odkaz_na_stazeni = "error";


                        QRegExp rx("href=\\\\\\\"(.+)\\\\\\\" rel=");
                        int pos = rx.indexIn(response);
                        int pozice = pos;   // nebude fungovat pokud se proměnná pos nevyužije

                        if (pozice > -1) {
                            odkaz_na_stazeni = rx.cap(1); // download link (https://)
                        }

                        if (odkaz_na_stazeni != "error"){

                            odkaz_na_stazeni.replace("\\", "");
                            MainWindow::get(odkaz_na_stazeni, "Zvukový soubor (*.mp3)");

                            return;

                        }else{

                            QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Problém", "[kód 5] Zvukový soubor se nepodařilo začít stahovat!\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                            if (reply_box == QMessageBox::Yes){
                                    QString odkaz = "https://www.y2mate.com/youtube-mp3/" + k_data_vid;
                                    ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
                            }
                        }
                    }

                } else if(_id == "error"){

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "[kód 6] Problém!\n_id se nepodařilo získat\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            QString odkaz = "https://www.y2mate.com/youtube-mp3/" + k_data_vid;
                            ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
                    }


                } else if(k_data_vid == "error"){

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "[kód 7] Problém!\nk_data_vid se nepodařilo získat\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            QString odkaz = "https://www.y2mate.com/youtube-mp3/" + k_data_vid;
                            ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
                    }

                } else{

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "[kód 8] Nastala neznámá chyba (stahování zvuku)\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            QString odkaz = "https://www.y2mate.com/youtube-mp3/" + k_data_vid;
                            ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
                    }
                }

            } else if (text_format == "mp4 (video)"){

                // stáhnutí videa

                QList<QString> udaje;

                udaje = najit_data();   // funkce pro získání _id & k_data_vid (do requestu)

                QString _id = udaje[0];
                QString k_data_vid = udaje[1];

                if ((_id != "error") && (k_data_vid != "error")){

                    QByteArray data;

                    data.append("type=youtube");
                    data.append("&");
                    data.append("_id=");
                    data.append(QUrl::toPercentEncoding(_id).toStdString());
                    data.append("&");
                    data.append("v_id=");
                    data.append(QUrl::toPercentEncoding(k_data_vid).toStdString());
                    data.append("&");
                    data.append("ajax=1");
                    data.append("&");
                    data.append("token=");
                    data.append("&");
                    data.append("ftype=mp4");
                    data.append("&");
                    data.append("fquality=");

                    QStringList splitted_kvalita = text_kvalita.split("p");
                    data.append(splitted_kvalita[0].toStdString());

                    MainWindow::post("https://www.y2mate.com/mates/convert", data, 2);     // post request na získání odkazu ke stažení

                    bool error = false;

                    if (response == "error"){
                        QMessageBox::critical(this, "Chyba", "[kód 9] Problém v post requestu!");
                        error = true;

                    } else if(response.contains("it may take a few minutes")){
                        // y2mate response: it may take a few minutes

                        while(MainWindow::checkdone_y2mate("https://www.y2mate.com/mates/convert", data)){

                            ThreadFunctions sleep_thread;
                            sleep_thread.operace = 1;
                            sleep_thread.sleep_time = 10;
                            sleep_thread.start();

                            while(sleep_thread.isRunning()){

                                qApp->processEvents();
                            }
                        }

                    } else if (response.contains("Refresh to try again")){

                        QMessageBox::critical(this, "Chyba", "[kód 10] Nepovedlo se stáhnout mp4, zkuste to zachvíli.");
                        error = true;

                    } else if (!response.contains("Download")){

                        QMessageBox::critical(this, "Chyba", "[kód 11] Nepovedlo se stáhnout mp4");
                        error = true;
                    }


                    if (response.contains("Download") && !error){

                        QString odkaz_na_stazeni = "error";

                        QRegExp rx("href=\\\\\\\"(.+)\\\\\\\" rel=");
                        int pos = rx.indexIn(response);
                        int pozice = pos;   // nebude fungovat pokud se proměnná pos nevyužije

                        if (pozice > -1) {
                            odkaz_na_stazeni = rx.cap(1); // download link (https://)
                        }

                        if (odkaz_na_stazeni != "error"){

                            odkaz_na_stazeni.replace("\\", "");
                            MainWindow::get(odkaz_na_stazeni, "Video (*.mp4)");

                            return;

                        } else{
                            QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Problém", "[kód 12] Video se nepodařilo začít stahovat!\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                            if (reply_box == QMessageBox::Yes){
                                    QString odkaz = "https://www.y2mate.com/youtube-mp3/" + k_data_vid;
                                    ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
                            }
                        }
                    }

                } else if(_id == "error"){

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "[kód 12] Problém!\n_id se nepodařilo získat\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            QString odkaz = "https://www.y2mate.com/youtube-mp3/" + k_data_vid;
                            ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
                    }

                } else if(k_data_vid == "error"){

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "[kód 13] Problém!\nk_data_vid se nepodařilo získat\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            QString odkaz = "https://www.y2mate.com/youtube-mp3/" + k_data_vid;
                            ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
                    }

                } else{

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "[kód 14] Nastala neznámá chyba (stahování videa)\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            QString odkaz = "https://www.y2mate.com/youtube-mp3/" + k_data_vid;
                            ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
                    }
                }
            }
        }
    }

    // enable widgets after requests
    disable_widgets(false);
}

void MainWindow::on_pushButton_2_clicked()
{
    // pushButton_2 je tlačítko zrušit

    ui->lineEdit->setReadOnly(false);        // odebrání read only na line edit s URL
    ui->lineEdit->clear();
    ui->lineEdit->setClearButtonEnabled(true);
    ui->pushButton->setText("Najít");    // změna stáhnout na najít
    ui->pushButton->setDisabled(false);
    ui->pushButton_2->setHidden(true);
    ui->label->setHidden(true);
    ui->label->clear();
    ui->label_2->setHidden(true);
    ui->label_2->clear();

    ui->label_3->setHidden(true);
    ui->label_4->setHidden(true);

    ui->progressBar->setHidden(true);
    ui->progressBar->setValue(0);

    ui->comboBox->setHidden(true);
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setHidden(true);
    ui->comboBox_2->setCurrentIndex(0);

    ui->horizontalSpacer->changeSize(250, 35);

    response = "";
    nazev_souboru = "";
}

void MainWindow::load_settings(){
    // načtení hodnot nastavení do hodnoty_nastaveni[]

    QFile file("nastaveni.txt");

    if (file.exists()){
        file.open(QIODevice::ReadOnly);

        QByteArray obsah = file.readAll();
        file.close();

        QString obsah_nastaveni = QTextCodec::codecForMib(106)->toUnicode(obsah);
        QStringList rows_nastaveni = obsah_nastaveni.split("\r\n");

        QString hledat_nazev_videa = rows_nastaveni[0];
        QString nahradit_podtrzitkem = rows_nastaveni[1];
        QString check_update = rows_nastaveni[2];
        QString zaznamenavat_historii = rows_nastaveni[3];
        QString last_location = rows_nastaveni[4];
        selected_video_quality = rows_nastaveni[5].split(" /;/ ").back();


        if (rows_nastaveni[4].contains(" /;/ ")){
            QStringList last_location_row = rows_nastaveni[4].split(" /;/ ");
            last_location = last_location_row[0];

            last_location_path = last_location_row[1];

            if (last_location_path == "" || last_location_path == " "){

                last_location_path = "/";
            }

        } else{
            last_location_path = "/";
        }


        // defaultní hodnoty, pokud budou řádky prázdné (např. při přechodu ze starší verze na novou)
        if (hledat_nazev_videa == ""){
            hledat_nazev_videa = "0";
        }

        if (nahradit_podtrzitkem == ""){
            nahradit_podtrzitkem = "0";
        }

        if (check_update == ""){
            check_update = "1";
        }

        if (zaznamenavat_historii == ""){
            zaznamenavat_historii = "1";
        }

        if (last_location == ""){
            last_location = "1";
        }

        if(selected_video_quality == ""){
            selected_video_quality = "128 kbps";
        }

        hodnoty_nastaveni[0] = hledat_nazev_videa.contains("1");  // zapnutí nahradí název souboru hashem
        hodnoty_nastaveni[1] = nahradit_podtrzitkem.contains("1");   // zapnutí nahrazuje mezery podtržítkama v názvu souboru při ukládání
        hodnoty_nastaveni[2] = check_update.contains("1");   // zapnutí bude automaticky kontrolovat novou verzi při startu
        hodnoty_nastaveni[3] = zaznamenavat_historii.contains("1");  // zapnutí bude zaznamenávat historii
        hodnoty_nastaveni[4] = last_location.contains("1");  // zapnutí bude otevírat ukládací dialog v této cestě

    } else{
        hodnoty_nastaveni[0] = false; // defaultní hodnota false
        hodnoty_nastaveni[1] = false;  // defaultní hodnota false
        hodnoty_nastaveni[2] = true; // defaultní hodnota true
        hodnoty_nastaveni[3] = true; // defaultní hodnota true
        hodnoty_nastaveni[4] = true; // defaultní hodnota true
    }
}

void MainWindow::disable_widgets(bool vypnout){

    // zakáže/povolí widgety
    // většinou během downloadu

    ui->pushButton->setDisabled(vypnout);
    ui->pushButton_2->setDisabled(vypnout);

    ui->lineEdit->setDisabled(vypnout);

    ui->comboBox->setDisabled(vypnout);
    ui->comboBox_2->setDisabled(vypnout);

    ui->actionPou_t->setDisabled(vypnout);
    ui->actionPou_t_2->setDisabled(vypnout);
    ui->actionPou_t_3->setDisabled(vypnout);
    ui->actionPou_t_4->setDisabled(vypnout);
    ui->actionPou_t_5->setDisabled(vypnout);

    ui->actionOtev_t_soubor->setDisabled(vypnout);
}

void MainWindow::open_yt_video(int row_order){
    // search for yt video link

    QStringList file_data = MainWindow::history_soubor("load");

    QStringList values = file_data[row_order].split(" /;/ ");
    QString odkaz = values[2];  // yt video link

    ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
}

void MainWindow::apply_yt_video(int row_order){
    // apply youtube video from history to search

    // prepare GUI (reset)
    MainWindow::disable_widgets(false);
    MainWindow::on_pushButton_2_clicked();

    QStringList file_data = MainWindow::history_soubor("load");
    QStringList values = file_data[row_order].split(" /;/ ");
    QString odkaz = values[2];  // yt video link

    // set yt video link to lineEdit instead of user
    ui->lineEdit->setText(odkaz);

    // activate search function
    MainWindow::on_pushButton_clicked();
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    // při změně formátu v boxu se načtou příslušné typy kvalit (u mp3: 128kbps, 192kbps, ...)
    // to stejné u mp4 (720p, ...)

    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("<Vyberte kvalitu>");

    if (arg1 == "mp3 (pouze zvuk)"){
        // načíst z proměnné nalezene_formaty_mp3

        for (int i=0; i<6; i++){

            if (nalezene_formaty_mp3[i] != "nic"){

                ui->comboBox_2->addItem(nalezene_formaty_mp3[i]);
            }
        }

        ui->comboBox_2->setHidden(false);
    }
    else if (arg1 == "mp4 (video)"){
        // načíst z proměnné nalezene_formaty_mp4

        for (int i=0; i<6; i++){

            if (nalezene_formaty_mp4[i] != "nic"){

                ui->comboBox_2->addItem(nalezene_formaty_mp4[i]);
            }
        }

        ui->comboBox_2->setHidden(false);
    }
    else {
        ui->comboBox_2->setHidden(true);
    }
}

void MainWindow::downloadProgress(qint64 ist, qint64 max)
{

    ui->progressBar->setRange(0,max);
    ui->progressBar->setValue(ist);

    ui->label_4->setText(QString::number(ist/1000000) + "." + QString::number(ist/100000).back() + " / " + QString::number(max/1000000) + "." + QString::number(max/100000).back() + " MB");

    if(max == ist){
        ui->label_3->setHidden(true);
        ui->label_4->setHidden(true);
        ui->label_3->clear();
        ui->label_4->clear();
        ui->progressBar->setHidden(true);
        ui->progressBar->setValue(0);
    }
}

void MainWindow::save_last_path(){

    // pokud je povoleno
    if(hodnoty_nastaveni[4] && cesta_k_souboru != ""){

        QFile file("nastaveni.txt");

        if (file.exists()){
            file.open(QIODevice::ReadOnly);

            QByteArray obsah = file.readAll();
            file.close();

            QString obsah_souboru = QTextCodec::codecForMib(106)->toUnicode(obsah);
            QStringList rows_settings = obsah_souboru.split("\r\n");

            int pocet_rows = rows_settings.count();

            for(int i=0; i < 6-pocet_rows; i++){
                rows_settings.append("");
            }

            QStringList adresar_list = cesta_k_souboru.split("/");
            adresar_list.pop_back();
            last_location_path = adresar_list.join("/") + "/";

            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);

            for(int i=0; i < pocet_rows; i++){
                if (i==4){
                    out << "LAST_LOCATION 1" << " /;/ "  << last_location_path << "\n";

                } else{
                    if(rows_settings[i] != ""){
                        out << rows_settings[i] << "\n";
                    }
                }
            }
            file.close();
        }
    }
}



void MainWindow::on_lineEdit_returnPressed()
{
    // zmáčknutí enteru v line editu při zadávání url

    on_pushButton_clicked();
}

void MainWindow::on_actiony2mate_com_triggered()
{
    //system("start https://www.y2mate.com");

    ShellExecute(0, 0, L"https://www.y2mate.com", 0, 0, SW_HIDE);
}


void MainWindow::on_actionzdrojovy_kod_triggered()
{
    // otevřít github se zdrojovým kódem

    ShellExecute(0, 0, L"https://github.com/RxiPland/y2mate_desktop", 0, 0, SW_HIDE);
}

void MainWindow::on_actionNastaven_triggered()
{
    // open settings window

    settings_dialog nastaveni_dialog;
    nastaveni_dialog.setModal(true);
    nastaveni_dialog.set_version(app_version);
    this->hide();
    nastaveni_dialog.exec();

    MainWindow::center_window();
    this->show();

    MainWindow::load_settings();  // načte nastavení ze souboru
    MainWindow::load_history();  // načte historii
}

void MainWindow::on_actionSmazat_historii_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Vymazat historii");
    msgBox.setText("Opravdu chcete smazat historii?");
    QAbstractButton* pButtonYes = msgBox.addButton("Smazat", QMessageBox::YesRole);
    msgBox.addButton("Zrušit", QMessageBox::NoRole);
    msgBox.exec();

    if (msgBox.clickedButton() == pButtonYes) {

        MainWindow::history_soubor("delete");
    }

    MainWindow::load_history();  // aktualizuje historii
}


// open youtube video link functions
void MainWindow::on_actionOtev_t_triggered()
{
    MainWindow::open_yt_video(0);
}

void MainWindow::on_actionOtev_t_2_triggered()
{
    MainWindow::open_yt_video(1);
}

void MainWindow::on_actionOtev_t_3_triggered()
{
    MainWindow::open_yt_video(2);
}

void MainWindow::on_actionOtev_t_4_triggered()
{
    MainWindow::open_yt_video(3);
}

void MainWindow::on_actionOtev_t_5_triggered()
{
    MainWindow::open_yt_video(4);
}


// apply button functions in history tab
void MainWindow::on_actionPou_t_triggered()
{
    MainWindow::apply_yt_video(0);
}

void MainWindow::on_actionPou_t_2_triggered()
{
    MainWindow::apply_yt_video(1);
}

void MainWindow::on_actionPou_t_3_triggered()
{
    MainWindow::apply_yt_video(2);
}

void MainWindow::on_actionPou_t_4_triggered()
{
    MainWindow::apply_yt_video(3);
}

void MainWindow::on_actionPou_t_5_triggered()
{
    MainWindow::apply_yt_video(4);
}

void MainWindow::on_actionOtev_t_soubor_triggered()
{

    QFile file_settings("tools/ffmpeg.exe");

    if (!file_settings.exists()){
        // ffmpeg doesn't exist

        QMessageBox msgBox;
        msgBox.setWindowTitle("ffmpeg");
        msgBox.setText("Nepodařilo se najít FFmpeg!\nKliknutím na stáhnout se automaticky vloží do složky s programem");
        QAbstractButton* pButtonDownload = msgBox.addButton("Stáhnout", QMessageBox::YesRole);
        msgBox.addButton("Zrušit úpravu videa", QMessageBox::NoRole);
        msgBox.exec();


        if (msgBox.clickedButton() == pButtonDownload) {
            // download ffmpeg to tools/ffmpeg.exe

            MainWindow::disable_widgets(true);

            ui->progressBar->setHidden(false);

            ui->label_3->setHidden(false);
            ui->label_4->setHidden(false);
            ui->label_3->setText("Stahuji ffmpeg.exe");

            // create directory tools
            ThreadFunctions shellThread;
            shellThread.operace = 2;  // Thread func

            shellThread.ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
            shellThread.ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
            shellThread.ShExecInfo.hwnd = NULL;
            shellThread.ShExecInfo.lpVerb = L"open";
            shellThread.ShExecInfo.lpFile = L"cmd.exe";
            shellThread.ShExecInfo.lpParameters = L"/C mkdir tools";
            shellThread.ShExecInfo.lpDirectory = (QDir::currentPath()).toStdWString().c_str();
            shellThread.ShExecInfo.nShow = SW_HIDE;
            shellThread.ShExecInfo.hInstApp = NULL;

            shellThread.start();

            // wait for thread to complete
            while(shellThread.isRunning()){
                qApp->processEvents();
            }

            file = openFileForWrite("tools/ffmpeg.exe");
            if (!file){
                QMessageBox::critical(this, "Problém", "Nastal problém při vytváření souboru.\n\n" + cesta_k_souboru);
                return;
            }

            QNetworkRequest request = QNetworkRequest(QUrl("https://github.com/RxiPland/y2mate_desktop/releases/download/v1.8.0/ffmpeg.exe"));
            request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.102 Safari/537.36");

            reply.reset();
            reply.reset(manager.get(request));

            downloading_ffmpeg = true;
            downloading_ffmpeg_menubar = true;

            connect(reply.get(), &QNetworkReply::finished, this, &MainWindow::httpFinished);
            connect(reply.get(), &QIODevice::readyRead, this, &MainWindow::httpReadyRead);
            connect(reply.get(), &QNetworkReply::downloadProgress,this, &MainWindow::downloadProgress);

            while(downloading_ffmpeg){
                qApp->processEvents();
            }

            downloading_ffmpeg_menubar = false;

            MainWindow::disable_widgets(false);
            return;
        }

    } else{

        std::wstring command;

        QString temp_cesta_k_souboru = QFileDialog::getOpenFileName(this, "Otevřít soubor", last_location_path, "Soubory (*.mp4 *.mp3 *.wav *.ogg)");

        if (temp_cesta_k_souboru != ""){

            if(!temp_cesta_k_souboru.contains(".")){

                QMessageBox::warning(this, "Nastala chyba", "Vyberte soubor s koncovkou!");
                return;
            }

            QStringList list_dir_path = temp_cesta_k_souboru.split("/");
            list_dir_path.pop_back();
            QString dir_path = list_dir_path.join("\\") + "\\";

            MainWindow::disable_widgets(true);

            QString koncovka;
            koncovka = "." + temp_cesta_k_souboru.split(".").back();

            QStringList video_name_list = temp_cesta_k_souboru.split("/").back().split(".");
            video_name_list.pop_back();
            QString video_name = video_name_list.join(".");

            // get duration
            command = ("/C ffmpeg.exe -i \"" + temp_cesta_k_souboru + "\" > ffmpeg_output_temp.txt 2>&1").toStdWString();


            ThreadFunctions shellThread;
            shellThread.operace = 2;  // Thread func

            shellThread.ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
            shellThread.ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
            shellThread.ShExecInfo.hwnd = NULL;
            shellThread.ShExecInfo.lpVerb = L"open";
            shellThread.ShExecInfo.lpFile = L"cmd.exe";
            shellThread.ShExecInfo.lpParameters = command.c_str();
            shellThread.ShExecInfo.lpDirectory = (QDir::currentPath()+ "/tools").toStdWString().c_str();
            shellThread.ShExecInfo.nShow = SW_HIDE;
            shellThread.ShExecInfo.hInstApp = NULL;

            shellThread.start();

            // wait for thread to complete
            while(shellThread.isRunning()){
                qApp->processEvents();
            }

            QFile output_file("tools/ffmpeg_output_temp.txt");
            QString video_duration_file;

            if (output_file.exists()){
                output_file.open(QIODevice::ReadOnly);

                QByteArray obsah_byte = output_file.readAll();
                output_file.close();

                QString obsah = QTextCodec::codecForMib(106)->toUnicode(obsah_byte);

                QRegExp rx("Duration: (..:..:..)");
                int pos = rx.indexIn(obsah);
                int pozice = pos;   // nebude fungovat pokud se proměnná pos nevyužije

                if (pozice > -1) {
                    video_duration_file = rx.cap(1); // xx:xx:xx time

                } else{
                    QMessageBox::warning(this, "Nastala chyba", "FFmpeg.exe nebyl schopen najít délku videa!\n\nUjistěte se, že se jedná o zvukový/video soubor, nebo zda nebyl poškozen!\n\nNebo zkuste odstranit FFmpeg.exe v nastavení.");
                    MainWindow::disable_widgets(false);

                    return;
                }

            }else{
                // not exists
                QMessageBox::warning(this, "Nastala chyba", "ffmpeg_output_temp.txt nebyl nalezen!");
                MainWindow::disable_widgets(false);

                return;
            }

            // delete temp output file
            command = L"/C del \"ffmpeg_output_temp.txt\"";
            ShellExecute(0, L"open", L"cmd.exe", command.c_str(), (QDir::currentPath()+ "/tools").toStdWString().c_str(), SW_HIDE);


            // open editvideo window
            EditVideoWindow edit_window;
            edit_window.set_info(video_name + koncovka, video_duration_file, dir_path);
            this->hide();
            edit_window.show();
            QMessageBox::information(this, "Oznámení", "Původní soubory budou po konverzi nenávratně přepsány! (lze dočasně vypnout v možnostech)");

            // wait until edit_window is closed
            while (!edit_window.isHidden())
            {
                qApp->processEvents();
            }

            MainWindow::disable_widgets(false);
            MainWindow::center_window();
            this->show();
        }
    }
}

