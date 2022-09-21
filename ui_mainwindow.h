/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
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
    QAction *actionHledat_n_zev_videa;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_3;
    QProgressBar *progressBar;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer_5;
    QComboBox *comboBox_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_6;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer_4;
    QMenuBar *menuBar;
    QMenu *menuInfo;
    QMenu *menuNastaven;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(495, 271);
        actiony2mate_com = new QAction(MainWindow);
        actiony2mate_com->setObjectName(QString::fromUtf8("actiony2mate_com"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/y2mate.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actiony2mate_com->setIcon(icon);
        actionzdrojovy_kod = new QAction(MainWindow);
        actionzdrojovy_kod->setObjectName(QString::fromUtf8("actionzdrojovy_kod"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/github.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionzdrojovy_kod->setIcon(icon1);
        actionHledat_n_zev_videa = new QAction(MainWindow);
        actionHledat_n_zev_videa->setObjectName(QString::fromUtf8("actionHledat_n_zev_videa"));
        actionHledat_n_zev_videa->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 49, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setClearButtonEnabled(true);

        verticalLayout->addWidget(lineEdit);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout_2->addWidget(comboBox);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_5);

        comboBox_2 = new QComboBox(centralwidget);
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        verticalLayout_2->addWidget(comboBox_2);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(pushButton);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_6);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_4->addWidget(pushButton_2);


        horizontalLayout->addLayout(verticalLayout_4);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 61, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        verticalLayout_3->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 495, 21));
        menuInfo = new QMenu(menuBar);
        menuInfo->setObjectName(QString::fromUtf8("menuInfo"));
        menuNastaven = new QMenu(menuBar);
        menuNastaven->setObjectName(QString::fromUtf8("menuNastaven"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuInfo->menuAction());
        menuBar->addAction(menuNastaven->menuAction());
        menuInfo->addAction(actiony2mate_com);
        menuInfo->addAction(actionzdrojovy_kod);
        menuNastaven->addAction(actionHledat_n_zev_videa);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actiony2mate_com->setText(QCoreApplication::translate("MainWindow", "y2mate.com", nullptr));
        actionzdrojovy_kod->setText(QCoreApplication::translate("MainWindow", "zdrojov\303\275 k\303\263d", nullptr));
        actionHledat_n_zev_videa->setText(QCoreApplication::translate("MainWindow", "Hledat n\303\241zev videa", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Informace o stahov\303\241n\303\255", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Zadejte URL videa", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "N\303\241zev: ", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "D\303\251lka videa:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "<Vyberte form\303\241t>", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "mp3 (zvuk)", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "mp4 (zvuk+video)", nullptr));

        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "<Vyberte kvalitu>", nullptr));

        pushButton->setText(QCoreApplication::translate("MainWindow", "Naj\303\255t", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Zru\305\241it", nullptr));
        menuInfo->setTitle(QCoreApplication::translate("MainWindow", "Info", nullptr));
        menuNastaven->setTitle(QCoreApplication::translate("MainWindow", "Nastaven\303\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
