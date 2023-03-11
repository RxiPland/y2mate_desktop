/********************************************************************************
** Form generated from reading UI file 'downloadvideowindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADVIDEOWINDOW_H
#define UI_DOWNLOADVIDEOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_downloadVideoWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *downloadVideoWindow)
    {
        if (downloadVideoWindow->objectName().isEmpty())
            downloadVideoWindow->setObjectName("downloadVideoWindow");
        downloadVideoWindow->resize(470, 209);
        centralwidget = new QWidget(downloadVideoWindow);
        centralwidget->setObjectName("centralwidget");
        downloadVideoWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(downloadVideoWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 470, 21));
        downloadVideoWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(downloadVideoWindow);
        statusbar->setObjectName("statusbar");
        downloadVideoWindow->setStatusBar(statusbar);

        retranslateUi(downloadVideoWindow);

        QMetaObject::connectSlotsByName(downloadVideoWindow);
    } // setupUi

    void retranslateUi(QMainWindow *downloadVideoWindow)
    {
        downloadVideoWindow->setWindowTitle(QCoreApplication::translate("downloadVideoWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class downloadVideoWindow: public Ui_downloadVideoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADVIDEOWINDOW_H
