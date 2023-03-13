#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <windows.h>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFileDialog>


settingsDialog::settingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsDialog)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);

    settingsDialog::loadSettings();

    this->show();
    ui->label->setHidden(true);
    ui->label->setStyleSheet("QLabel { color : red; }");
}

settingsDialog::~settingsDialog()
{
    delete ui;
}

void settingsDialog::closeEvent(QCloseEvent *bar)
{
    // Before application close

    if(settingsChanged){

        QMessageBox msgBox;
        msgBox.setWindowTitle("Upozornění");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Bylo zjištěno neuložené nastavení! Chcete uložit změny?");
        QAbstractButton* pButtonYes = msgBox.addButton(" Ano ", QMessageBox::YesRole);
        msgBox.addButton(" Ne ", QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton() == pButtonYes){

            settingsDialog::saveSettings();
            return;
        }
    }

    this->close();

    if(bar != nullptr){
        bar->accept();
    }
}

void settingsDialog::loadSettings()
{
    // load settings from file and set checkboxes

    QFile dataFile(QDir::currentPath() + "/Data/data.json");

    if (dataFile.exists()){
        dataFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QByteArray fileContent = dataFile.readAll();
        dataFile.close();

        if(fileContent.isEmpty()){
            // File is empty

            QMessageBox::critical(this, "Chyba", "Soubor s nastavením je prázdný! Program bude restartován pro opravu.");

            QProcess::startDetached(QApplication::applicationFilePath());

            QApplication::quit();
            return;

        } else{
            QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

            if(loadedJson.isEmpty()){
                // JSON is corrupted

                QMessageBox::critical(this, "Chyba", "JSON v souboru s nastavením je poškozený! Program bude restartován pro opravu.");

                QProcess::startDetached(QApplication::applicationFilePath());

                QApplication::quit();
                return;

            } else{
                // everything OK

                settingsDialog::appVersion = loadedJson["app_version"].toString();
                settingsDialog::userAgent = loadedJson["user_agent"].toString().toUtf8();

                settingsDialog::checkForUpdates = loadedJson["check_for_updates"].toBool();
                settingsDialog::allowHistory = loadedJson["allow_history"].toBool();
                settingsDialog::lastSavePath = loadedJson["last_path"].toString();
                settingsDialog::lastPathEnabled = loadedJson["enable_last_path"].toBool();
                settingsDialog::replaceNameWithHash = loadedJson["replace_name_with_hash"].toBool();
                settingsDialog::replaceNameWithUnderscores = loadedJson["replace_name_with_underscores"].toBool();

                ui->label_2->setText("Aktuální verze: " + settingsDialog::appVersion);

                ui->checkBox->setChecked(replaceNameWithHash);
                ui->checkBox_2->setChecked(replaceNameWithUnderscores);

                ui->checkBox_3->setChecked(!lastPathEnabled);
                ui->pushButton->setEnabled(!lastPathEnabled);

                ui->checkBox_4->setChecked(allowHistory);
                ui->checkBox_5->setChecked(checkForUpdates);
            }
        }

    } else{
        // file with settings not found

        QMessageBox::critical(this, "Chyba", "Soubor s nastavením neexistuje! Program bude restartován pro opravu.");

        QProcess::startDetached(QApplication::applicationFilePath());

        QApplication::quit();
        return;
    }
}

bool settingsDialog::saveSettings()
{
    // save settings to file

    QFile dataFile(QDir::currentPath() + "/Data/data.json");

    if (dataFile.exists()){
        dataFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QByteArray fileContent = dataFile.readAll();
        dataFile.close();

        if(fileContent.isEmpty()){
            // File is empty

            QMessageBox::critical(this, "Chyba", "Soubor s nastavením je prázdný! Při příštím zapnutí programu bude problém vyřešen.");
            return false;

        } else{
            QJsonObject loadedJson = QJsonDocument::fromJson(fileContent).object();

            if(loadedJson.isEmpty()){
                // JSON is corrupted

                QMessageBox::critical(this, "Chyba", "JSON v souboru s nastavením je poškozený! Při příštím zapnutí programu bude problém vyřešen.");
                return false;

            } else{
                // overwrite settings

                loadedJson["allow_history"] = settingsDialog::allowHistory;
                loadedJson["check_for_updates"] = settingsDialog::checkForUpdates;
                loadedJson["enable_last_path"] = settingsDialog::lastPathEnabled;
                loadedJson["last_path"] = settingsDialog::lastSavePath;
                loadedJson["replace_name_with_hash"] = settingsDialog::replaceNameWithHash;
                loadedJson["replace_name_with_underscores"] = settingsDialog::replaceNameWithUnderscores;

                QJsonDocument docData(loadedJson);

                dataFile.open(QIODevice::WriteOnly | QIODevice::Text);
                int status = dataFile.write(docData.toJson());
                dataFile.close();

                if (status == -1){
                    QMessageBox::critical(this, "Chyba", "Nastala neznámá chyba při zapisování do souboru s nastavením!\n\n" + dataFile.fileName());

                    return false;
                }
            }
        }

    } else{
        // file with settings not found

        QMessageBox::critical(this, "Chyba", "Soubor s nastavením neexistuje! Při příštím zapnutí programu bude problém vyřešen.");
        return false;
    }

    return true;
}

void settingsDialog::on_pushButton_clicked()
{
    // set default path for downloading files

    QString folderPath;
    folderPath = QFileDialog::getExistingDirectory(this, "Vybrat složku", lastSavePath);

    if(folderPath.isEmpty()){
        return;

    } else if (folderPath.contains(lastSavePath) || lastSavePath.contains(folderPath)){
        QMessageBox::information(this, "Oznámení", "Lokace nebyla změněna, protože se shoduje s předchozí");

    } else{
        settingsDialog::lastSavePath = folderPath;
        ui->label->setHidden(false);
        settingsDialog::settingsChanged = true;

        QMessageBox::information(this, "Oznámení", "Byla nastavena nová lokace");
    }
}

void settingsDialog::on_pushButton_2_clicked()
{
    // default settings

    settingsDialog::checkForUpdates = true;
    settingsDialog::allowHistory = true;
    settingsDialog::lastPathEnabled = true;
    settingsDialog::replaceNameWithHash = false;
    settingsDialog::replaceNameWithUnderscores = false;

    ui->checkBox->setChecked(replaceNameWithHash);
    ui->checkBox_2->setChecked(replaceNameWithUnderscores);

    ui->checkBox_3->setChecked(!lastPathEnabled);
    ui->pushButton->setEnabled(!lastPathEnabled);

    ui->checkBox_4->setChecked(allowHistory);
    ui->checkBox_5->setChecked(checkForUpdates);


    settingsDialog::settingsChanged = true;
    ui->label->setHidden(false);

    QMessageBox::information(this, "Oznámení", "Bylo nastaveno defaultní nastavení, nezapomeňte uložit změny");
}

void settingsDialog::on_pushButton_3_clicked()
{
    // cancel

    this->close();
}

void settingsDialog::on_pushButton_4_clicked()
{
    // save settings

    bool success = true;

    // if any change made
    if(settingsChanged){
        success = settingsDialog::saveSettings();
    }


    if(success){
        ui->label->setHidden(true);
        QMessageBox::information(this, "Oznámení", "Nastavení bylo úspěšně uloženo");
    }

    settingsDialog::settingsChanged = false;
    this->close();
}

void settingsDialog::on_pushButton_5_clicked()
{
    // check new version

    QNetworkRequest request;
    request.setUrl(QUrl("https://api.github.com/repos/RxiPland/y2mate_desktop/releases/latest"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    request.setHeader(QNetworkRequest::UserAgentHeader, userAgent);

    QNetworkReply *replyGet = manager.get(request);

    while (!replyGet->isFinished())
    {
        qApp->processEvents();
    }

    if(replyGet->error() != QNetworkReply::NoError){
        return;
    }

    QByteArray response = replyGet->readAll();
    replyGet->deleteLater();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
    QJsonObject jsonObject = jsonResponse.object();

    QString newestVersion = jsonObject["tag_name"].toString();

    if (newestVersion != appVersion && newestVersion != ""){

        QMessageBox msgBox;
        msgBox.setWindowTitle("Aktualizace");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Je dostupná novější verze y2mate desktop.\n\nDostupná verze: " + newestVersion + "\nVaše verze: " + appVersion  +"\n\nPři instalaci nové verze se předchozí automaticky odstraní.");

        QAbstractButton* pButtonYes = msgBox.addButton("  Otevřít odkaz  ", QMessageBox::YesRole);
        msgBox.addButton("Zrušit", QMessageBox::NoRole);
        msgBox.exec();

        if (msgBox.clickedButton() == pButtonYes) {
            ShellExecute(0, 0, L"https://github.com/RxiPland/y2mate_desktop", 0, 0, SW_HIDE);
        }

    } else{
        QMessageBox::information(this, "Aktualizace", QString("Již máte nejnovější verzi (%1)").arg(settingsDialog::appVersion));
    }
}

void settingsDialog::on_checkBox_clicked()
{
    // replace with hash

   settingsDialog::replaceNameWithHash = ui->checkBox->isChecked();

   if(!settingsDialog::settingsChanged){
       ui->label->setHidden(false);
       settingsDialog::settingsChanged = true;
   }
}

void settingsDialog::on_checkBox_2_clicked()
{
    // replace with underscores

    settingsDialog::replaceNameWithUnderscores = ui->checkBox_2->isChecked();

    if(!settingsDialog::settingsChanged){
        ui->label->setHidden(false);
        settingsDialog::settingsChanged = true;
    }
}

void settingsDialog::on_checkBox_3_clicked()
{
    // default download path

    bool isChecked = ui->checkBox_3->isChecked();

    if(isChecked){
        ui->pushButton->setDisabled(false);

    } else{
        ui->pushButton->setDisabled(true);
    }

    settingsDialog::lastPathEnabled = !isChecked;

    if(!settingsDialog::settingsChanged){
        ui->label->setHidden(false);
        settingsDialog::settingsChanged = true;
    }
}

void settingsDialog::on_checkBox_4_clicked()
{
    // allow history

    settingsDialog::allowHistory = ui->checkBox_4->isChecked();

    if(!settingsDialog::settingsChanged){
        ui->label->setHidden(false);
        settingsDialog::settingsChanged = true;
    }
}

void settingsDialog::on_checkBox_5_clicked()
{
    // allow automatic updates

    settingsDialog::checkForUpdates = ui->checkBox_5->isChecked();

    if(!settingsDialog::settingsChanged){
        ui->label->setHidden(false);
        settingsDialog::settingsChanged = true;
    }
}
