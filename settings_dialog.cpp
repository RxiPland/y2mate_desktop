#include "settings_dialog.h"
#include "ui_settings_dialog.h"
#include "mainwindow.h"

#include <QFile>
#include <QTextCodec>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QFileDialog>
#include <windows.h>

QString last_location_path_settings = "/";
QString video_quality = "";
bool posledni_ulozene_nastaveni[5] = {};  // {REPLACE_VIDEO_NAME, UNDERSCORE_REPLACE, AUTO_CHECK_UPDATE, SAVE_HISTORY, LAST_LOCATION}
bool path_changed = false;  // pokud se nastaví nová cesta, bude true


QString app_version_settings = "";  // aktuální verze programu (doplní se pomocí funkce set_version(); )
QByteArray user_agent_settings = "";

settings_dialog::settings_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings_dialog)
{
    ui->setupUi(this);
    setWindowTitle("Nastavení");
    setWindowIcon(QIcon(":/images/settings.ico"));

    settings_dialog::load_settings();
    settings_dialog::settings_changed(false);  // vyresetuje výstražný label o neuložených změnách

    ui->pushButton_4->setDefault(true);

    QFile ffmpeg_path("tools/ffmpeg.exe");

    if(ffmpeg_path.exists()){
        ui->label_3->setText("FFmpeg je stažený.");
        ui->label_3->setStyleSheet("QLabel { color : green; }");
        ui->pushButton_11->setDisabled(false);

    } else{
        ui->label_3->setText("FFmpeg není stažený!");
        ui->label_3->setStyleSheet("QLabel { color : red; }");
        ui->pushButton_11->setDisabled(true);
    }
}

settings_dialog::~settings_dialog()
{
    delete ui;
}

void settings_dialog::set_version(QString version, QByteArray user_agent){

    ui->label->setText("Aktuální verze: " + version);
    app_version_settings = version;
    user_agent_settings = user_agent;
}

void settings_dialog::check_version(bool show_response=false){
    // zkontrolovat verzi, jestli nebyla vydána nová

    QUrl api_url = QUrl("https://api.github.com/repos/RxiPland/y2mate_desktop/releases/latest");

    QNetworkRequest request = QNetworkRequest(api_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    request.setRawHeader("User-Agent", user_agent_settings);

    QNetworkReply *reply_check = manager.get(request);

    while (!reply_check->isFinished())
    {
        qApp->processEvents();
    }

    // zpracování response
    QString strReply = (QString)reply_check->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    QString newest_version = jsonObject["tag_name"].toString();
    QStringList current_version = (ui->label->text()).split(" ");

    if (newest_version != current_version.back() && newest_version != ""){

        QMessageBox msgBox;
        msgBox.setWindowTitle("Nalezena nová aktualizace");
        msgBox.setText("Je dostupná novější verze y2mate desktop: " + newest_version + "\nVaše verze: "+ current_version.back()  +"\n\nPři instalaci nové verze se předchozí automaticky odstraní");
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

    reply_check->reset();
    reply_check->deleteLater();
}

void settings_dialog::load_settings(){
    // načte nastavení ze souboru do checkboxů

    QFile file_settings("nastaveni.txt");

    if (file_settings.exists()){
        file_settings.open(QIODevice::ReadOnly);

        QByteArray obsah = file_settings.readAll();
        file_settings.close();

        QString obsah_nastaveni = QTextCodec::codecForMib(106)->toUnicode(obsah);
        QStringList rows_nastaveni = obsah_nastaveni.split("\r\n");

        QString hledat_nazev_videa = rows_nastaveni[0];
        QString nahradit_podtrzitkem = rows_nastaveni[1];
        QString check_update = rows_nastaveni[2];
        QString zaznamenavat_historii = rows_nastaveni[3];
        QString last_location = rows_nastaveni[4];
        video_quality = rows_nastaveni[5].split(" /;/ ").back();

        if (rows_nastaveni[4].contains(" /;/ ")){
            QStringList last_location_row = rows_nastaveni[4].split(" /;/ ");
            last_location = last_location_row[0];

            last_location_path_settings = last_location_row[1];

            if (last_location_path_settings == "" || last_location_path_settings == " "){

                last_location_path_settings = "/";
            }

        } else{
            last_location_path_settings = "/";
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

        if(video_quality == ""){
            video_quality = "128 kbps";
        }

        ui->checkBox->setChecked(hledat_nazev_videa.contains("1"));   // zapnutí nahradí název souboru hashem
        ui->checkBox_2->setChecked(nahradit_podtrzitkem.contains("1"));  // zapnutí nahrazuje mezery podtržítkama v názvu souboru při ukládání
        ui->checkBox_3->setChecked(check_update.contains("1"));   // zapnutí bude automaticky kontrolovat novou verzi při startu aplikace
        ui->checkBox_4->setChecked(zaznamenavat_historii.contains("1"));  // zapnutí bude zaznamenávat historii
        ui->checkBox_5->setChecked(last_location.contains("1"));  // zapnutí bude otevírat ukládací dialog v této cestě
        ui->comboBox->setCurrentText(video_quality);

    } else{
        ui->checkBox->setChecked(false); // defaultní hodnota false
        ui->checkBox_2->setChecked(false); // defaultní hodnota false
        ui->checkBox_3->setChecked(true); // defaultní hodnota true
        ui->checkBox_4->setChecked(true); // defaultní hodnota true
        ui->checkBox_5->setChecked(true); // defaultní hodnota true
        ui->comboBox->setCurrentText("128 kbps");
    }

    posledni_ulozene_nastaveni[0] = ui->checkBox->isChecked();
    posledni_ulozene_nastaveni[1] = ui->checkBox_2->isChecked();
    posledni_ulozene_nastaveni[2] = ui->checkBox_3->isChecked();
    posledni_ulozene_nastaveni[3] = ui->checkBox_4->isChecked();
    posledni_ulozene_nastaveni[4] = ui->checkBox_5->isChecked();
}


void settings_dialog::settings_changed(bool warning){
    // píše zda jsou neuložené změny
    // bool warning (zda se má text zbarvit dočervena)

    QFile file_settings("nastaveni.txt");

    if (!file_settings.exists() && video_quality == ""){

        ui->label_2->setText("Soubor s nastavením neexistuje. Uložte nastavení pro vytvoření souboru.");
        ui->label_2->setStyleSheet("QLabel { color : red; }");
        return;
    }

    bool aktualni_nastaveni[5] = {};

    aktualni_nastaveni[0] = ui->checkBox->isChecked();
    aktualni_nastaveni[1] = ui->checkBox_2->isChecked();
    aktualni_nastaveni[2] = ui->checkBox_3->isChecked();
    aktualni_nastaveni[3] = ui->checkBox_4->isChecked();
    aktualni_nastaveni[4] = ui->checkBox_5->isChecked();

    bool hodnoty_jsou_stejne = true;
    for (int i=0; i < sizeof(aktualni_nastaveni); i++){
        if (aktualni_nastaveni[i] != posledni_ulozene_nastaveni[i]){
            hodnoty_jsou_stejne = false;
            break;
        }
    }

    bool quality_changed = false;

    if(video_quality != ui->comboBox->currentText()){
        quality_changed = true;
    }

    if ((warning && !hodnoty_jsou_stejne) || path_changed || quality_changed){
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

    bool aktualni_nastaveni[5] = {};

    aktualni_nastaveni[0] = ui->checkBox->isChecked();
    aktualni_nastaveni[1] = ui->checkBox_2->isChecked();
    aktualni_nastaveni[2] = ui->checkBox_3->isChecked();
    aktualni_nastaveni[3] = ui->checkBox_4->isChecked();
    aktualni_nastaveni[4] = ui->checkBox_5->isChecked();

    video_quality = ui->comboBox->currentText();

    QFile file_settings("nastaveni.txt");

    if(file_settings.exists()){

        file_settings.open(QIODevice::ReadOnly);

        QByteArray obsah = file_settings.readAll();
        file_settings.close();

        QString obsah_nastaveni = QTextCodec::codecForMib(106)->toUnicode(obsah);
        QStringList rows_nastaveni = obsah_nastaveni.split("\r\n");

        file_settings.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file_settings);

        int items_count = sizeof(aktualni_nastaveni)+1;  //+1 because of VIDEO_QUALITY, which is not in bool array

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

            } else if(i==4){ // LAST_LOCATION se nachází na pátém řádku
                if (aktualni_nastaveni[4]){
                    out << "LAST_LOCATION 1" << " /;/ " << last_location_path_settings << "\n";
                } else {
                    out << "LAST_LOCATION 0" << " /;/ " << last_location_path_settings << "\n";
                }

            } else if(i==5){ // LAST_LOCATION se nachází na šestém řádku
                if (video_quality != ""){
                    out << "VIDEO_QUALITY 1" << " /;/ " << video_quality << "\n";
                } else {
                    out << "VIDEO_QUALITY 1" << " /;/ " << "128 kbps" << "\n";
                }

            } else{

                if (rows_nastaveni[i] != "\n"){
                    out << rows_nastaveni[i] << "\n";
                }
            }
        }

    } else{
        file_settings.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file_settings);

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

        if (aktualni_nastaveni[4]){
            out << "LAST_LOCATION 1" << " /;/ " << last_location_path_settings << "\n";
        } else {
            out << "LAST_LOCATION 0" << " /;/ " << last_location_path_settings << "\n";
        }

        if (video_quality != ""){
            out << "VIDEO_QUALITY 1" << " /;/ " << video_quality << "\n";
        } else {
            out << "VIDEO_QUALITY 1" << " /;/ " << "128 kbps" << "\n";
        }
    }

    file_settings.close();
    settings_dialog::settings_changed(false);

    path_changed = false;
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
    ui->checkBox_5->setChecked(true); // defaultní hodnota true

    ui->comboBox->setCurrentText("128 kbps"); // defaultní kvalita je 128kbps

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

void settings_dialog::on_checkBox_5_stateChanged(int arg1)
{
    settings_dialog::settings_changed(true);

    if(ui->checkBox_5->isChecked()){
        ui->pushButton_10->setDisabled(true);

    } else{
        ui->pushButton_10->setDisabled(false);
    }
}


void settings_dialog::on_pushButton_7_clicked()
{
    // tlačítko zrušit
    this->close();
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

void settings_dialog::on_pushButton_9_clicked()
{
    // poslední lokace
    QMessageBox::information(this, "Nápověda", "Pokud bude povoleno, dialog s ukládáním souboru se otevře do naposledy stahované lokace. Pro fungování musí existovat soubor s nastavením (vytvoří se při uložení)\n\nPo zakázání lze nastavit vlastní (defaultní) lokaci.\n\nAktuální: " + last_location_path_settings);

}

void settings_dialog::on_pushButton_12_clicked()
{
    // FFmpeg
    QFileInfo ffmpeg("tools/ffmpeg.exe");
    QString ffmpeg_message="";

    if(ffmpeg.exists()){
        ffmpeg_message = "<br><br>Aktuální lokace: " + ffmpeg.absoluteFilePath();
    }

    QMessageBox::information(this, "Nápověda", "<a href=\"https://ffmpeg.org/\">FFmpeg</a> je nástroj pro manipulaci s video/zvukovými soubory.<br><br>Pokud nepracuje správně, můžete FFmpeg odstranit a při další úpravě videa může být stažen znovu. <br><br>Jak stáhnout FFmpeg? Jednoduše si stáhnout nějaké video a vybrat možnost 'upravit video'. Když program zjistí, že FFmpeg neexistuje, nabídne možnost stažení." + ffmpeg_message);
}

void settings_dialog::on_pushButton_10_clicked()
{
    // nastavení lokace

    QString location = QFileDialog::getExistingDirectory(this, "Vybrat cestu", last_location_path_settings);

    if(location != ""){

        last_location_path_settings = location + "/";

        QFile file_settings("nastaveni.txt");

        if (file_settings.exists()){
            file_settings.open(QIODevice::ReadOnly);

            QByteArray obsah = file_settings.readAll();
            file_settings.close();

            QString obsah_souboru = QTextCodec::codecForMib(106)->toUnicode(obsah);
            QStringList rows_settings = obsah_souboru.split("\r\n");

            int pocet_rows = rows_settings.count();

            for(int i=0; i < 5-pocet_rows; i++){
                rows_settings.append("");
            }

            file_settings.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file_settings);

            for(int i=0; i < pocet_rows; i++){
                if (i==4){
                    out << "LAST_LOCATION 0" << " /;/ "  << last_location_path_settings << "\n";

                } else{
                    if(rows_settings[i] != ""){
                        out << rows_settings[i] << "\n";
                    }
                }
            }
            file_settings.close();

            path_changed = true;
            settings_dialog::settings_changed(true);

            QMessageBox::information(this, "Nápověda", "Cesta byla nastavena, nezapomeňte uložit změny.");
        }
    }
}

void settings_dialog::on_pushButton_11_clicked()
{
    // delete ffmpeg

    QDir dir("tools");
    bool succes = dir.removeRecursively();

    if(succes){
        QMessageBox::information(this, "FFmpeg", "FFmpeg.exe byl úspěšně odstraněn. Lze ho stáhnout při příští úpravě videa.");
        ui->label_3->setText("FFmpeg není stažený!");
        ui->label_3->setStyleSheet("QLabel { color : red; }");
        ui->pushButton_11->setDisabled(true);

    } else{
        QMessageBox::information(this, "FFmpeg", "Chyba! Nepodařilo se vymazat FFmpeg.exe");
        ui->pushButton_11->setDisabled(false);
    }
}

void settings_dialog::on_pushButton_13_clicked()
{
    QMessageBox::information(this, "Nápověda", "Při zjišťování názvu videa je vyslán požadavek na y2mate.com s určitou kvalitou.\n\nVybráním nejčastěji stahované kvality lze proces stahování výrazně zrychlit, protože y2mate.com nemusí připravovat další soubor s jinou kvalitou, pokud se chystáte stáhnout totožnou kvalitu.");
}


void settings_dialog::on_comboBox_currentTextChanged(const QString &arg1)
{
    settings_dialog::settings_changed(true);
}

