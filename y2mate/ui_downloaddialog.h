/********************************************************************************
** Form generated from reading UI file 'downloaddialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADDIALOG_H
#define UI_DOWNLOADDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_downloadDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QProgressBar *progressBar;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *downloadDialog)
    {
        if (downloadDialog->objectName().isEmpty())
            downloadDialog->setObjectName("downloadDialog");
        downloadDialog->resize(259, 255);
        horizontalLayout = new QHBoxLayout(downloadDialog);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_2 = new QLabel(downloadDialog);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        label = new QLabel(downloadDialog);
        label->setObjectName("label");
        label->setMinimumSize(QSize(0, 20));

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 8, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        progressBar = new QProgressBar(downloadDialog);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(0);

        verticalLayout->addWidget(progressBar);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer_3 = new QSpacerItem(25, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        pushButton_3 = new QPushButton(downloadDialog);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(160, 0));
        pushButton_3->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(pushButton_3, 2, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(25, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 2, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(25, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(25, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 2, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 3, 1, 1, 1);

        pushButton_2 = new QPushButton(downloadDialog);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setEnabled(false);
        pushButton_2->setMinimumSize(QSize(160, 0));
        pushButton_2->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(pushButton_2, 1, 1, 1, 1);

        pushButton_4 = new QPushButton(downloadDialog);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setEnabled(false);
        pushButton_4->setMinimumSize(QSize(160, 0));
        pushButton_4->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(pushButton_4, 0, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(25, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 0, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(25, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer = new QSpacerItem(25, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(downloadDialog);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(175, 27));
        pushButton->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(25, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(downloadDialog);

        QMetaObject::connectSlotsByName(downloadDialog);
    } // setupUi

    void retranslateUi(QDialog *downloadDialog)
    {
        downloadDialog->setWindowTitle(QCoreApplication::translate("downloadDialog", "Stahov\303\241n\303\255 - prob\303\255h\303\241", nullptr));
        label_2->setText(QCoreApplication::translate("downloadDialog", "N\303\241zev", nullptr));
        label->setText(QCoreApplication::translate("downloadDialog", "Sta\305\276eno", nullptr));
        pushButton_3->setText(QCoreApplication::translate("downloadDialog", "Otev\305\231\303\255t um\303\255st\304\233n\303\255", nullptr));
        pushButton_2->setText(QCoreApplication::translate("downloadDialog", "Otev\305\231\303\255t soubor", nullptr));
        pushButton_4->setText(QCoreApplication::translate("downloadDialog", "Upravit video", nullptr));
        pushButton->setText(QCoreApplication::translate("downloadDialog", "Zru\305\241it stahov\303\241n\303\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class downloadDialog: public Ui_downloadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADDIALOG_H
