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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_downloadDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QProgressBar *progressBar;

    void setupUi(QDialog *downloadDialog)
    {
        if (downloadDialog->objectName().isEmpty())
            downloadDialog->setObjectName("downloadDialog");
        downloadDialog->resize(257, 326);
        horizontalLayout = new QHBoxLayout(downloadDialog);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        progressBar = new QProgressBar(downloadDialog);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(downloadDialog);

        QMetaObject::connectSlotsByName(downloadDialog);
    } // setupUi

    void retranslateUi(QDialog *downloadDialog)
    {
        downloadDialog->setWindowTitle(QCoreApplication::translate("downloadDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class downloadDialog: public Ui_downloadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADDIALOG_H
