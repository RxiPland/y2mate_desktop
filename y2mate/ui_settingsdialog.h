/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_settingsDialog
{
public:

    void setupUi(QDialog *settingsDialog)
    {
        if (settingsDialog->objectName().isEmpty())
            settingsDialog->setObjectName("settingsDialog");
        settingsDialog->resize(410, 283);

        retranslateUi(settingsDialog);

        QMetaObject::connectSlotsByName(settingsDialog);
    } // setupUi

    void retranslateUi(QDialog *settingsDialog)
    {
        settingsDialog->setWindowTitle(QCoreApplication::translate("settingsDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class settingsDialog: public Ui_settingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
