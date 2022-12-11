#include "editvideowindow.h"
#include "ui_editvideowindow.h"
#include "threadfunctions.h"

#include <QFile>
#include <QMessageBox>
#include <windows.h>
#include <QDir>

QString video_name;   // video name without file extension
QString file_extension;   // file extension with dot
QString dir_path = "/";   // path of downloaded video
int video_length[3] = {0,0,0};  // hours:minutes:seconds


EditVideoWindow::EditVideoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditVideoWindow)
{
    ui->setupUi(this);
    ui->pushButton_3->setFocus();
    ui->pushButton_3->setDefault(true);
    ui->actionVymazat_p_vodn_soubor->setChecked(true);
}

EditVideoWindow::~EditVideoWindow()
{
    delete ui;
}


bool compare_arrays(int first[3], int second[3]){
    //comparing only 3-item arrays

    for(int i=0; i<3; i++){

        if(first[i] == second[i]){

        } else{
            return true;
        }
    }

    return false;
}

void EditVideoWindow::set_info(QString name, QString length, QString path){
    //save info about downloaded file

    dir_path = path;

    QStringList splitted = name.split(".");
    file_extension = "." + splitted.last();

    splitted.pop_back();
    video_name = splitted.join(".");

    if (length.count(":") == 2){

        QStringList string_length = length.split(":");

        for(int i=0; i<3; i++){
            video_length[i] = string_length[i].toInt();
        }
    }

    ui->timeEdit->setMaximumTime(QTime(video_length[0], video_length[1], video_length[2]));
    ui->timeEdit_2->setMaximumTime(QTime(video_length[0], video_length[1], video_length[2]));
    ui->comboBox->setCurrentText(file_extension);

    EditVideoWindow::on_pushButton_2_clicked();
}

void EditVideoWindow::disable_widgets(bool disable){

    ui->lineEdit->setDisabled(disable);
    ui->timeEdit->setDisabled(disable);
    ui->timeEdit_2->setDisabled(disable);

    ui->pushButton->setDisabled(disable);
    ui->pushButton_2->setDisabled(disable);
    ui->pushButton_3->setDisabled(disable);

    ui->comboBox->setDisabled(disable);

    ui->actionVymazat_p_vodn_soubor->setDisabled(disable);
}

void EditVideoWindow::on_pushButton_2_clicked()
{
    // reset widgets values
    ui->lineEdit->setText(video_name);
    ui->timeEdit->setTime(QTime(0, 0, 0));
    ui->timeEdit_2->setTime(QTime(video_length[0], video_length[1], video_length[2]));
}

void EditVideoWindow::on_pushButton_clicked()
{
    // exit window
    this->close();
}


void EditVideoWindow::on_pushButton_3_clicked()
{
    // start convert button
    // ffmpeg -i "NÁZEV+X" -vn -y -hide_banner -loglevel error -c:a copy "NÁZEV-X"

    EditVideoWindow::disable_widgets(true);

    QString name = ui->lineEdit->text();
    QString filetype = ui->comboBox->currentText();

    QTime qtime_start = ui->timeEdit->time();

    int time_start[3];
    time_start[0] = qtime_start.hour();
    time_start[1] = qtime_start.minute();
    time_start[2] = qtime_start.second();

    QTime qtime_end = ui->timeEdit_2->time();

    int time_end[3];
    time_end[0] = qtime_end.hour();
    time_end[1] = qtime_end.minute();
    time_end[2] = qtime_end.second();

    int time_start_default[3] = {0,0,0};

    bool name_changed = name != video_name;
    bool start_changed = compare_arrays(time_start, time_start_default);
    bool end_changed = compare_arrays(time_end, video_length);
    bool filetype_changed = filetype != file_extension;

    QFile new_file(dir_path + name + filetype);

    QMessageBox msgBox;
    msgBox.setWindowTitle("Úprava videa");

    if(!(name_changed || start_changed || end_changed || filetype_changed)){
        // nothing changed

        msgBox.setText("Nebyly provedeny žádné změny.");
        msgBox.addButton("Ok", QMessageBox::YesRole);
        QAbstractButton* pButtonOpen = msgBox.addButton("Otevřít soubor", QMessageBox::YesRole);
        QAbstractButton* pButtonCancel = msgBox.addButton("Zrušit", QMessageBox::YesRole);
        msgBox.exec();

        if (msgBox.clickedButton() == pButtonOpen) {
            // open file by default media player

            ShellExecute(0, L"open", new_file.fileName().toStdWString().c_str(), 0, 0, SW_RESTORE);

        } else if(msgBox.clickedButton() == pButtonCancel){

            EditVideoWindow::disable_widgets(false);
            return;
        }

        EditVideoWindow::on_pushButton_clicked();
        return;

    } else if(!ui->actionVymazat_p_vodn_soubor->isChecked() && !(name_changed || filetype_changed)){
        // the file is not to be deleted, but filetype or name is the same

        QMessageBox::warning(this, "Chyba", "Pokud chcete ponechat původní soubor, musí mít nový jiné jméno nebo koncovku!");
        EditVideoWindow::disable_widgets(false);
        return;

    } else if(new_file.exists() && (name_changed || filetype_changed)){
        // file with this new name already exists

        QMessageBox::warning(this, "Chyba", "Soubor s tímto názvem a koncovkou již ve složce existuje!");
        EditVideoWindow::disable_widgets(false);
        return;
    }

    std::wstring command;

    if((start_changed || end_changed) && !filetype_changed){
        // cut time, without changing file type

        QString time_params = "-ss " + QString::number(time_start[0]) + ":" + QString::number(time_start[1]) + ":" + QString::number(time_start[2]) + " -to " + QString::number(time_end[0]) + ":" + QString::number(time_end[1]) + ":" + QString::number(time_end[2]);

        // convert file and delete original file
        if(ui->actionVymazat_p_vodn_soubor->isChecked()){

            // rename file
            command = ("/C ren \"" + dir_path + video_name + file_extension + "\" \"" + name + "_ORIGINAL" + file_extension + "\"").toStdWString();

            // convert renamed file & delete
            command += (" & ffmpeg.exe -i \"" + dir_path + name + "_ORIGINAL" + file_extension + "\" " + time_params + " -y -hide_banner -loglevel error -c:a copy \"" + new_file.fileName() + "\"").toStdWString();

            // delete _ORIGINAL file
            command += (" & del \"" + dir_path + name + "_ORIGINAL" + file_extension + "\"").toStdWString();

        } else {
            // convert file without deletion (with new name)
            command = ("/C ffmpeg.exe -i \"" + dir_path + video_name + file_extension + "\" " + time_params + " -y -hide_banner -loglevel error -c:a copy \"" + new_file.fileName() + "\"").toStdWString();
        }

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

        // check if created file exists
        if(new_file.exists()){
            msgBox.setText("Soubor byl úspěšně překonvertován");

        } else{
            QMessageBox::warning(this, "Chyba", "Nastala neznámá chyba a soubor se nepodařilo překonvertovat!");
            return;
        }


    } else if(start_changed || end_changed || filetype_changed){
        // cut time AND convert to different file type

        QString audio_parameters = "";
        QString time_params = "-ss " + QString::number(time_start[0]) + ":" + QString::number(time_start[1]) + ":" + QString::number(time_start[2]) + " -to " + QString::number(time_end[0]) + ":" + QString::number(time_end[1]) + ":" + QString::number(time_end[2]);

        if(ui->actionVymazat_p_vodn_soubor->isChecked()){
            // rename & convert & delete


            // rename file
            command = ("/C ren \"" + dir_path + video_name + file_extension + "\" \"" + name + "_ORIGINAL" + file_extension + "\"").toStdWString();

            if(filetype == ".ogg"){

                audio_parameters = "-codec:a libvorbis";

            } else if(filetype == ".wav"){

                audio_parameters = "-acodec pcm_s16le";

            } else {
                audio_parameters = "-c:a libmp3lame";
            }

            // convert renamed file
            command += (" & ffmpeg.exe -i \"" + dir_path + name + "_ORIGINAL" + file_extension + "\" " + time_params + " -y -vn -crf 20 " + audio_parameters + " -hide_banner -loglevel error \"" + new_file.fileName() + "\"").toStdWString();

            // delete _ORIGINAL file
            command += (" & del \"" + dir_path + name + "_ORIGINAL" + file_extension + "\"").toStdWString();

        } else{
            // convert without deletion

            if(filetype == ".ogg"){

                audio_parameters = "-codec:a libvorbis";

            }else if(filetype == ".wav"){

                audio_parameters = "-acodec pcm_s16le";

            }else {
                audio_parameters = "-c:a libmp3lame";
            }

            // convert file
            command = ("/C ffmpeg.exe -i \"" + dir_path + video_name + file_extension + "\" " + time_params + " -y -vn -crf 20 " + audio_parameters + " -hide_banner -loglevel error \"" + new_file.fileName() + "\"").toStdWString();
        }


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


        // check if created file exists
        if(new_file.exists()){
            msgBox.setText("Soubor byl úspěšně překonvertován");

        } else{

            QMessageBox::warning(this, "Chyba", "Nastala neznámá chyba a soubor se nepodařilo překonvertovat!");
            EditVideoWindow::disable_widgets(false);
            return;
        }

    } else if(name_changed){
        // rename or duplicate

        if(ui->actionVymazat_p_vodn_soubor->isChecked()){
            // rename

            command = ("/C ren \"" + dir_path + video_name + file_extension + "\" \"" + name + file_extension + "\"").toStdWString();

            ThreadFunctions shellThread;
            shellThread.operace = 2;  // Thread func

            shellThread.ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
            shellThread.ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
            shellThread.ShExecInfo.hwnd = NULL;
            shellThread.ShExecInfo.lpVerb = L"open";
            shellThread.ShExecInfo.lpFile = L"cmd.exe";
            shellThread.ShExecInfo.lpParameters = command.c_str();
            shellThread.ShExecInfo.lpDirectory = NULL;
            shellThread.ShExecInfo.nShow = SW_HIDE;
            shellThread.ShExecInfo.hInstApp = NULL;

            shellThread.start();

            // wait for thread to complete
            while(shellThread.isRunning()){
                qApp->processEvents();
            }


            if(new_file.exists()){
                msgBox.setText("Soubor byl úspěšně přejmenován");

            } else{
                QMessageBox::warning(this, "Chyba", "Nastala neznámá chyba a soubor se nepodařilo přejmenovat!");
                EditVideoWindow::disable_widgets(false);
                return;
            }

        } else{
            // duplicate

            command = ("/C copy \"" + dir_path + video_name + file_extension + "\" \"" + dir_path + name + file_extension + "\"").toStdWString();

            ThreadFunctions shellThread;
            shellThread.operace = 2;  // Thread func

            shellThread.ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
            shellThread.ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
            shellThread.ShExecInfo.hwnd = NULL;
            shellThread.ShExecInfo.lpVerb = L"open";
            shellThread.ShExecInfo.lpFile = L"cmd.exe";
            shellThread.ShExecInfo.lpParameters = command.c_str();
            shellThread.ShExecInfo.lpDirectory = NULL;
            shellThread.ShExecInfo.nShow = SW_HIDE;
            shellThread.ShExecInfo.hInstApp = NULL;

            shellThread.start();

            // wait for thread to complete
            while(shellThread.isRunning()){
                qApp->processEvents();
            }

            if(new_file.exists()){
                msgBox.setText("Soubor byl úspěšně duplikován.");

            } else{
                QMessageBox::warning(this, "Chyba", "Nastala neznámá chyba a soubor se nepodařilo duplikovat!");
                EditVideoWindow::disable_widgets(false);
                return;
            }
        }

    } else{

        msgBox.setText("Nebyly provedeny žádné změny.");
    }

    // ask user to open created file or skip
    msgBox.addButton("Ok", QMessageBox::YesRole);
    QAbstractButton* pButtonOpenFile = msgBox.addButton("Otevřít soubor", QMessageBox::YesRole);
    QAbstractButton* pButtonOpenDir = msgBox.addButton("Otevřít umístění", QMessageBox::YesRole);
    msgBox.exec();

    if (msgBox.clickedButton() == pButtonOpenFile) {

        ShellExecute(0, L"open", new_file.fileName().toStdWString().c_str(), 0, 0, SW_RESTORE);

    } else if (msgBox.clickedButton() == pButtonOpenDir){
        ShellExecute(0, L"open", L"explorer.exe", dir_path.toStdWString().c_str(), 0, SW_RESTORE);
    }

    EditVideoWindow::on_pushButton_clicked();
}


void EditVideoWindow::on_timeEdit_userTimeChanged(const QTime &time)
{
    ui->timeEdit_2->setMinimumTime(time);

    QTime time2 = ui->timeEdit_2->time();
    ui->timeEdit->setMaximumTime(time2.addSecs(-1));
}


void EditVideoWindow::on_timeEdit_2_userTimeChanged(const QTime &time2)
{
    QTime time = ui->timeEdit->time();
    QTime zero = QTime(0,0,0,0);

    ui->timeEdit->setMaximumTime(time2.addSecs(-1));

    if(time == time2 && time != zero){
        ui->timeEdit->setTime(time2.addSecs(-1));

    } else if(time2 == zero){
        ui->timeEdit_2->setTime(zero.addSecs(1));
    }
}


void EditVideoWindow::on_lineEdit_returnPressed()
{
    EditVideoWindow::on_pushButton_3_clicked();
}

