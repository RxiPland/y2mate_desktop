/********************************************************************************
** Form generated from reading UI file 'searchvideowindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHVIDEOWINDOW_H
#define UI_SEARCHVIDEOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchVideoWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SearchVideoWindow)
    {
        if (SearchVideoWindow->objectName().isEmpty())
            SearchVideoWindow->setObjectName("SearchVideoWindow");
        SearchVideoWindow->resize(800, 600);
        centralwidget = new QWidget(SearchVideoWindow);
        centralwidget->setObjectName("centralwidget");
        SearchVideoWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SearchVideoWindow);
        menubar->setObjectName("menubar");
        SearchVideoWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SearchVideoWindow);
        statusbar->setObjectName("statusbar");
        SearchVideoWindow->setStatusBar(statusbar);

        retranslateUi(SearchVideoWindow);

        QMetaObject::connectSlotsByName(SearchVideoWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SearchVideoWindow)
    {
        SearchVideoWindow->setWindowTitle(QCoreApplication::translate("SearchVideoWindow", "SearchVideoWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchVideoWindow: public Ui_SearchVideoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHVIDEOWINDOW_H
