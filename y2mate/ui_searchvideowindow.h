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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchVideoWindow
{
public:
    QAction *action_menu1_1;
    QAction *action_menu1_2;
    QAction *action_menu1_3;
    QAction *action_menu2_6;
    QAction *action_menu_2_1_1;
    QAction *action_menu_2_1_2;
    QAction *action_menu_2_1_3;
    QAction *action_menu_2_2_1;
    QAction *action_menu_2_2_2;
    QAction *action_menu_2_2_3;
    QAction *action_menu_2_3_1;
    QAction *action_menu_2_3_2;
    QAction *action_menu_2_3_3;
    QAction *action_menu_2_4_1;
    QAction *action_menu_2_4_2;
    QAction *action_menu_2_4_3;
    QAction *action_menu_2_5_1;
    QAction *action_menu_2_5_2;
    QAction *action_menu_2_5_3;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menubar;
    QMenu *menu_1;
    QMenu *menu_2;
    QMenu *menu2_1;
    QMenu *menu2_2;
    QMenu *menu2_3;
    QMenu *menu2_4;
    QMenu *menu2_5;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SearchVideoWindow)
    {
        if (SearchVideoWindow->objectName().isEmpty())
            SearchVideoWindow->setObjectName("SearchVideoWindow");
        SearchVideoWindow->resize(553, 183);
        action_menu1_1 = new QAction(SearchVideoWindow);
        action_menu1_1->setObjectName("action_menu1_1");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/y2mate.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_menu1_1->setIcon(icon);
        action_menu1_2 = new QAction(SearchVideoWindow);
        action_menu1_2->setObjectName("action_menu1_2");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/github.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_menu1_2->setIcon(icon1);
        action_menu1_3 = new QAction(SearchVideoWindow);
        action_menu1_3->setObjectName("action_menu1_3");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/settings.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_menu1_3->setIcon(icon2);
        action_menu2_6 = new QAction(SearchVideoWindow);
        action_menu2_6->setObjectName("action_menu2_6");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/delete.ico"), QSize(), QIcon::Normal, QIcon::Off);
        action_menu2_6->setIcon(icon3);
        action_menu_2_1_1 = new QAction(SearchVideoWindow);
        action_menu_2_1_1->setObjectName("action_menu_2_1_1");
        action_menu_2_1_2 = new QAction(SearchVideoWindow);
        action_menu_2_1_2->setObjectName("action_menu_2_1_2");
        action_menu_2_1_3 = new QAction(SearchVideoWindow);
        action_menu_2_1_3->setObjectName("action_menu_2_1_3");
        action_menu_2_1_3->setEnabled(false);
        action_menu_2_2_1 = new QAction(SearchVideoWindow);
        action_menu_2_2_1->setObjectName("action_menu_2_2_1");
        action_menu_2_2_2 = new QAction(SearchVideoWindow);
        action_menu_2_2_2->setObjectName("action_menu_2_2_2");
        action_menu_2_2_3 = new QAction(SearchVideoWindow);
        action_menu_2_2_3->setObjectName("action_menu_2_2_3");
        action_menu_2_2_3->setEnabled(false);
        action_menu_2_3_1 = new QAction(SearchVideoWindow);
        action_menu_2_3_1->setObjectName("action_menu_2_3_1");
        action_menu_2_3_2 = new QAction(SearchVideoWindow);
        action_menu_2_3_2->setObjectName("action_menu_2_3_2");
        action_menu_2_3_3 = new QAction(SearchVideoWindow);
        action_menu_2_3_3->setObjectName("action_menu_2_3_3");
        action_menu_2_3_3->setEnabled(false);
        action_menu_2_4_1 = new QAction(SearchVideoWindow);
        action_menu_2_4_1->setObjectName("action_menu_2_4_1");
        action_menu_2_4_2 = new QAction(SearchVideoWindow);
        action_menu_2_4_2->setObjectName("action_menu_2_4_2");
        action_menu_2_4_3 = new QAction(SearchVideoWindow);
        action_menu_2_4_3->setObjectName("action_menu_2_4_3");
        action_menu_2_4_3->setEnabled(false);
        action_menu_2_5_1 = new QAction(SearchVideoWindow);
        action_menu_2_5_1->setObjectName("action_menu_2_5_1");
        action_menu_2_5_2 = new QAction(SearchVideoWindow);
        action_menu_2_5_2->setObjectName("action_menu_2_5_2");
        action_menu_2_5_3 = new QAction(SearchVideoWindow);
        action_menu_2_5_3->setObjectName("action_menu_2_5_3");
        action_menu_2_5_3->setEnabled(false);
        centralwidget = new QWidget(SearchVideoWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_2 = new QSpacerItem(8, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMinimumSize(QSize(0, 25));
        QFont font;
        font.setPointSize(9);
        lineEdit->setFont(font);
        lineEdit->setMaxLength(9999);
        lineEdit->setClearButtonEnabled(true);

        verticalLayout->addWidget(lineEdit);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(160, 30));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(8, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        SearchVideoWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SearchVideoWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 553, 21));
        menu_1 = new QMenu(menubar);
        menu_1->setObjectName("menu_1");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        menu2_1 = new QMenu(menu_2);
        menu2_1->setObjectName("menu2_1");
        menu2_2 = new QMenu(menu_2);
        menu2_2->setObjectName("menu2_2");
        menu2_3 = new QMenu(menu_2);
        menu2_3->setObjectName("menu2_3");
        menu2_4 = new QMenu(menu_2);
        menu2_4->setObjectName("menu2_4");
        menu2_5 = new QMenu(menu_2);
        menu2_5->setObjectName("menu2_5");
        SearchVideoWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(SearchVideoWindow);
        statusBar->setObjectName("statusBar");
        SearchVideoWindow->setStatusBar(statusBar);

        menubar->addAction(menu_1->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu_1->addAction(action_menu1_1);
        menu_1->addAction(action_menu1_2);
        menu_1->addSeparator();
        menu_1->addAction(action_menu1_3);
        menu_2->addAction(menu2_1->menuAction());
        menu_2->addAction(menu2_2->menuAction());
        menu_2->addAction(menu2_3->menuAction());
        menu_2->addAction(menu2_4->menuAction());
        menu_2->addAction(menu2_5->menuAction());
        menu_2->addSeparator();
        menu_2->addAction(action_menu2_6);
        menu2_1->addAction(action_menu_2_1_1);
        menu2_1->addAction(action_menu_2_1_2);
        menu2_1->addSeparator();
        menu2_1->addAction(action_menu_2_1_3);
        menu2_2->addAction(action_menu_2_2_1);
        menu2_2->addAction(action_menu_2_2_2);
        menu2_2->addSeparator();
        menu2_2->addAction(action_menu_2_2_3);
        menu2_3->addAction(action_menu_2_3_1);
        menu2_3->addAction(action_menu_2_3_2);
        menu2_3->addSeparator();
        menu2_3->addAction(action_menu_2_3_3);
        menu2_4->addAction(action_menu_2_4_1);
        menu2_4->addAction(action_menu_2_4_2);
        menu2_4->addSeparator();
        menu2_4->addAction(action_menu_2_4_3);
        menu2_5->addAction(action_menu_2_5_1);
        menu2_5->addAction(action_menu_2_5_2);
        menu2_5->addSeparator();
        menu2_5->addAction(action_menu_2_5_3);

        retranslateUi(SearchVideoWindow);

        QMetaObject::connectSlotsByName(SearchVideoWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SearchVideoWindow)
    {
        SearchVideoWindow->setWindowTitle(QCoreApplication::translate("SearchVideoWindow", "y2mate desktop", nullptr));
        action_menu1_1->setText(QCoreApplication::translate("SearchVideoWindow", "y2mate", nullptr));
        action_menu1_2->setText(QCoreApplication::translate("SearchVideoWindow", "Zdrojov\303\275 k\303\263d", nullptr));
        action_menu1_3->setText(QCoreApplication::translate("SearchVideoWindow", "Nastaven\303\255", nullptr));
        action_menu2_6->setText(QCoreApplication::translate("SearchVideoWindow", "Smazat historii", nullptr));
        action_menu_2_1_1->setText(QCoreApplication::translate("SearchVideoWindow", "Pou\305\276\303\255t", nullptr));
        action_menu_2_1_2->setText(QCoreApplication::translate("SearchVideoWindow", "Otev\305\231\303\255t", nullptr));
        action_menu_2_1_3->setText(QCoreApplication::translate("SearchVideoWindow", "D\303\251lka:", nullptr));
        action_menu_2_2_1->setText(QCoreApplication::translate("SearchVideoWindow", "Pou\305\276\303\255t", nullptr));
        action_menu_2_2_2->setText(QCoreApplication::translate("SearchVideoWindow", "Otev\305\231\303\255t", nullptr));
        action_menu_2_2_3->setText(QCoreApplication::translate("SearchVideoWindow", "D\303\251lka:", nullptr));
        action_menu_2_3_1->setText(QCoreApplication::translate("SearchVideoWindow", "Pou\305\276\303\255t", nullptr));
        action_menu_2_3_2->setText(QCoreApplication::translate("SearchVideoWindow", "Otev\305\231\303\255t", nullptr));
        action_menu_2_3_3->setText(QCoreApplication::translate("SearchVideoWindow", "D\303\251lka", nullptr));
        action_menu_2_4_1->setText(QCoreApplication::translate("SearchVideoWindow", "Pou\305\276\303\255t", nullptr));
        action_menu_2_4_2->setText(QCoreApplication::translate("SearchVideoWindow", "Otev\305\231\303\255t", nullptr));
        action_menu_2_4_3->setText(QCoreApplication::translate("SearchVideoWindow", "D\303\251lka", nullptr));
        action_menu_2_5_1->setText(QCoreApplication::translate("SearchVideoWindow", "Pou\305\276\303\255t", nullptr));
        action_menu_2_5_2->setText(QCoreApplication::translate("SearchVideoWindow", "Otev\305\231\303\255t", nullptr));
        action_menu_2_5_3->setText(QCoreApplication::translate("SearchVideoWindow", "D\303\251lka:", nullptr));
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("SearchVideoWindow", "Vlo\305\276te URL videa", nullptr));
        pushButton->setText(QCoreApplication::translate("SearchVideoWindow", "Naj\303\255t", nullptr));
        menu_1->setTitle(QCoreApplication::translate("SearchVideoWindow", "Mo\305\276nosti", nullptr));
        menu_2->setTitle(QCoreApplication::translate("SearchVideoWindow", "Historie", nullptr));
        menu2_1->setTitle(QCoreApplication::translate("SearchVideoWindow", "1", nullptr));
        menu2_2->setTitle(QCoreApplication::translate("SearchVideoWindow", "2", nullptr));
        menu2_3->setTitle(QCoreApplication::translate("SearchVideoWindow", "3", nullptr));
        menu2_4->setTitle(QCoreApplication::translate("SearchVideoWindow", "4", nullptr));
        menu2_5->setTitle(QCoreApplication::translate("SearchVideoWindow", "5", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchVideoWindow: public Ui_SearchVideoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHVIDEOWINDOW_H
