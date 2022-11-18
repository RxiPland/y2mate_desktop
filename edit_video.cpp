#include "edit_video.h"
#include "ui_edit_video.h"
#include <QFile>
#include <QMessageBox>
#include <windows.h>
#include <QDir>

QString video_name;   // video name without file extension
QString file_extension;   // file extension with dot
QString dir_path = "/";   // path of downloaded video
int video_length[3] = {0,0,0};  // hours:minutes:seconds


edit_video::edit_video(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_video)
{
    ui->setupUi(this);
    ui->pushButton_3->setFocus();
    ui->pushButton_3->setDefault(true);
}

edit_video::~edit_video()
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

void edit_video::set_info(QString name, QString length, QString path){
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

    edit_video::on_pushButton_2_clicked();
}

void edit_video::disable_widgets(bool disable){

    ui->lineEdit->setDisabled(disable);
    ui->timeEdit->setDisabled(disable);
    ui->timeEdit_2->setDisabled(disable);

    ui->pushButton->setDisabled(disable);
    ui->pushButton_2->setDisabled(disable);
    ui->pushButton_3->setDisabled(disable);

    ui->comboBox->setDisabled(disable);
}

void edit_video::on_pushButton_2_clicked()
{
    // reset widgets values
    ui->lineEdit->setText(video_name);
    ui->timeEdit->setTime(QTime(0, 0, 0));
    ui->timeEdit_2->setTime(QTime(video_length[0], video_length[1], video_length[2]));
}

void edit_video::on_pushButton_clicked()
{
    // exit window
    this->close();
}


void edit_video::on_pushButton_3_clicked()
{
    // start convert button
    // ffmpeg -i "NÁZEV+X" -vn -y -hide_banner -loglevel error -c:a copy "NÁZEV-X"

    edit_video::disable_widgets(true);

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

    ULONG_PTR ret;
    std::wstring command;

    QMessageBox msgBox;
    msgBox.setWindowTitle("Úprava videa");

    if((start_changed || end_changed) && !filetype_changed){
        // cut time, without changing file type format

        // rename file
        command = ("/C ren \"" + dir_path + video_name + file_extension + "\" \"" + name + "THIS_IS_TEMP_FILE" + file_extension + "\"").toStdWString();
        ShellExecute(0, L"open", L"cmd.exe", command.c_str(), 0, SW_HIDE);

        // convert renamed file & delete
        QString time_params = "-ss " + QString::number(time_start[0]) + ":" + QString::number(time_start[1]) + ":" + QString::number(time_start[2]) + " -to " + QString::number(time_end[0]) + ":" + QString::number(time_end[1]) + ":" + QString::number(time_end[2]);
        command = ("/C ffmpeg.exe -i \"" + dir_path + name + "THIS_IS_TEMP_FILE" + file_extension + "\" " + time_params + " -y -hide_banner -loglevel error -c:a copy \"" + dir_path + name + filetype + "\" & del \"" + dir_path + name + "THIS_IS_TEMP_FILE" + file_extension + "\"").toStdWString();


        SHELLEXECUTEINFO ShExecInfo ={0};
        ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        ShExecInfo.fMask = SEE_MASK_INVOKEIDLIST ;
        ShExecInfo.hwnd = NULL;
        ShExecInfo.lpVerb = L"open";
        ShExecInfo.lpFile = L"cmd.exe";
        ShExecInfo.lpParameters = command.c_str();
        ShExecInfo.lpDirectory = (QDir::currentPath()+ "/tools").toStdWString().c_str();
        ShExecInfo.nShow = SW_HIDE;
        ShExecInfo.hInstApp = NULL;
        auto ret = ShellExecuteEx(&ShExecInfo);
        WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
        CloseHandle(ShExecInfo.hProcess);

        if(ret==1){
            msgBox.setText("Čas videa byl úspěšně upraven");

        } else{
            msgBox.setText("Nastala chyba!\n\nShellExecuteEx() response kód: " + QString::number(ret));
        }


    } else if(start_changed || end_changed || filetype_changed){
        // cut time AND convert to different file type

        // rename file
        command = ("/C ren \"" + dir_path + video_name + file_extension + "\" \"" + name + "THIS_IS_TEMP_FILE" + file_extension + "\"").toStdWString();
        ShellExecute(0, L"open", L"cmd.exe", command.c_str(), 0, SW_HIDE);

        // convert renamed file & delete
        QString time_params = "-ss " + QString::number(time_start[0]) + ":" + QString::number(time_start[1]) + ":" + QString::number(time_start[2]) + " -to " + QString::number(time_end[0]) + ":" + QString::number(time_end[1]) + ":" + QString::number(time_end[2]);

        if(filetype == ".ogg"){

            command = ("/C ffmpeg.exe -i \"" + dir_path + name + "THIS_IS_TEMP_FILE" + file_extension + "\" " + time_params + " -y -vn -crf 20 -codec:a libvorbis -hide_banner -loglevel error \"" + dir_path + name + filetype + "\" & del \"" + dir_path + name + "THIS_IS_TEMP_FILE" + file_extension + "\"").toStdWString();

        }else if(filetype == ".wav"){

            command = ("/C ffmpeg.exe -i \"" + dir_path + name + "THIS_IS_TEMP_FILE" + file_extension + "\" " + time_params + " -y -vn -crf 20 -acodec pcm_s16le -hide_banner -loglevel error \"" + dir_path + name + filetype + "\" & del \"" + dir_path + name + "THIS_IS_TEMP_FILE" + file_extension + "\"").toStdWString();

        }else {

            command = ("/C ffmpeg.exe -i \"" + dir_path + name + "THIS_IS_TEMP_FILE" + file_extension + "\" " + time_params + " -y -vn -crf 20 -c:a libmp3lame -hide_banner -loglevel error \"" + dir_path + name + filetype + "\" & del \"" + dir_path + name + "THIS_IS_TEMP_FILE" + file_extension + "\"").toStdWString();
        }

        SHELLEXECUTEINFO ShExecInfo ={0};
        ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        ShExecInfo.fMask = SEE_MASK_INVOKEIDLIST ;
        ShExecInfo.hwnd = NULL;
        ShExecInfo.lpVerb = L"open";
        ShExecInfo.lpFile = L"cmd.exe";
        ShExecInfo.lpParameters = command.c_str();
        ShExecInfo.lpDirectory = (QDir::currentPath()+ "/tools").toStdWString().c_str();
        ShExecInfo.nShow = SW_HIDE;
        ShExecInfo.hInstApp = NULL;
        auto ret = ShellExecuteEx(&ShExecInfo);
        WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
        CloseHandle(ShExecInfo.hProcess);

        if(ret==1){
            msgBox.setText("Soubor byl úspěšně překonvertován");

        } else{
            msgBox.setText("Nastala chyba!\n\nShellExecuteEx() response kód: " + QString::number(ret));
        }


    } else if(name_changed){
        // only rename

        QFile new_name_path(dir_path + name + file_extension);

        if(new_name_path.exists()){

            QMessageBox msgBoxExists;
            msgBoxExists.setWindowTitle("Nový název");
            msgBoxExists.setText("Soubor s tímto názvem již existuje. Starý soubor se automaticky odstraní!");
            msgBoxExists.addButton("Ok", QMessageBox::YesRole);
            QAbstractButton* pButtonCancel = msgBoxExists.addButton("Zrušit", QMessageBox::NoRole);
            msgBoxExists.exec();

            if (msgBoxExists.clickedButton() == pButtonCancel) {

                return;
            }
        }

        command = ("/C ren \"" + dir_path + video_name + file_extension + "\" \"" + name + file_extension + "\"").toStdWString();
        ret = reinterpret_cast<ULONG_PTR>(ShellExecute(0, L"open", L"cmd.exe", command.c_str(), 0, SW_HIDE));

        if(ret>32){
            msgBox.setText("Soubor byl úspěšně přejmenován");

        } else{
            msgBox.setText("Nastala chyba!\n\nShellExecute() response kód: " + QString::number(ret));
        }

    } else{

        msgBox.setText("Nebyly provedeny žádné změny");
    }

    // ask user to open new file or skip
    msgBox.addButton("Ok", QMessageBox::YesRole);
    QAbstractButton* pButtonOpen = msgBox.addButton("Otevřít soubor", QMessageBox::YesRole);
    msgBox.exec();

    if (msgBox.clickedButton() == pButtonOpen) {

        QString cesta_k_souboru = "\"" + dir_path + name + filetype + "\"";
        std::wstring command = cesta_k_souboru.toStdWString();

        ShellExecute(0, L"open", command.c_str(), 0, 0, SW_RESTORE);
    }

    edit_video::on_pushButton_clicked();
}
