#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings_dialog.h"

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
#include <QJsonDocument>
#include <QJsonObject>

using namespace std;

QString response = "", response_najit_formaty = "";     // různé proměnné pro různé ukládání http responsů
string nalezene_formaty_mp3[6] = {"nic", "nic", "nic", "nic", "nic", "nic"}; // zde se přepíše "nic" nalezenými formáty (128kbps, 192kbps, ...)
string nalezene_formaty_mp4[6] = {"nic", "nic", "nic", "nic", "nic", "nic"};
QString nazev_souboru = "";  // název yt videa
QString cesta_k_souboru = "";  // úplná cesta k uloženému souboru

QString app_version = "v1.6.0";  // aktuální verze programu
bool hodnoty_nastaveni[3] = {};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    if (QSslSocket::supportsSsl() == false){

        QMessageBox msgBox;
        msgBox.setWindowTitle("Problém | y2mate desktop - by RxiPland");
        msgBox.setText("Verze OpenSSL není platná!<br>Bez ní program nemůže přistupovat na zabezpečené weby s protokolem HTTPs<br><br>Nainstalování verze \"" + QSslSocket::sslLibraryBuildVersionString() + "\" nebo velmi podobné problém opraví<br>Odkaz na stažení: <a href=\"https://www.filehorse.com/download-openssl-64\">https://www.filehorse.com/download-openssl-64</a><br><br>Před stažením je důležité označit správnou verzi!<br>Vaše aktuální nainstalovaná verze: \"" + QSslSocket::sslLibraryVersionString() + "\"");
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
    setWindowTitle("y2mate desktop");

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
    ui->verticalSpacer_2->changeSize(20, 45);

    ui->statusBar->addPermanentWidget(ui->label_3, 1);  // informace o requestu
    ui->statusBar->addPermanentWidget(ui->label_4, 1);  // staženo mb z celkového počtu
    ui->statusBar->addPermanentWidget(ui->progressBar, 2);  // progress bar stahování

    // načtení hodnoty automatické hledání názvu videí
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

        // defaultní hodnoty, pokud budou řádky prázdné (např. při přechodu ze starší verze na novou)
        if (hledat_nazev_videa == ""){
            hledat_nazev_videa = "1";
        }

        if (nahradit_podtrzitkem == ""){
            nahradit_podtrzitkem = "0";
        }

        if (check_update == ""){
            check_update = "1";
        }

        hodnoty_nastaveni[0] = hledat_nazev_videa.contains("1");  // zapnutí zvyšuje dobu procesu stahování videa (název souboru pak nemusí být automaticky hash)
        hodnoty_nastaveni[1] = nahradit_podtrzitkem.contains("1");   // zapnutí nahrazuje mezery podtržítkama v názvu souboru při ukládání
        hodnoty_nastaveni[2] = check_update.contains("1");   // zapnutí bude automaticky kontrolovat novou verzi při startu

    } else{

        hodnoty_nastaveni[0] = true; // defaultní hodnota true
        hodnoty_nastaveni[1] = false;  // defaultní hodnota false
        hodnoty_nastaveni[2] = true; // defaultní hodnota true
    }

    // automatická kontrola verze
    if (hodnoty_nastaveni[2]){
        check_version();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check_version(){
    // zkontrolovat verzi, jestli nebyla vydána nová

    QUrl api_url = QUrl("https://api.github.com/repos/RxiPland/y2mate_desktop/releases/latest");

    QNetworkRequest request = QNetworkRequest(api_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.102 Safari/537.36");

    QNetworkReply *reply = manager.get(request);

    ui->label_3->setHidden(false);
    ui->label_4->setHidden(true);
    ui->label_3->setText("Kontroluji verzi");

    connect(reply, &QNetworkReply::downloadProgress,this, &MainWindow::downloadProgress);

    while (!reply->isFinished())
    {
        qApp->processEvents();
    }

    // zpracování response
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    QString newest_version = jsonObject["tag_name"].toString();

    if (newest_version != app_version && newest_version != ""){

        QMessageBox msgBox;
        msgBox.setWindowTitle("Aktualizace");
        msgBox.setText("Je dostupná novější verze y2mate desktop: " + newest_version + "\nVaše verze: "+ app_version  +"\n\nNezapomeňte starou verzi manuálně odinstalovat před instalací nové");
        QAbstractButton* pButtonYes = msgBox.addButton("Otevřít odkaz", QMessageBox::YesRole);
        msgBox.addButton("Zrušit", QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton()==pButtonYes) {
            ShellExecute(0, 0, L"https://github.com/RxiPland/y2mate_desktop", 0, 0, SW_HIDE);
        }
    }

    reply->deleteLater();
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

                nazev_souboru.replace("y2mate.com - ", "");      // odebrání watermarku z názvu souboru
                nazev_souboru.replace("  ", " ");


                QString formaty_mp4[] = {"1080p", "720p", "480p", "360p", "240p", "144p"};
                QString formaty_mp3[] = {"320kbps", "256kbps", "192kbps", "128kbps", "96kbps", "64kbps"};

                for (int i=0; i<6; i++){
                    nazev_souboru.replace("_" + formaty_mp4[i], "");    // odebrání kvality z názvu souboru
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
    // http request byl dokončen

    QFileInfo fi;
    if (file) {
        fi.setFile(file->fileName());
        file->close();
        file->deleteLater();
        file.reset();

        QMessageBox msgBox;
        msgBox.setWindowTitle("V pořádku");
        msgBox.setText("Soubor byl úspěšně stažen.");
        QAbstractButton* pButtonYes = msgBox.addButton("Otevřít soubor", QMessageBox::YesRole);
        msgBox.addButton("Ok", QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton()==pButtonYes) {
            // otevřít soubor

            cesta_k_souboru = "\"" + cesta_k_souboru + "\"";
            std::wstring command = cesta_k_souboru.toStdWString();

            ShellExecute(0, L"open", command.c_str(), 0, 0, SW_RESTORE);
        }

        nazev_souboru = "";
        cesta_k_souboru = "";

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
    // GET

    disable_widgets(true);

    QString upraveny_nazev_souboru = "";
    bool nahradit_podtrzitkem = hodnoty_nastaveni[1];

    if (nahradit_podtrzitkem){

        upraveny_nazev_souboru = nazev_souboru;
        upraveny_nazev_souboru.replace(" ", "_");
    } else{
        upraveny_nazev_souboru = nazev_souboru;
    }

    cesta_k_souboru = QFileDialog::getSaveFileName(this, "Uložit soubor", "/" + upraveny_nazev_souboru, koncovka);

    if (cesta_k_souboru != ""){

        ui->progressBar->setHidden(false);

        ui->label_3->setHidden(false);
        ui->label_4->setHidden(false);
        ui->label_3->setText("Stahuji soubor");

        file = openFileForWrite(cesta_k_souboru);
        if (!file){
            QMessageBox::critical(this, "Problém", "Nastal problém při otevírání souboru.\n\n" + cesta_k_souboru);
            return;
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
    // POST

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

    } else if (druh_promenne == 3){
        ui->label_3->setText("Získávám název videa");
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

    } else if (druh_promenne == 2 || druh_promenne == 3){

        response = response_data;
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

void MainWindow::get_nazev(){
    // získat název videa

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
        data.append("fquality=64");

        MainWindow::post("https://www.y2mate.com/mates/mp3Convert", data, 3);     // post request na získání odkazu ke stažení

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
    // pushButton je najít/stáhnout

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

        if (chyba_url != true){

            // post request na získání informací o url
            // dostupné kvality u mp4/mp3, délka videa

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
                QMessageBox::critical(this, "Chyba", "[kód 1] Problém v post requestu!");

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

                bool nazev_videa = hodnoty_nastaveni[0];

                if (nazev_videa){

                    // pokud bude chtít uživatel najít skutečný název videa (trvá déle)
                    get_nazev();

                    nazev_souboru.replace(".mp3", "");
                    nazev_souboru.replace(".mp4", "");
                    nazev_souboru.replace(".webm", "");
                    ui->label_2->setText("Název videa: " + nazev_souboru);    // název videa do labelu

                } else{
                    // uživatel nechce hledat název videa
                    // jako název souboru se dosadí _id hodnota z y2mate
                    ui->label_2->setHidden(true);

                    QList<QString> udaje;
                    udaje = najit_data();

                    nazev_souboru = udaje[0];    // např. "62fd01c3f1a87588248b45ba"
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

                QMessageBox::critical(this, "Chyba", "[kód 2] Nastala neznámá chyba\n\n1) Zkontrolutje připojení k síti");

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
                        QMessageBox::critical(this, "Chyba", "[kód 3] Problém v post requestu!");

                    }
                    else if (response_str.find("Download") == string::npos) {

                        QMessageBox::critical(this, "Chyba", "[kód 4] Nepovedlo se stáhnout mp3");

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

                            QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Problém", "[kód 5] Zvukový soubor se nepodařilo začít stahovat!\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                            if (reply_box == QMessageBox::Yes){
                                    QString odkaz = "https://www.y2mate.com/youtube-mp3/" + k_data_vid;
                                    ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
                                }
                        }

                    }
                }else if(_id == "error"){

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "[kód 6] Problém!\n_id se nepodařilo získat\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            QString odkaz = "https://www.y2mate.com/youtube-mp3/" + k_data_vid;
                            ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
                        }


                }else if(k_data_vid == "error"){

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "[kód 7] Problém!\nk_data_vid se nepodařilo získat\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            QString odkaz = "https://www.y2mate.com/youtube-mp3/" + k_data_vid;
                            ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
                        }
                }

                else{

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
                        QMessageBox::critical(this, "Chyba", "[kód 9] Problém v post requestu!");

                    }
                    else if (response_str.find("Refresh to try again") != string::npos) {

                        QMessageBox::critical(this, "Chyba", "[kód 10] Nepovedlo se stáhnout mp4, zkuste to zachvíli.");

                    }
                    else if (response_str.find("Download") == string::npos) {

                        QMessageBox::critical(this, "Chyba", "[kód 11] Nepovedlo se stáhnout mp4");

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
                            QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Problém", "[kód 12] Video se nepodařilo začít stahovat!\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                            if (reply_box == QMessageBox::Yes){
                                    QString odkaz = "https://www.y2mate.com/youtube-mp3/" + k_data_vid;
                                    ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
                            }
                        }
                    }
                }else if(_id == "error"){

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "[kód 12] Problém!\n_id se nepodařilo získat\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            QString odkaz = "https://www.y2mate.com/youtube-mp3/" + k_data_vid;
                            ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
                    }


                }else if(k_data_vid == "error"){

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "[kód 13] Problém!\nk_data_vid se nepodařilo získat\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            QString odkaz = "https://www.y2mate.com/youtube-mp3/" + k_data_vid;
                            ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
                    }
                }

                else{

                    QMessageBox::StandardButton reply_box = QMessageBox::critical(this, "Chyba", "[kód 14] Nastala neznámá chyba (stahování videa)\n\nChcete otevřít y2mate v prohlížeči?", QMessageBox::Yes | QMessageBox::No);

                    if (reply_box == QMessageBox::Yes){
                            QString odkaz = "https://www.y2mate.com/youtube-mp3/" + k_data_vid;
                            ShellExecute(0, 0, odkaz.toStdWString().c_str(), 0, 0, SW_HIDE);
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
    // při změně formátu v boxu se načtou příslušné typy kvalit (u mp3: 128kbps, 192kbps, ...)
    // to stejné u mp4 (720p, ...)

    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("<Vyberte kvalitu>");

    if (arg1 == "mp3 (pouze zvuk)"){
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
    else if (arg1 == "mp4 (video)"){
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

    ui->label_4->setText(QString::number(ist/1000000) + "." + QString::number(ist/100000).back() + " / " + QString::number(max/1000000) + "." + QString::number(max/100000).back() + " MB");

    if(max == ist){
        ui->label_3->setHidden(true);
        ui->label_4->setHidden(true);
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

    // otevřít github se zdrojovým kódem

    ShellExecute(0, 0, L"https://github.com/RxiPland/y2mate_desktop", 0, 0, SW_HIDE);

}

void MainWindow::on_actionNastaven_triggered()
{
    settings_dialog nastaveni_dialog;
    nastaveni_dialog.setModal(true);
    nastaveni_dialog.exec();
}

