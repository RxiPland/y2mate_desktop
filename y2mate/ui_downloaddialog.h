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
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QProgressBar *progressBar;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *downloadDialog)
    {
        if (downloadDialog->objectName().isEmpty())
            downloadDialog->setObjectName("downloadDialog");
        downloadDialog->resize(257, 145);
        horizontalLayout = new QHBoxLayout(downloadDialog);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
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

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(downloadDialog);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(0, 27));
        pushButton->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(downloadDialog);

        QMetaObject::connectSlotsByName(downloadDialog);
    } // setupUi

    void retranslateUi(QDialog *downloadDialog)
    {
        downloadDialog->setWindowTitle(QCoreApplication::translate("downloadDialog", "Stahov\303\241n\303\255", nullptr));
        label->setText(QCoreApplication::translate("downloadDialog", "Sta\305\276eno", nullptr));
        pushButton->setText(QCoreApplication::translate("downloadDialog", "Zru\305\241it stahov\303\241n\303\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class downloadDialog: public Ui_downloadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADDIALOG_H
