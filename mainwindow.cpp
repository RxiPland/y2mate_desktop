#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
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

using namespace std;

QString response = "", response_najit_formaty = "";     // různé proměnné pro různé http requesty
string nalezene_formaty_mp3[6] = {"nic", "nic", "nic", "nic", "nic", "nic"}; // zde se přepíše "nic" nalezenými formáty (128kbps, 192kbps, ...)
string nalezene_formaty_mp4[6] = {"nic", "nic", "nic", "nic", "nic", "nic"};
QString nazev_souboru = "";  // název videa

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    if (QSslSocket::supportsSsl() == false){

        ShellExecute(0, 0, L"https://www.filehorse.com/download-openssl-64", 0, 0, SW_HIDE);
        QMessageBox::critical(this, "Problém | y2mate desktop - by RxiPland", "Verze OpenSSL není platná<br><br>Nainstalování verze \"" + QSslSocket::sslLibraryBuildVersionString() + "\" problém opraví<br>Odkaz na stažení: <a href=\"https://www.filehorse.com/download-openssl-64\">https://www.filehorse.com/download-openssl-64</a><br><br>Před stažením je důležité označit správnou verzi!<br>Vaše aktuální nainstalovaná verze: \"" + QSslSocket::sslLibraryVersionString() + "\"");

        QMetaObject::invokeMethod(qApp, "quit", Qt::QueuedConnection);
    }

    ui->setupUi(this);
    setWindowTitle("y2mate desktop - by RxiPland");

    ui->comboBox->setHidden(true);
    ui->comboBox_2->setHidden(true);
    ui->pushButton_2->setHidden(true);
    ui->label->setHidden(true);
    ui->label_2->setHidden(true);

    ui->label_3->setHidden(true);

    ui->progressBar->setHidden(true);
    ui->progressBar->setValue(0);

    ui->horizontalSpacer->changeSize(250, 35);
    ui->verticalSpacer_2->changeSize(20, 45);

    ui->statusBar->addPermanentWidget(ui->label_3, 1);
    ui->statusBar->addPermanentWidget(ui->progressBar, 2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::get_headers(QString location)
{
    // cancel download & read headers
    // najde název souboru z headru a zapíše ho do globální proměnné

    ui->progressBar->setHidden(false);

    QNetworkRequest request = QNetworkRequest(QUrl(location));
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.102 Safari/537.36");

    QNetworkReply *reply = manager.get(request);

    ui->label_3->setHidden(false);
    ui->label_3->setText("Získávám název videa");

    connect(reply, &QNetworkReply::downloadProgress,this, &MainWindow::downloadProgress);

    while (!reply->isFinished())
    {
        qApp->processEvents();
    }

    QList<QByteArray> headerlist = reply->rawHeaderList();
    QByteArray header;

    nazev_souboru = "error";


    for (auto it = headerlist.cbegin(); it != headerlist.cend(); ++it)
    {
        header = reply->rawHeader(*it);

        QString headers_qstring = QTextCodec::codecForMib(106)->toUnicode(header);

        if(headers_qstring.contains("filename")){

            QRegExp rx("filename=\\\"(.+)\\\";");
            int pos = rx.indexIn(headers_qstring);
            int pozice = pos;   // nebude fungovat pokud se proměnná pos nevyužije

            if (pozice > -1) {
                nazev_souboru = rx.cap(1); // "y2mate.com%20-%20LAmour%20Toujours%20Hardstyle.mp3"
                nazev_souboru = QUrl::fromPercentEncoding(nazev_souboru.toUtf8());

                nazev_souboru.replace("y2mate.com - ", "");
                nazev_souboru.replace("  ", " ");


                QString formaty_mp4[] = {"1080p", "720p", "480p", "360p", "240p", "144p"};
                QString formaty_mp3[] = {"320kbps", "256kbps", "192kbps", "128kbps", "96kbps", "64kbps"};

                for (int i=0; i<6; i++){
                    nazev_souboru.replace("_" + formaty_mp4[i], "");
                    nazev_souboru.replace("_" + formaty_mp3[i], "");
                }
                break;
            } else{
                nazev_souboru = "[Nepodařilo se najít]";
            }
        }
    }
    reply->deleteLater();
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

    QFileInfo fi;
    if (file) {
        fi.setFile(file->fileName());
        file->close();
        file->deleteLater();
        file.reset();

        QMessageBox::information(this, "V pořádku", "Soubor byl úspěšně stažen.");
        nazev_souboru = "";

        disable_widgets(false);
        on_pushButton_2_clicked();
    }

    QNetworkReply::NetworkError error = reply->error();
    const QString &errorString = reply->errorString();

    reply->deleteLater();
    reply.reset();
    if (error != QNetworkReply::NoError) {
        QFile::remove(fi.absoluteFilePath());
        return;
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
    disable_widgets(true);

    QString cesta = QFileDialog::getSaveFileName(this, "Uložit soubor", "/" + nazev_souboru, koncovka);

    if (cesta != ""){

        ui->progressBar->setHidden(false);

        ui->label_3->setHidden(false);
        ui->label_3->setText("Stahuji soubor");

        file = openFileForWrite(cesta);
        if (!file){
            QMessageBox::critical(this, "Problém", "Nastal problém při otevírání souboru.\n\n" + cesta);
        }

        QNetworkRequest request = QNetworkRequest(QUrl(url));
        request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.102 Safari/537.36");

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

    QNetworkRequest request = QNetworkRequest(QUrl(location));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded; charset=UTF-8");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.102 Safari/537.36");

    QNetworkReply *reply = manager.post(request, data);

    ui->progressBar->setHidden(false);
    ui->label_3->setHidden(false);

    if (druh_promenne == 1){
        ui->label_3->setText("Hledám dostupné formáty");

    } else if (druh_promenne == 2){
        ui->label_3->setText("Získávám odkaz na stažení souboru");
    }

    connect(reply, &QNetworkReply::downloadProgress,this, &MainWindow::downloadProgress);

    while (!reply->isFinished())
    {
        qApp->processEvents();
    }

    QString response_data = reply->readAll();
    reply->deleteLater();

    if (druh_promenne == 1){
        response_najit_formaty = response_data;

    } else if (druh_promenne == 2){

        response = response_data;
    }

}

QList<QString> najit_data(){

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
        video_id = rx2.cap(1); // "2psj1O9Fsb4"
    }
    udaje.append(video_id);

    return udaje; // [_id, video_id]
}

void MainWindow::get_nazev(){

    QList<QString> udaje;
    udaje = najit_data();

    QString _id = udaje[0];
    QString k_data_vid = udaje[1];

    if ((_id != "error") && (k_data_vid != "error")){

        QByteArray data;

        data.append("type=youtube");
        data.append("&");
        data.append("_id=");
        data.append(_id.toLocal8Bit());
        data.append("&");
        data.append("v_id=");
        data.append(k_data_vid.toLocal8Bit());
        data.append("&");
        data.append("ajax=1");
        data.append("&");
        data.append("token=");
        data.append("&");
        data.append("ftype=mp3");
        data.append("&");
        data.append("fquality=128");

        MainWindow::post("https://www.y2mate.com/mates/mp3Convert", data, 2);     // post request na získání odkazu ke stažení

        QRegExp rx("href=\\\\\\\"(.+)\\\\\\\" rel=");
        int pos = rx.indexIn(response);
        int pozice = pos;   // nebude fungovat pokud se proměnná pos nevyužije

        QString odkaz_na_stazeni = "error";

        if (pozice > -1) {
            odkaz_na_stazeni = rx.cap(1); // download link (https://)
        }

        if (odkaz_na_stazeni != "error"){

            odkaz_na_stazeni.replace("\\", "");
            get_headers(odkaz_na_stazeni);

        }

    } else {
        nazev_souboru = "[Nepodařilo se najít]";
    }
}

void MainWindow::on_pushButton_clicked(){

    QString text_tlacitka = ui->pushButton->text();
    QString line_edit_text = ui->lineEdit->text();

    string video_url = line_edit_text.toLocal8Bit().constData();

    ui->pushButton->setDisabled(true);

    if (text_tlacitka == "Najít"){

        string prvky[] = {"http", "://", "youtu"};
        bool chyba_url = false;

        // kontrola správnosti url
        for (int i=0; i<3; i++){

            if (video_url.find(prvky[i]) == string::npos) {

                QMessageBox::critical(this, "Problém", "Zadejte kompletní URL adresu\n\nPříklady:\n1. https://www.youtube.com/watch?v=DMtFhACPnTY\n2. https://youtu.be/DMtFhACPnTY");

                chyba_url = true;
                break;
            }
        }

        if (chyba_url == false){

            // post request na získání informací o url

            QByteArray data;

            data.append("url=");
            data.append(line_edit_text.toLocal8Bit());
            data.append("&");
            data.append("q_auto=1");
            data.append("&");
            data.append("ajax=1");

            MainWindow::post("https://www.y2mate.com/mates/mp3/ajax", data, 1);     // post request na získání informací o videu

            string response_str = response_najit_formaty.toLocal8Bit().constData();

            if (response_najit_formaty == "error"){
                QMessageBox::critical(this, "Chyba", "Problém v post requestu!");

            }
            else if (response_str.find("Video not found") != string::npos) {

                QMessageBox::critical(this, "Chyba", "Video pod tímto odkazem neexistuje!");

            }
            else if (response_najit_formaty != ""){

                ui->lineEdit->setReadOnly(true);        // read only na line edit s URL videa
                ui->label->setHidden(false);
                ui->label_2->setHidden(false);

                QRegExp rx("Duration: (..:..:..)");
                int pos = rx.indexIn(response_najit_formaty);
                int pozice = pos;   // nebude fungovat pokud se proměnná pos nevyužije

                if (pozice > -1) {
                    QString video_duration = rx.cap(1); // xx:xx:xx čas

                    ui->label->setText("Délka videa: " + video_duration);
                }

                get_nazev();
                nazev_souboru.replace(".mp3", "");
                nazev_souboru.replace(".mp4", "");
                ui->label_2->setText("Název videa: " + nazev_souboru);    // název videa do labelu

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

                string formaty_mp3[] = {"320 kbps", "256 kbps", "192 kbps", "128 kbps", "96 kbps", "64 kbps"};

                for (int i=0; i<6; i++){

                    if (response_str.find(formaty_mp3[i]) != string::npos) {
                        if (formaty_mp3[i] == "128 kbps"){
                            nalezene_formaty_mp3[i] = formaty_mp3[i] + " (Standart)";
                        } else {
                            nalezene_formaty_mp3[i] = formaty_mp3[i];
                        }
                    }
                }

                string formaty_mp4[] = {"1080p", "720p", "480p", "360p", "240p", "144p"};

                for (int i=0; i<6; i++){

                    if (response_str.find(formaty_mp4[i]) != string::npos) {
                        nalezene_formaty_mp4[i] = formaty_mp4[i];
                    }
                }

            } else{

                QMessageBox::critical(this, "Chyba", "Nastala neznámá chyba\n\n1) Zkontrolutje připojení k síti");

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

            if (text_format == "mp3 (zvuk)"){

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
                    data.append(_id.toLocal8Bit());
                    data.append("&");
                    data.append("v_id=");
                    data.append(k_data_vid.toLocal8Bit());
                    data.append("&");
                    data.append("ajax=1");
                    data.append("&");
                    data.append("token=");
                    data.append("&");
                    data.append("ftype=mp3");
                    data.append("&");
                    data.append("fquality=");

                    QStringList splitted_kvalita = text_kvalita.split(" ");

                    data.append(splitted_kvalita[0].toLocal8Bit());


                    MainWindow::post("https://www.y2mate.com/mates/mp3Convert", data, 2);     // post request na získání odkazu ke stažení

                    string response_str = response.toLocal8Bit().constData();


                    if (response == "error"){
                        QMessageBox::critical(this, "Chyba", "Problém v post requestu!");

                    }
                    else if (response_str.find("Download") == string::npos) {

                        QMessageBox::critical(this, "Chyba", "Nepovedlo se stáhnout mp3");

                    }
                    else if (response != ""){

                        QString odkaz_na_stazeni = "error";


                        QRegExp rx("href=\\\\\\\"(.+)\\\\\\\" rel=");
                        int pos = rx.indexIn(response);
                        int pozice = pos;   // nebude fungovat pokud se proměnná pos nevyužije

                        if (pozice > -1) {
                            odkaz_na_stazeni = rx.cap(1); // download link (https://)
                        }

                        if (odkaz_na_stazeni != "error"){

                            odkaz_na_stazeni.replace("\\", "");

                            //ShellExecuteA(0, 0, stazeni_url.c_str(), 0, 0, SW_HIDE);

                            MainWindow::get(odkaz_na_stazeni, "Zvukový soubor (*.mp3)");

                            return;

                        }else{
                            QMessageBox::warning(this, "Problém", "Zvukový soubor se nepodařilo začít stahovat!");
                        }

                    }
                }else if(_id == "error"){

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "Problém!\n_id se nepodařilo získat\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            ShellExecute(0, 0, L"https://www.y2mate.com", 0, 0, SW_HIDE);
                        }


                }else if(k_data_vid == "error"){

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "Problém!\nk_data_vid se nepodařilo získat\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            ShellExecute(0, 0, L"https://www.y2mate.com", 0, 0, SW_HIDE);
                    }
                }

                else{

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "Nastala neznámá chyba (stahování zvuku)\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            ShellExecute(0, 0, L"https://www.y2mate.com", 0, 0, SW_HIDE);
                    }
                }


            } else if (text_format == "mp4 (zvuk+video)"){

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
                    data.append(_id.toLocal8Bit());
                    data.append("&");
                    data.append("v_id=");
                    data.append(k_data_vid.toLocal8Bit());
                    data.append("&");
                    data.append("ajax=1");
                    data.append("&");
                    data.append("token=");
                    data.append("&");
                    data.append("ftype=mp4");
                    data.append("&");
                    data.append("fquality=");

                    QStringList splitted_kvalita = text_kvalita.split("p");

                    data.append(splitted_kvalita[0].toLocal8Bit());

                    MainWindow::post("https://www.y2mate.com/mates/convert", data, 2);     // post request na získání odkazu ke stažení


                    string response_str = response.toLocal8Bit().constData();


                    if (response == "error"){
                        QMessageBox::critical(this, "Chyba", "Problém v post requestu!");

                    }
                    else if (response_str.find("Refresh to try again") != string::npos) {

                        QMessageBox::critical(this, "Chyba", "Nepovedlo se stáhnout mp4, zkuste to zachvíli.");

                    }
                    else if (response_str.find("Download") == string::npos) {

                        QMessageBox::critical(this, "Chyba", "Nepovedlo se stáhnout mp4");

                    }
                    else if (response != ""){

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
                            QMessageBox::warning(this, "Problém", "Video se nepodařilo začít stahovat!");
                        }

                    }
                }else if(_id == "error"){

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "Problém!\n_id se nepodařilo získat\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            ShellExecute(0, 0, L"https://www.y2mate.com", 0, 0, SW_HIDE);
                        }


                }else if(k_data_vid == "error"){

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "Problém!\nk_data_vid se nepodařilo získat\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            ShellExecute(0, 0, L"https://www.y2mate.com", 0, 0, SW_HIDE);
                    }
                }

                else{

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "Nastala neznámá chyba (stahování videa)\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            ShellExecute(0, 0, L"https://www.y2mate.com", 0, 0, SW_HIDE);
                    }
                }

            }

        }

    }

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

    ui->comboBox->setHidden(true);
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setHidden(true);
    ui->comboBox_2->setCurrentIndex(0);

    ui->horizontalSpacer->changeSize(250, 35);
    ui->verticalSpacer_2->changeSize(20, 45);

    response = "";
    nazev_souboru = "";

    reply->deleteLater();

}

void MainWindow::disable_widgets(bool vypnout){

    // zakáže/povolí widgety

    ui->pushButton->setDisabled(vypnout);
    ui->pushButton_2->setDisabled(vypnout);

    ui->comboBox->setDisabled(vypnout);
    ui->comboBox_2->setDisabled(vypnout);

}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    // při vybrání mp3 načte příslušné formáty (128kbps, 192kbps, ...)
    // to stejné u mp4 (720p, ...)

    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("<Vyberte kvalitu>");

    if (arg1 == "mp3 (zvuk)"){
        // načíst z proměnné nalezene_formaty_mp3

        QString aktualni_format = "";

        for (int i=0; i<6; i++){

            aktualni_format = QString::fromStdString(nalezene_formaty_mp3[i]);

            if (aktualni_format != "nic"){

                ui->comboBox_2->addItem(aktualni_format);
            }
        }

        ui->comboBox_2->setHidden(false);
    }
    else if (arg1 == "mp4 (zvuk+video)"){
        // načíst z proměnné nalezene_formaty_mp4


        QString aktualni_format = "";

        for (int i=0; i<6; i++){

            aktualni_format = QString::fromStdString(nalezene_formaty_mp4[i]);

            if (aktualni_format != "nic"){

                ui->comboBox_2->addItem(aktualni_format);
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

    if(max == ist){
        ui->label_3->setHidden(true);
        ui->progressBar->setHidden(true);
        ui->progressBar->setValue(0);
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

    ShellExecute(0, 0, L"https://github.com/RxiPland/y2mate_desktop", 0, 0, SW_HIDE);

}

