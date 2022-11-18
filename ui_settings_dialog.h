/********************************************************************************
** Form generated from reading UI file 'settings_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_DIALOG_H
#define UI_SETTINGS_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_settings_dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QCheckBox *checkBox_5;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_8;
    QCheckBox *checkBox_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QPushButton *pushButton_9;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_10;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_6;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_7;
    QPushButton *pushButton_4;

    void setupUi(QDialog *settings_dialog)
    {
        if (settings_dialog->objectName().isEmpty())
            settings_dialog->setObjectName(QString::fromUtf8("settings_dialog"));
        settings_dialog->resize(486, 330);
        verticalLayout_2 = new QVBoxLayout(settings_dialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkBox_5 = new QCheckBox(settings_dialog);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));

        gridLayout->addWidget(checkBox_5, 3, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 2, 1, 1, 1);

        pushButton_8 = new QPushButton(settings_dialog);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_8, 2, 2, 1, 1);

        checkBox_2 = new QCheckBox(settings_dialog);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(checkBox_2->sizePolicy().hasHeightForWidth());
        checkBox_2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(checkBox_2, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        pushButton = new QPushButton(settings_dialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);

        pushButton_9 = new QPushButton(settings_dialog);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));

        gridLayout->addWidget(pushButton_9, 3, 2, 1, 1);

        pushButton_3 = new QPushButton(settings_dialog);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_3, 4, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 1);

        checkBox = new QCheckBox(settings_dialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        sizePolicy1.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        checkBox_4 = new QCheckBox(settings_dialog);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        sizePolicy1.setHeightForWidth(checkBox_4->sizePolicy().hasHeightForWidth());
        checkBox_4->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(checkBox_4, 2, 0, 1, 1);

        checkBox_3 = new QCheckBox(settings_dialog);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        sizePolicy1.setHeightForWidth(checkBox_3->sizePolicy().hasHeightForWidth());
        checkBox_3->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(checkBox_3, 4, 0, 1, 1);

        pushButton_2 = new QPushButton(settings_dialog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_2, 1, 2, 1, 1);

        pushButton_10 = new QPushButton(settings_dialog);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));

        gridLayout->addWidget(pushButton_10, 3, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(settings_dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        pushButton_11 = new QPushButton(settings_dialog);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));

        horizontalLayout_5->addWidget(pushButton_11);

        pushButton_12 = new QPushButton(settings_dialog);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        sizePolicy.setHeightForWidth(pushButton_12->sizePolicy().hasHeightForWidth());
        pushButton_12->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(pushButton_12);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_6 = new QPushButton(settings_dialog);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy2);
        pushButton_6->setMinimumSize(QSize(0, 0));

        horizontalLayout_3->addWidget(pushButton_6);

        horizontalSpacer_5 = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        label = new QLabel(settings_dialog);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(label);

        horizontalSpacer_4 = new QSpacerItem(85, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        label_2 = new QLabel(settings_dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_5 = new QPushButton(settings_dialog);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        horizontalLayout_2->addWidget(pushButton_5);

        pushButton_7 = new QPushButton(settings_dialog);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        horizontalLayout_2->addWidget(pushButton_7);

        pushButton_4 = new QPushButton(settings_dialog);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        horizontalLayout_2->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(settings_dialog);

        QMetaObject::connectSlotsByName(settings_dialog);
    } // setupUi

    void retranslateUi(QDialog *settings_dialog)
    {
        settings_dialog->setWindowTitle(QCoreApplication::translate("settings_dialog", "Dialog", nullptr));
        checkBox_5->setText(QCoreApplication::translate("settings_dialog", "Posledn\303\255 lokace", nullptr));
        pushButton_8->setText(QCoreApplication::translate("settings_dialog", "?", nullptr));
        checkBox_2->setText(QCoreApplication::translate("settings_dialog", "Nahradit mezery podtr\305\276\303\255tkama", nullptr));
        pushButton->setText(QCoreApplication::translate("settings_dialog", "?", nullptr));
        pushButton_9->setText(QCoreApplication::translate("settings_dialog", "?", nullptr));
        pushButton_3->setText(QCoreApplication::translate("settings_dialog", "?", nullptr));
        checkBox->setText(QCoreApplication::translate("settings_dialog", "Nahradit n\303\241zev videa n\303\241hodn\303\275mi znaky", nullptr));
        checkBox_4->setText(QCoreApplication::translate("settings_dialog", "Zaznamen\303\241vat historii", nullptr));
        checkBox_3->setText(QCoreApplication::translate("settings_dialog", "Automaticky kontrolovat novou verzi", nullptr));
        pushButton_2->setText(QCoreApplication::translate("settings_dialog", "?", nullptr));
        pushButton_10->setText(QCoreApplication::translate("settings_dialog", "Nastavit", nullptr));
        label_3->setText(QCoreApplication::translate("settings_dialog", "FFmpeg nen\303\255 sta\305\276en\303\275", nullptr));
        pushButton_11->setText(QCoreApplication::translate("settings_dialog", "Odstranit FFmpeg.exe", nullptr));
        pushButton_12->setText(QCoreApplication::translate("settings_dialog", "?", nullptr));
        pushButton_6->setText(QCoreApplication::translate("settings_dialog", "Zkontrolovat aktualizace", nullptr));
        label->setText(QCoreApplication::translate("settings_dialog", "verze:", nullptr));
        label_2->setText(QString());
        pushButton_5->setText(QCoreApplication::translate("settings_dialog", "Defaultn\303\255", nullptr));
        pushButton_7->setText(QCoreApplication::translate("settings_dialog", "Zru\305\241it", nullptr));
        pushButton_4->setText(QCoreApplication::translate("settings_dialog", "Ulo\305\276it", nullptr));
    } // retranslateUi

};

namespace Ui {
    class settings_dialog: public Ui_settings_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_DIALOG_H
