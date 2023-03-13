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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_settingsDialog
{
public:
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_3;
    QToolButton *toolButton;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *checkBox_2;
    QSpacerItem *horizontalSpacer_5;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_5;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_5;
    QPushButton *pushButton;
    QToolButton *toolButton_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_3;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_6;
    QLabel *label;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *settingsDialog)
    {
        if (settingsDialog->objectName().isEmpty())
            settingsDialog->setObjectName("settingsDialog");
        settingsDialog->resize(390, 271);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/settings.ico"), QSize(), QIcon::Normal, QIcon::Off);
        settingsDialog->setWindowIcon(icon);
        horizontalLayout_2 = new QHBoxLayout(settingsDialog);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_2 = new QSpacerItem(8, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 8, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_4, 5, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 3, 1, 1, 1);

        toolButton = new QToolButton(settingsDialog);
        toolButton->setObjectName("toolButton");
        toolButton->setMinimumSize(QSize(30, 25));
        QFont font;
        font.setBold(false);
        toolButton->setFont(font);
        toolButton->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(toolButton, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 1, 1, 1);

        checkBox_2 = new QCheckBox(settingsDialog);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(checkBox_2, 2, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 6, 1, 1, 1);

        toolButton_2 = new QToolButton(settingsDialog);
        toolButton_2->setObjectName("toolButton_2");
        toolButton_2->setMinimumSize(QSize(30, 25));
        toolButton_2->setFont(font);
        toolButton_2->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(toolButton_2, 2, 2, 1, 1);

        toolButton_3 = new QToolButton(settingsDialog);
        toolButton_3->setObjectName("toolButton_3");
        toolButton_3->setMinimumSize(QSize(30, 25));
        toolButton_3->setFont(font);
        toolButton_3->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(toolButton_3, 4, 2, 1, 1);

        toolButton_5 = new QToolButton(settingsDialog);
        toolButton_5->setObjectName("toolButton_5");
        toolButton_5->setMinimumSize(QSize(30, 25));
        toolButton_5->setFont(font);
        toolButton_5->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(toolButton_5, 8, 2, 1, 1);

        checkBox_4 = new QCheckBox(settingsDialog);
        checkBox_4->setObjectName("checkBox_4");
        checkBox_4->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(checkBox_4, 6, 0, 1, 1);

        checkBox = new QCheckBox(settingsDialog);
        checkBox->setObjectName("checkBox");
        checkBox->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 1, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_5, 7, 1, 1, 1);

        pushButton = new QPushButton(settingsDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setEnabled(false);
        pushButton->setMinimumSize(QSize(0, 25));
        pushButton->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(pushButton, 4, 1, 1, 1);

        toolButton_4 = new QToolButton(settingsDialog);
        toolButton_4->setObjectName("toolButton_4");
        toolButton_4->setMinimumSize(QSize(30, 25));
        toolButton_4->setFont(font);
        toolButton_4->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(toolButton_4, 6, 2, 1, 1);

        checkBox_5 = new QCheckBox(settingsDialog);
        checkBox_5->setObjectName("checkBox_5");
        checkBox_5->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(checkBox_5, 8, 0, 1, 1);

        checkBox_3 = new QCheckBox(settingsDialog);
        checkBox_3->setObjectName("checkBox_3");
        checkBox_3->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(checkBox_3, 4, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer_8 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_8);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        pushButton_5 = new QPushButton(settingsDialog);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMinimumSize(QSize(150, 25));
        pushButton_5->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_4->addWidget(pushButton_5);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        label_2 = new QLabel(settingsDialog);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(0, 25));

        horizontalLayout_4->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout->addItem(verticalSpacer_6);

        label = new QLabel(settingsDialog);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(9);
        label->setFont(font1);

        verticalLayout->addWidget(label);

        verticalSpacer_7 = new QSpacerItem(20, 8, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_2 = new QPushButton(settingsDialog);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(settingsDialog);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(settingsDialog);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(8, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        retranslateUi(settingsDialog);

        QMetaObject::connectSlotsByName(settingsDialog);
    } // setupUi

    void retranslateUi(QDialog *settingsDialog)
    {
        settingsDialog->setWindowTitle(QCoreApplication::translate("settingsDialog", "Nastaven\303\255", nullptr));
        toolButton->setText(QCoreApplication::translate("settingsDialog", "?", nullptr));
        checkBox_2->setText(QCoreApplication::translate("settingsDialog", "Nahradit mezery podtr\305\276\303\255tkama", nullptr));
        toolButton_2->setText(QCoreApplication::translate("settingsDialog", "?", nullptr));
        toolButton_3->setText(QCoreApplication::translate("settingsDialog", "?", nullptr));
        toolButton_5->setText(QCoreApplication::translate("settingsDialog", "?", nullptr));
        checkBox_4->setText(QCoreApplication::translate("settingsDialog", "Zaznamen\303\241vat historii", nullptr));
        checkBox->setText(QCoreApplication::translate("settingsDialog", "Nahradit n\303\241zev n\303\241hodn\303\275mi znaky", nullptr));
        pushButton->setText(QCoreApplication::translate("settingsDialog", "Nastavit", nullptr));
        toolButton_4->setText(QCoreApplication::translate("settingsDialog", "?", nullptr));
        checkBox_5->setText(QCoreApplication::translate("settingsDialog", "Automaticky kontrolovat aktualizace", nullptr));
        checkBox_3->setText(QCoreApplication::translate("settingsDialog", "Defaultn\303\255 lokace pro stahov\303\241n\303\255", nullptr));
        pushButton_5->setText(QCoreApplication::translate("settingsDialog", "Zkontrolovat aktualizace", nullptr));
        label_2->setText(QCoreApplication::translate("settingsDialog", "Verze", nullptr));
        label->setText(QCoreApplication::translate("settingsDialog", "Nastaven\303\255 nen\303\255 ulo\305\276eno", nullptr));
        pushButton_2->setText(QCoreApplication::translate("settingsDialog", "Defaultn\303\255", nullptr));
        pushButton_3->setText(QCoreApplication::translate("settingsDialog", "Zru\305\241it", nullptr));
        pushButton_4->setText(QCoreApplication::translate("settingsDialog", "Ulo\305\276it", nullptr));
    } // retranslateUi

};

namespace Ui {
    class settingsDialog: public Ui_settingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
