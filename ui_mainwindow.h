/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actiony2mate_com;
    QAction *actionzdrojovy_kod;
    QAction *actionNastaven;
    QAction *actionSmazat_historii;
    QAction *actionPou_t;
    QAction *actionPou_t_2;
    QAction *actionPou_t_3;
    QAction *actionPou_t_4;
    QAction *actionPou_t_5;
    QAction *action_nazev;
    QAction *action_delka;
    QAction *action_nazev_2;
    QAction *action_delka_2;
    QAction *action_nazev_3;
    QAction *action_delka_3;
    QAction *action_nazev_4;
    QAction *action_delka_4;
    QAction *action_nazev_5;
    QAction *action_delka_5;
    QAction *actionOtev_t;
    QAction *actionOtev_t_2;
    QAction *actionOtev_t_3;
    QAction *actionOtev_t_4;
    QAction *actionOtev_t_5;
    QAction *actionD_lka;
    QAction *actionD_lka_2;
    QAction *actionD_lka_3;
    QAction *actionD_lka_4;
    QAction *actionD_lka_5;
    QAction *actionOtev_t_soubor;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_3;
    QLabel *label_4;
    QProgressBar *progressBar;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *label;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer_5;
    QComboBox *comboBox_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_6;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer_4;
    QMenuBar *menuBar;
    QMenu *menuInfo;
    QMenu *menuHistorie;
    QMenu *menu1;
    QMenu *menu2;
    QMenu *menu3;
    QMenu *menu4;
    QMenu *menu5;
    QMenu *menuUpravit_video;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(495, 330);
        MainWindow->setTabShape(QTabWidget::Triangular);
        actiony2mate_com = new QAction(MainWindow);
        actiony2mate_com->setObjectName("actiony2mate_com");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/y2mate.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actiony2mate_com->setIcon(icon);
        actionzdrojovy_kod = new QAction(MainWindow);
        actionzdrojovy_kod->setObjectName("actionzdrojovy_kod");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/github.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionzdrojovy_kod->setIcon(icon1);
        actionNastaven = new QAction(MainWindow);
        actionNastaven->setObjectName("actionNastaven");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/settings.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionNastaven->setIcon(icon2);
        actionSmazat_historii = new QAction(MainWindow);
        actionSmazat_historii->setObjectName("actionSmazat_historii");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/delete.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionSmazat_historii->setIcon(icon3);
        actionPou_t = new QAction(MainWindow);
        actionPou_t->setObjectName("actionPou_t");
        actionPou_t_2 = new QAction(MainWindow);
        actionPou_t_2->setObjectName("actionPou_t_2");
        actionPou_t_3 = new QAction(MainWindow);
        actionPou_t_3->setObjectName("actionPou_t_3");
        actionPou_t_4 = new QAction(MainWindow);
        actionPou_t_4->setObjectName("actionPou_t_4");
        actionPou_t_5 = new QAction(MainWindow);
        actionPou_t_5->setObjectName("actionPou_t_5");
        action_nazev = new QAction(MainWindow);
        action_nazev->setObjectName("action_nazev");
        action_delka = new QAction(MainWindow);
        action_delka->setObjectName("action_delka");
        action_nazev_2 = new QAction(MainWindow);
        action_nazev_2->setObjectName("action_nazev_2");
        action_delka_2 = new QAction(MainWindow);
        action_delka_2->setObjectName("action_delka_2");
        action_nazev_3 = new QAction(MainWindow);
        action_nazev_3->setObjectName("action_nazev_3");
        action_delka_3 = new QAction(MainWindow);
        action_delka_3->setObjectName("action_delka_3");
        action_nazev_4 = new QAction(MainWindow);
        action_nazev_4->setObjectName("action_nazev_4");
        action_delka_4 = new QAction(MainWindow);
        action_delka_4->setObjectName("action_delka_4");
        action_nazev_5 = new QAction(MainWindow);
        action_nazev_5->setObjectName("action_nazev_5");
        action_delka_5 = new QAction(MainWindow);
        action_delka_5->setObjectName("action_delka_5");
        actionOtev_t = new QAction(MainWindow);
        actionOtev_t->setObjectName("actionOtev_t");
        actionOtev_t_2 = new QAction(MainWindow);
        actionOtev_t_2->setObjectName("actionOtev_t_2");
        actionOtev_t_3 = new QAction(MainWindow);
        actionOtev_t_3->setObjectName("actionOtev_t_3");
        actionOtev_t_4 = new QAction(MainWindow);
        actionOtev_t_4->setObjectName("actionOtev_t_4");
        actionOtev_t_5 = new QAction(MainWindow);
        actionOtev_t_5->setObjectName("actionOtev_t_5");
        actionD_lka = new QAction(MainWindow);
        actionD_lka->setObjectName("actionD_lka");
        actionD_lka->setEnabled(false);
        actionD_lka_2 = new QAction(MainWindow);
        actionD_lka_2->setObjectName("actionD_lka_2");
        actionD_lka_2->setEnabled(false);
        actionD_lka_3 = new QAction(MainWindow);
        actionD_lka_3->setObjectName("actionD_lka_3");
        actionD_lka_3->setEnabled(false);
        actionD_lka_4 = new QAction(MainWindow);
        actionD_lka_4->setObjectName("actionD_lka_4");
        actionD_lka_4->setEnabled(false);
        actionD_lka_5 = new QAction(MainWindow);
        actionD_lka_5->setObjectName("actionD_lka_5");
        actionD_lka_5->setEnabled(false);
        actionOtev_t_soubor = new QAction(MainWindow);
        actionOtev_t_soubor->setObjectName("actionOtev_t_soubor");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/open_file.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionOtev_t_soubor->setIcon(icon4);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_3 = new QSpacerItem(20, 49, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setClearButtonEnabled(true);

        verticalLayout->addWidget(lineEdit);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        verticalSpacer_7 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout->addItem(verticalSpacer_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        verticalLayout_2->addWidget(comboBox);

        verticalSpacer_5 = new QSpacerItem(20, 7, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_5);

        comboBox_2 = new QComboBox(centralwidget);
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");

        verticalLayout_2->addWidget(comboBox_2);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(pushButton);

        verticalSpacer_6 = new QSpacerItem(20, 7, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_6);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout_4->addWidget(pushButton_2);


        horizontalLayout->addLayout(verticalLayout_4);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 61, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        verticalLayout_3->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 495, 21));
        menuInfo = new QMenu(menuBar);
        menuInfo->setObjectName("menuInfo");
        menuHistorie = new QMenu(menuBar);
        menuHistorie->setObjectName("menuHistorie");
        menu1 = new QMenu(menuHistorie);
        menu1->setObjectName("menu1");
        menu2 = new QMenu(menuHistorie);
        menu2->setObjectName("menu2");
        menu3 = new QMenu(menuHistorie);
        menu3->setObjectName("menu3");
        menu4 = new QMenu(menuHistorie);
        menu4->setObjectName("menu4");
        menu5 = new QMenu(menuHistorie);
        menu5->setObjectName("menu5");
        menuUpravit_video = new QMenu(menuBar);
        menuUpravit_video->setObjectName("menuUpravit_video");
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuInfo->menuAction());
        menuBar->addAction(menuHistorie->menuAction());
        menuBar->addAction(menuUpravit_video->menuAction());
        menuInfo->addAction(actiony2mate_com);
        menuInfo->addAction(actionzdrojovy_kod);
        menuInfo->addSeparator();
        menuInfo->addAction(actionNastaven);
        menuHistorie->addAction(menu1->menuAction());
        menuHistorie->addAction(menu2->menuAction());
        menuHistorie->addAction(menu3->menuAction());
        menuHistorie->addAction(menu4->menuAction());
        menuHistorie->addAction(menu5->menuAction());
        menuHistorie->addSeparator();
        menuHistorie->addAction(actionSmazat_historii);
        menu1->addAction(actionPou_t);
        menu1->addAction(actionOtev_t);
        menu1->addSeparator();
        menu1->addAction(actionD_lka);
        menu2->addAction(actionPou_t_2);
        menu2->addAction(actionOtev_t_2);
        menu2->addSeparator();
        menu2->addAction(actionD_lka_2);
        menu3->addAction(actionPou_t_3);
        menu3->addAction(actionOtev_t_3);
        menu3->addSeparator();
        menu3->addAction(actionD_lka_3);
        menu4->addAction(actionPou_t_4);
        menu4->addAction(actionOtev_t_4);
        menu4->addSeparator();
        menu4->addAction(actionD_lka_4);
        menu5->addAction(actionPou_t_5);
        menu5->addAction(actionOtev_t_5);
        menu5->addSeparator();
        menu5->addAction(actionD_lka_5);
        menuUpravit_video->addAction(actionOtev_t_soubor);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "y2mate - desktop", nullptr));
        actiony2mate_com->setText(QCoreApplication::translate("MainWindow", "y2mate.com", nullptr));
#if QT_CONFIG(tooltip)
        actiony2mate_com->setToolTip(QCoreApplication::translate("MainWindow", "y2mate.com", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        actiony2mate_com->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        actionzdrojovy_kod->setText(QCoreApplication::translate("MainWindow", "zdrojov\303\275 k\303\263d", nullptr));
        actionNastaven->setText(QCoreApplication::translate("MainWindow", "Nastaven\303\255", nullptr));
        actionSmazat_historii->setText(QCoreApplication::translate("MainWindow", "Smazat historii", nullptr));
        actionPou_t->setText(QCoreApplication::translate("MainWindow", "Pou\305\276\303\255t", nullptr));
        actionPou_t_2->setText(QCoreApplication::translate("MainWindow", "Pou\305\276\303\255t", nullptr));
        actionPou_t_3->setText(QCoreApplication::translate("MainWindow", "Pou\305\276\303\255t", nullptr));
        actionPou_t_4->setText(QCoreApplication::translate("MainWindow", "Pou\305\276\303\255t", nullptr));
        actionPou_t_5->setText(QCoreApplication::translate("MainWindow", "Pou\305\276\303\255t", nullptr));
        action_nazev->setText(QCoreApplication::translate("MainWindow", "[nazev]", nullptr));
        action_delka->setText(QCoreApplication::translate("MainWindow", "[delka]", nullptr));
        action_nazev_2->setText(QCoreApplication::translate("MainWindow", "[nazev]", nullptr));
        action_delka_2->setText(QCoreApplication::translate("MainWindow", "[delka]", nullptr));
        action_nazev_3->setText(QCoreApplication::translate("MainWindow", "[nazev]", nullptr));
        action_delka_3->setText(QCoreApplication::translate("MainWindow", "[delka]", nullptr));
        action_nazev_4->setText(QCoreApplication::translate("MainWindow", "[nazev]", nullptr));
        action_delka_4->setText(QCoreApplication::translate("MainWindow", "[delka]", nullptr));
        action_nazev_5->setText(QCoreApplication::translate("MainWindow", "[nazev]", nullptr));
        action_delka_5->setText(QCoreApplication::translate("MainWindow", "[delka]", nullptr));
        actionOtev_t->setText(QCoreApplication::translate("MainWindow", "Otev\305\231\303\255t", nullptr));
        actionOtev_t_2->setText(QCoreApplication::translate("MainWindow", "Otev\305\231\303\255t", nullptr));
        actionOtev_t_3->setText(QCoreApplication::translate("MainWindow", "Otev\305\231\303\255t", nullptr));
        actionOtev_t_4->setText(QCoreApplication::translate("MainWindow", "Otev\305\231\303\255t", nullptr));
        actionOtev_t_5->setText(QCoreApplication::translate("MainWindow", "Otev\305\231\303\255t", nullptr));
        actionD_lka->setText(QCoreApplication::translate("MainWindow", "D\303\251lka:", nullptr));
        actionD_lka_2->setText(QCoreApplication::translate("MainWindow", "D\303\251lka:", nullptr));
        actionD_lka_3->setText(QCoreApplication::translate("MainWindow", "D\303\251lka:", nullptr));
        actionD_lka_4->setText(QCoreApplication::translate("MainWindow", "D\303\251lka:", nullptr));
        actionD_lka_5->setText(QCoreApplication::translate("MainWindow", "D\303\251lka:", nullptr));
        actionOtev_t_soubor->setText(QCoreApplication::translate("MainWindow", "Otev\305\231\303\255t soubor", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Informace o stahov\303\241n\303\255", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "25.6 / 120.7", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Zadejte URL videa", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "N\303\241zev videa:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "D\303\251lka videa:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "<Vyberte form\303\241t>", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "mp3 (pouze zvuk)", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "mp4 (video)", nullptr));

        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "<Vyberte kvalitu>", nullptr));

        pushButton->setText(QCoreApplication::translate("MainWindow", "Naj\303\255t", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Zru\305\241it", nullptr));
        menuInfo->setTitle(QCoreApplication::translate("MainWindow", "Info", nullptr));
        menuHistorie->setTitle(QCoreApplication::translate("MainWindow", "Historie", nullptr));
        menu1->setTitle(QCoreApplication::translate("MainWindow", "1.", nullptr));
        menu2->setTitle(QCoreApplication::translate("MainWindow", "2.", nullptr));
        menu3->setTitle(QCoreApplication::translate("MainWindow", "3.", nullptr));
        menu4->setTitle(QCoreApplication::translate("MainWindow", "4.", nullptr));
        menu5->setTitle(QCoreApplication::translate("MainWindow", "5.", nullptr));
        menuUpravit_video->setTitle(QCoreApplication::translate("MainWindow", "\303\232prava videa", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
