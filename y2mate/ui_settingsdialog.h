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
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settingsDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_2;
    QToolButton *toolButton;
    QCheckBox *checkBox_3;
    QSpacerItem *horizontalSpacer_10;
    QCheckBox *checkBox_5;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *verticalSpacer_15;
    QSpacerItem *verticalSpacer_14;
    QCheckBox *checkBox_2;
    QToolButton *toolButton_2;
    QCheckBox *checkBox_4;
    QToolButton *toolButton_3;
    QSpacerItem *horizontalSpacer_9;
    QCheckBox *checkBox;
    QToolButton *toolButton_4;
    QSpacerItem *verticalSpacer_11;
    QSpacerItem *verticalSpacer_12;
    QToolButton *toolButton_5;
    QSpacerItem *verticalSpacer_16;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer_14;
    QLabel *label_2;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_3;
    QCheckBox *checkBox_6;
    QSpacerItem *horizontalSpacer_17;
    QToolButton *toolButton_7;
    QCheckBox *checkBox_7;
    QToolButton *toolButton_6;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_13;
    QSpacerItem *verticalSpacer_4;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *settingsDialog)
    {
        if (settingsDialog->objectName().isEmpty())
            settingsDialog->setObjectName("settingsDialog");
        settingsDialog->resize(428, 384);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/settings.ico"), QSize(), QIcon::Normal, QIcon::Off);
        settingsDialog->setWindowIcon(icon);
        horizontalLayout = new QHBoxLayout(settingsDialog);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        tabWidget = new QTabWidget(settingsDialog);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        horizontalLayout_6 = new QHBoxLayout(tab);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        toolButton = new QToolButton(tab);
        toolButton->setObjectName("toolButton");
        toolButton->setMinimumSize(QSize(30, 25));
        QFont font;
        font.setBold(false);
        toolButton->setFont(font);
        toolButton->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(toolButton, 0, 2, 1, 1);

        checkBox_3 = new QCheckBox(tab);
        checkBox_3->setObjectName("checkBox_3");
        checkBox_3->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(checkBox_3, 4, 0, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_10, 2, 1, 1, 1);

        checkBox_5 = new QCheckBox(tab);
        checkBox_5->setObjectName("checkBox_5");
        checkBox_5->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(checkBox_5, 8, 0, 1, 1);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_13, 6, 1, 1, 1);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName("pushButton");
        pushButton->setEnabled(false);
        pushButton->setMinimumSize(QSize(0, 25));
        pushButton->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(pushButton, 4, 1, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_11, 0, 1, 1, 1);

        verticalSpacer_15 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_15, 7, 1, 1, 1);

        verticalSpacer_14 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_14, 1, 1, 1, 1);

        checkBox_2 = new QCheckBox(tab);
        checkBox_2->setObjectName("checkBox_2");
        checkBox_2->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(checkBox_2, 2, 0, 1, 1);

        toolButton_2 = new QToolButton(tab);
        toolButton_2->setObjectName("toolButton_2");
        toolButton_2->setMinimumSize(QSize(30, 25));
        toolButton_2->setFont(font);
        toolButton_2->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(toolButton_2, 2, 2, 1, 1);

        checkBox_4 = new QCheckBox(tab);
        checkBox_4->setObjectName("checkBox_4");
        checkBox_4->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(checkBox_4, 6, 0, 1, 1);

        toolButton_3 = new QToolButton(tab);
        toolButton_3->setObjectName("toolButton_3");
        toolButton_3->setMinimumSize(QSize(30, 25));
        toolButton_3->setFont(font);
        toolButton_3->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(toolButton_3, 4, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 8, 1, 1, 1);

        checkBox = new QCheckBox(tab);
        checkBox->setObjectName("checkBox");
        checkBox->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(checkBox, 0, 0, 1, 1);

        toolButton_4 = new QToolButton(tab);
        toolButton_4->setObjectName("toolButton_4");
        toolButton_4->setMinimumSize(QSize(30, 25));
        toolButton_4->setFont(font);
        toolButton_4->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(toolButton_4, 6, 2, 1, 1);

        verticalSpacer_11 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_11, 3, 1, 1, 1);

        verticalSpacer_12 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_12, 5, 1, 1, 1);

        toolButton_5 = new QToolButton(tab);
        toolButton_5->setObjectName("toolButton_5");
        toolButton_5->setMinimumSize(QSize(30, 25));
        toolButton_5->setFont(font);
        toolButton_5->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(toolButton_5, 8, 2, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);

        verticalSpacer_16 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_16);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(-1, 0, -1, -1);
        pushButton_5 = new QPushButton(tab);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMinimumSize(QSize(150, 25));
        pushButton_5->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_5->addWidget(pushButton_5);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_14);

        label_2 = new QLabel(tab);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(0, 25));

        horizontalLayout_5->addWidget(label_2);


        verticalLayout_3->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_3);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        horizontalLayout_7 = new QHBoxLayout(tab_2);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        checkBox_6 = new QCheckBox(tab_2);
        checkBox_6->setObjectName("checkBox_6");
        checkBox_6->setFocusPolicy(Qt::NoFocus);

        gridLayout_3->addWidget(checkBox_6, 0, 0, 1, 1);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_17, 0, 1, 1, 1);

        toolButton_7 = new QToolButton(tab_2);
        toolButton_7->setObjectName("toolButton_7");
        toolButton_7->setMinimumSize(QSize(30, 25));

        gridLayout_3->addWidget(toolButton_7, 3, 2, 1, 1);

        checkBox_7 = new QCheckBox(tab_2);
        checkBox_7->setObjectName("checkBox_7");

        gridLayout_3->addWidget(checkBox_7, 3, 0, 1, 1);

        toolButton_6 = new QToolButton(tab_2);
        toolButton_6->setObjectName("toolButton_6");
        toolButton_6->setMinimumSize(QSize(30, 25));
        toolButton_6->setFont(font);
        toolButton_6->setFocusPolicy(Qt::NoFocus);

        gridLayout_3->addWidget(toolButton_6, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 3, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer_5, 2, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout_3);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_13);


        horizontalLayout_7->addLayout(verticalLayout_4);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout->addItem(verticalSpacer_4);

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

        verticalSpacer_3 = new QSpacerItem(20, 8, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_2 = new QPushButton(settingsDialog);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_3->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(settingsDialog);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_3->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(settingsDialog);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_3->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 12, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(settingsDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(settingsDialog);
    } // setupUi

    void retranslateUi(QDialog *settingsDialog)
    {
        settingsDialog->setWindowTitle(QCoreApplication::translate("settingsDialog", "Nastaven\303\255", nullptr));
        toolButton->setText(QCoreApplication::translate("settingsDialog", "?", nullptr));
        checkBox_3->setText(QCoreApplication::translate("settingsDialog", "Defaultn\303\255 lokace pro stahov\303\241n\303\255", nullptr));
        checkBox_5->setText(QCoreApplication::translate("settingsDialog", "Automaticky kontrolovat aktualizace", nullptr));
        pushButton->setText(QCoreApplication::translate("settingsDialog", "Nastavit", nullptr));
        checkBox_2->setText(QCoreApplication::translate("settingsDialog", "Nahradit mezery podtr\305\276\303\255tkama", nullptr));
        toolButton_2->setText(QCoreApplication::translate("settingsDialog", "?", nullptr));
        checkBox_4->setText(QCoreApplication::translate("settingsDialog", "Zaznamen\303\241vat historii", nullptr));
        toolButton_3->setText(QCoreApplication::translate("settingsDialog", "?", nullptr));
        checkBox->setText(QCoreApplication::translate("settingsDialog", "Nahradit n\303\241zev n\303\241hodn\303\275mi znaky", nullptr));
        toolButton_4->setText(QCoreApplication::translate("settingsDialog", "?", nullptr));
        toolButton_5->setText(QCoreApplication::translate("settingsDialog", "?", nullptr));
        pushButton_5->setText(QCoreApplication::translate("settingsDialog", "Zkontrolovat aktualizace", nullptr));
        label_2->setText(QCoreApplication::translate("settingsDialog", "Verze", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("settingsDialog", "Z\303\241kladn\303\255", nullptr));
        checkBox_6->setText(QCoreApplication::translate("settingsDialog", "Tla\304\215\303\255tko pro zobrazen\303\255 odkazu", nullptr));
        toolButton_7->setText(QCoreApplication::translate("settingsDialog", "?", nullptr));
        checkBox_7->setText(QCoreApplication::translate("settingsDialog", "Povolit zvukovou notifikaci", nullptr));
        toolButton_6->setText(QCoreApplication::translate("settingsDialog", "?", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("settingsDialog", "Pokro\304\215il\303\251", nullptr));
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
