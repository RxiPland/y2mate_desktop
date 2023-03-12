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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_downloadVideoWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_4;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer_2;
    QComboBox *comboBox_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menubar;

    void setupUi(QMainWindow *downloadVideoWindow)
    {
        if (downloadVideoWindow->objectName().isEmpty())
            downloadVideoWindow->setObjectName("downloadVideoWindow");
        downloadVideoWindow->resize(581, 208);
        centralwidget = new QWidget(downloadVideoWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_2 = new QSpacerItem(8, 8, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_4 = new QSpacerItem(20, 8, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setEnabled(false);
        lineEdit->setBaseSize(QSize(0, 0));

        verticalLayout->addWidget(lineEdit);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_3);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(comboBox);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        comboBox_2 = new QComboBox(centralwidget);
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");

        verticalLayout_2->addWidget(comboBox_2);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout_3->addWidget(pushButton_2);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_3);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMinimumSize(QSize(150, 0));

        verticalLayout_3->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_5 = new QSpacerItem(20, 8, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(8, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        downloadVideoWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(downloadVideoWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 581, 25));
        downloadVideoWindow->setMenuBar(menubar);

        retranslateUi(downloadVideoWindow);

        QMetaObject::connectSlotsByName(downloadVideoWindow);
    } // setupUi

    void retranslateUi(QMainWindow *downloadVideoWindow)
    {
        downloadVideoWindow->setWindowTitle(QCoreApplication::translate("downloadVideoWindow", "Sta\305\276en\303\255 videa", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("downloadVideoWindow", "URL videa", nullptr));
        label->setText(QCoreApplication::translate("downloadVideoWindow", "N\303\241zev:", nullptr));
        label_2->setText(QCoreApplication::translate("downloadVideoWindow", "D\303\251lka:", nullptr));
        label_3->setText(QCoreApplication::translate("downloadVideoWindow", "Kan\303\241l:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("downloadVideoWindow", "<Vyberte form\303\241t>", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("downloadVideoWindow", "mp3 (pouze zvuk)", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("downloadVideoWindow", "mp4 (video + zvuk)", nullptr));

        comboBox_2->setItemText(0, QCoreApplication::translate("downloadVideoWindow", "<Vyberte kvalitu>", nullptr));

        pushButton_2->setText(QCoreApplication::translate("downloadVideoWindow", "Zru\305\241it", nullptr));
        pushButton->setText(QCoreApplication::translate("downloadVideoWindow", "St\303\241hnout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class downloadVideoWindow: public Ui_downloadVideoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADVIDEOWINDOW_H
