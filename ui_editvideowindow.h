/********************************************************************************
** Form generated from reading UI file 'editvideowindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITVIDEOWINDOW_H
#define UI_EDITVIDEOWINDOW_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditVideoWindow
{
public:
    QAction *actionVymazat_p_vodn_soubor;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_5;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTimeEdit *timeEdit;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QTimeEdit *timeEdit_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButton_3;
    QMenuBar *menubar;
    QMenu *menuMo_nosti;

    void setupUi(QMainWindow *EditVideoWindow)
    {
        if (EditVideoWindow->objectName().isEmpty())
            EditVideoWindow->setObjectName("EditVideoWindow");
        EditVideoWindow->resize(435, 234);
        actionVymazat_p_vodn_soubor = new QAction(EditVideoWindow);
        actionVymazat_p_vodn_soubor->setObjectName("actionVymazat_p_vodn_soubor");
        actionVymazat_p_vodn_soubor->setCheckable(true);
        centralwidget = new QWidget(EditVideoWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_6 = new QVBoxLayout(centralwidget);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        verticalLayout_3->addWidget(label_3);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMaxLength(150);
        lineEdit->setReadOnly(false);
        lineEdit->setClearButtonEnabled(false);

        verticalLayout_3->addWidget(lineEdit);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalSpacer_5 = new QSpacerItem(20, 22, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_5);

        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        verticalLayout_5->addWidget(comboBox);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);


        horizontalLayout_3->addLayout(verticalLayout_5);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        timeEdit = new QTimeEdit(centralwidget);
        timeEdit->setObjectName("timeEdit");
        timeEdit->setCurrentSection(QDateTimeEdit::SecondSection);
        timeEdit->setCurrentSectionIndex(2);
        timeEdit->setTime(QTime(0, 0, 0));

        verticalLayout_2->addWidget(timeEdit);

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        timeEdit_2 = new QTimeEdit(centralwidget);
        timeEdit_2->setObjectName("timeEdit_2");
        timeEdit_2->setCurrentSection(QDateTimeEdit::SecondSection);
        timeEdit_2->setCurrentSectionIndex(2);
        timeEdit_2->setTime(QTime(0, 0, 0));

        verticalLayout_2->addWidget(timeEdit_2);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout->addWidget(pushButton_3);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_4->addLayout(horizontalLayout);


        verticalLayout_6->addLayout(verticalLayout_4);

        EditVideoWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(EditVideoWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 435, 21));
        menuMo_nosti = new QMenu(menubar);
        menuMo_nosti->setObjectName("menuMo_nosti");
        EditVideoWindow->setMenuBar(menubar);

        menubar->addAction(menuMo_nosti->menuAction());
        menuMo_nosti->addAction(actionVymazat_p_vodn_soubor);

        retranslateUi(EditVideoWindow);

        QMetaObject::connectSlotsByName(EditVideoWindow);
    } // setupUi

    void retranslateUi(QMainWindow *EditVideoWindow)
    {
        EditVideoWindow->setWindowTitle(QCoreApplication::translate("EditVideoWindow", "\303\232prava videa", nullptr));
        actionVymazat_p_vodn_soubor->setText(QCoreApplication::translate("EditVideoWindow", "Vymazat p\305\257vodn\303\255 soubor", nullptr));
        label_3->setText(QCoreApplication::translate("EditVideoWindow", "N\303\241zev:", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("EditVideoWindow", "N\303\241zev videa", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("EditVideoWindow", ".mp4", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("EditVideoWindow", ".mp3", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("EditVideoWindow", ".wav", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("EditVideoWindow", ".ogg", nullptr));

        label->setText(QCoreApplication::translate("EditVideoWindow", "Za\304\215\303\241tek:", nullptr));
        timeEdit->setDisplayFormat(QCoreApplication::translate("EditVideoWindow", "HH:mm:ss", nullptr));
        label_2->setText(QCoreApplication::translate("EditVideoWindow", "Konec:", nullptr));
        timeEdit_2->setDisplayFormat(QCoreApplication::translate("EditVideoWindow", "HH:mm:ss", nullptr));
        pushButton_2->setText(QCoreApplication::translate("EditVideoWindow", "Reset hodnot", nullptr));
        pushButton->setText(QCoreApplication::translate("EditVideoWindow", "Odej\303\255t", nullptr));
        pushButton_3->setText(QCoreApplication::translate("EditVideoWindow", "Potvrdit", nullptr));
        menuMo_nosti->setTitle(QCoreApplication::translate("EditVideoWindow", "Mo\305\276nosti", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditVideoWindow: public Ui_EditVideoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITVIDEOWINDOW_H
