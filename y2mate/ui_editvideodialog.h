/********************************************************************************
** Form generated from reading UI file 'editvideodialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITVIDEODIALOG_H
#define UI_EDITVIDEODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_editVideoDialog
{
public:
    QProgressBar *progressBar;

    void setupUi(QDialog *editVideoDialog)
    {
        if (editVideoDialog->objectName().isEmpty())
            editVideoDialog->setObjectName("editVideoDialog");
        editVideoDialog->resize(285, 223);
        progressBar = new QProgressBar(editVideoDialog);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(30, 140, 211, 23));
        progressBar->setValue(24);

        retranslateUi(editVideoDialog);

        QMetaObject::connectSlotsByName(editVideoDialog);
    } // setupUi

    void retranslateUi(QDialog *editVideoDialog)
    {
        editVideoDialog->setWindowTitle(QCoreApplication::translate("editVideoDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class editVideoDialog: public Ui_editVideoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITVIDEODIALOG_H
