#include "settings_dialog.h"
#include "ui_settings_dialog.h"
#include "mainwindow.h"
#include <QFile>
#include <QTextCodec>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <windows.h>

QString app_version_settings = "v1.7.1";  // aktuální verze programu
bool posledni_ulozene_nastaveni[4] = {};  // {REPLACE_VIDEO_NAME, UNDERSCORE_REPLACE, AUTO_CHECK_UPDATE, SAVE_HISTORY}

settings_dialog::settings_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings_dialog)
{
    ui->setupUi(this);
    setWindowTitle("Nastavení");

    ui->label->setText("Aktuální verze: " + app_version_settings);

    settings_dialog::load_settings();
    settings_dialog::settings_changed(false);  // vyresetuje výstražný label o neuložených změnách
}

settings_dialog::~settings_dialog()
{
    delete ui;
}

void settings_dialog::check_version(bool show_response=false){
    // zkontrolovat verzi, jestli nebyla vydána nová

    QUrl api_url = QUrl("https://api.github.com/repos/RxiPland/y2mate_desktop/releases/latest");

    QNetworkRequest request = QNetworkRequest(api_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.5112.102 Safari/537.36");

    QNetworkReply *reply = manager.get(request);

    while (!reply->isFinished())
    {
        qApp->processEvents();
    }

    // zpracování response
    QString strReply = (QString)reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    QString newest_version = jsonObject["tag_name"].toString();
    QStringList current_version = (ui->label->text()).split(" ");

    if (newest_version != current_version.back() && newest_version != ""){

        QMessageBox msgBox;
        msgBox.setWindowTitle("Nalezena nová aktualizace");
        msgBox.setText("Je dostupná novější verze y2mate desktop: " + newest_version + "\nVaše verze: "+ current_version.back()  +"\n\nPozn. Při instalaci nové verze se předchozí automaticky odstraní.");
        QAbstractButton* pButtonYes = msgBox.addButton("Otevřít odkaz", QMessageBox::YesRole);
        msgBox.addButton("Zrušit", QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton()==pButtonYes) {
            ShellExecute(0, 0, L"https://github.com/RxiPland/y2mate_desktop", 0, 0, SW_HIDE);
        }
    } else if (newest_version == ""){
        if (show_response){
            QMessageBox::information(this, "Kontrola aktualizace", "Nelze se připojit k internetu\nVaše verze: " + current_version.back());
        }
    } else{
        if (show_response){
            QMessageBox::information(this, "Kontrola aktualizace", "Již máte nejnovější verzi ("+ newest_version + ")");
        }
    }

    reply->deleteLater();
}

void settings_dialog::load_settings(){
    // načte nastavení ze souboru do checkboxů

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


        ui->checkBox->setChecked(hledat_nazev_videa.contains("1"));   // zapnutí nahradí název souboru hashem
        ui->checkBox_2->setChecked(nahradit_podtrzitkem.contains("1"));  // zapnutí nahrazuje mezery podtržítkama v názvu souboru při ukládání
        ui->checkBox_3->setChecked(check_update.contains("1"));   // zapnutí bude automaticky kontrolovat novou verzi při startu aplikace
        ui->checkBox_4->setChecked(zaznamenavat_historii.contains("1"));  // zapnutí bude zaznamenávat historii

    } else{
        ui->checkBox->setChecked(false); // defaultní hodnota false
        ui->checkBox_2->setChecked(false); // defaultní hodnota false
        ui->checkBox_3->setChecked(true); // defaultní hodnota true
        ui->checkBox_4->setChecked(true); // defaultní hodnota true
    }

    posledni_ulozene_nastaveni[0] = ui->checkBox->isChecked();
    posledni_ulozene_nastaveni[1] = ui->checkBox_2->isChecked();
    posledni_ulozene_nastaveni[2] = ui->checkBox_3->isChecked();
    posledni_ulozene_nastaveni[3] = ui->checkBox_4->isChecked();
}


void settings_dialog::settings_changed(bool warning){
    // píše zda jsou neuložené změny

    bool aktualni_nastaveni[4] = {};

    aktualni_nastaveni[0] = ui->checkBox->isChecked();
    aktualni_nastaveni[1] = ui->checkBox_2->isChecked();
    aktualni_nastaveni[2] = ui->checkBox_3->isChecked();
    aktualni_nastaveni[3] = ui->checkBox_4->isChecked();

    bool hodnoty_jsou_stejne = true;
    for (int i=0; i<4; i++){
        if (aktualni_nastaveni[i] != posledni_ulozene_nastaveni[i]){
            hodnoty_jsou_stejne = false;
            break;
        }
    }

    if (warning && !hodnoty_jsou_stejne){
        ui->label_2->setText("Nastavení není uloženo");
        ui->label_2->setStyleSheet("QLabel { color : red; }");
    } else{
        ui->label_2->clear();
        ui->label_2->setStyleSheet("QLabel { color : black; }");
    }
}



// on_push funkce

void settings_dialog::on_pushButton_4_clicked(){
    // uloží nastavení do souboru

    bool aktualni_nastaveni[4] = {};

    aktualni_nastaveni[0] = ui->checkBox->isChecked();
    aktualni_nastaveni[1] = ui->checkBox_2->isChecked();
    aktualni_nastaveni[2] = ui->checkBox_3->isChecked();
    aktualni_nastaveni[3] = ui->checkBox_4->isChecked();

    QFile file("nastaveni.txt");

    if(file.exists()){

        file.open(QIODevice::ReadOnly);

        QByteArray obsah = file.readAll();
        file.close();

        QString obsah_nastaveni = QTextCodec::codecForMib(106)->toUnicode(obsah);
        QStringList rows_nastaveni = obsah_nastaveni.split("\r\n");

        auto items_count = rows_nastaveni.size();

        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);

        // zapsání hodnot do nastaveni.txt
        for(int i=0; i < items_count; i++){
            if (i==0){  // REPLACE_VIDEO_NAME se nachází na prvním řádku
                if (aktualni_nastaveni[0]){
                    out << "REPLACE_VIDEO_NAME 1" << "\n";
                } else {
                    out << "REPLACE_VIDEO_NAME 0" << "\n";
                }
            } else if(i==1){ // UNDERSCORE_REPLACE se nachází na druhém řádku
                if (aktualni_nastaveni[1]){
                    out << "UNDERSCORE_REPLACE 1" << "\n";
                } else {
                    out << "UNDERSCORE_REPLACE 0" << "\n";
                }

            } else if(i==2){ // AUTO_CHECK_UPDATE se nachází na třetím řádku
                if (aktualni_nastaveni[2]){
                    out << "AUTO_CHECK_UPDATE 1" << "\n";
                } else {
                    out << "AUTO_CHECK_UPDATE 0" << "\n";
                }

            } else if(i==3){ // SAVE_HISTORY se nachází na čtvrtém řádku
                if (aktualni_nastaveni[3]){
                    out << "SAVE_HISTORY 1" << "\n";
                } else {
                    out << "SAVE_HISTORY 0" << "\n";
                }

            } else{

                if (i<items_count-1){
                    out << rows_nastaveni[i] << "\n";
                } else{
                    out << rows_nastaveni[i];
                }
            }
        }

    } else{
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);

        if (aktualni_nastaveni[0]){
            out << "REPLACE_VIDEO_NAME 1" << "\n";
        } else {
            out << "REPLACE_VIDEO_NAME 0" << "\n";
        }

        if (aktualni_nastaveni[1]){
            out << "UNDERSCORE_REPLACE 1" << "\n";
        } else {
            out << "UNDERSCORE_REPLACE 0" << "\n";
        }

        if (aktualni_nastaveni[2]){
            out << "AUTO_CHECK_UPDATE 1" << "\n";
        } else {
            out << "AUTO_CHECK_UPDATE 0" << "\n";
        }

        if (aktualni_nastaveni[3]){
            out << "SAVE_HISTORY 1" << "\n";
        } else {
            out << "SAVE_HISTORY 0" << "\n";
        }
    }

    file.close();
    settings_dialog::settings_changed(false);

    QMessageBox::information(this, "Oznámení", "Nastavení bylo úspěšně uloženo");
    close();
}


void settings_dialog::on_pushButton_5_clicked()
{
    // tlačítko defaultní nastavení

    ui->checkBox->setChecked(false); // defaultní hodnota false
    ui->checkBox_2->setChecked(false); // defaultní hodnota false
    ui->checkBox_3->setChecked(true); // defaultní hodnota true
    ui->checkBox_4->setChecked(true); // defaultní hodnota true

    QMessageBox::information(this, "Oznámení", "Bylo nastaveno defaultní nastavení, nezapomeňte uložit změny");

}

void settings_dialog::on_pushButton_6_clicked()
{
    // tlačítko manuální kontroly nové verze
    check_version(true);
}


void settings_dialog::on_checkBox_stateChanged(int arg1)
{
    settings_dialog::settings_changed(true);
}

void settings_dialog::on_checkBox_2_stateChanged(int arg1)
{
    settings_dialog::settings_changed(true);
}

void settings_dialog::on_checkBox_3_stateChanged(int arg1)
{
    settings_dialog::settings_changed(true);
}

void settings_dialog::on_checkBox_4_stateChanged(int arg1)
{
    settings_dialog::settings_changed(true);
}


void settings_dialog::on_pushButton_7_clicked()
{
    // tlačítko zrušit
    close();
}


// nápovědy:
void settings_dialog::on_pushButton_clicked()
{
    // nahrazení názvu videa hashem
    QMessageBox::information(this, "Nápověda", "Pokud bude povoleno, název videa bude nahrazen náhodnými znaky při ukládání souboru.\n\nNapř. 62ef90b9f99cc56a238b457a.mp4");
}


void settings_dialog::on_pushButton_2_clicked()
{
    // nahrazovat mezery podtržítkem
    QMessageBox::information(this, "Nápověda", "Pokud bude povoleno, tak se při ukládání souboru nahradí všechny mezery v názvu podtržítkem ( _ ).");

}

void settings_dialog::on_pushButton_3_clicked()
{
    // automatické zjišťování nové verze
    QMessageBox::information(this, "Nápověda", "Pokud bude povoleno, tak se při spuštění aplikace automaticky zkontroluje, zda nevyšla nová verze programu. Kontrolovat aktualizace jde i manuálně.");

}

void settings_dialog::on_pushButton_8_clicked()
{
    // ukládání historie
    QMessageBox::information(this, "Nápověda", "Pokud bude povoleno, bude se zaznamenávat historie 5ti naposled hledaných videí.");

}
