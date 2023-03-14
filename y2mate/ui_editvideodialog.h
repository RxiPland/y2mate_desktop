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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_editVideoDialog
{
public:
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QTimeEdit *timeEdit;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QTimeEdit *timeEdit_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_6;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_5;
    QProgressBar *progressBar;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *editVideoDialog)
    {
        if (editVideoDialog->objectName().isEmpty())
            editVideoDialog->setObjectName("editVideoDialog");
        editVideoDialog->resize(435, 283);
        horizontalLayout_3 = new QHBoxLayout(editVideoDialog);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(editVideoDialog);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lineEdit = new QLineEdit(editVideoDialog);
        lineEdit->setObjectName("lineEdit");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setFocusPolicy(Qt::WheelFocus);

        horizontalLayout->addWidget(lineEdit);

        comboBox = new QComboBox(editVideoDialog);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        comboBox->setMinimumSize(QSize(0, 0));
        comboBox->setFocusPolicy(Qt::NoFocus);
        comboBox->setMaxCount(20);

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(editVideoDialog);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(0, 0));

        verticalLayout_3->addWidget(label_2);

        timeEdit = new QTimeEdit(editVideoDialog);
        timeEdit->setObjectName("timeEdit");
        timeEdit->setFocusPolicy(Qt::WheelFocus);

        verticalLayout_3->addWidget(timeEdit);

        verticalSpacer_2 = new QSpacerItem(20, 8, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_3 = new QLabel(editVideoDialog);
        label_3->setObjectName("label_3");

        verticalLayout_4->addWidget(label_3);

        timeEdit_2 = new QTimeEdit(editVideoDialog);
        timeEdit_2->setObjectName("timeEdit_2");
        timeEdit_2->setFocusPolicy(Qt::WheelFocus);

        verticalLayout_4->addWidget(timeEdit_2);


        verticalLayout_3->addLayout(verticalLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        verticalLayout_2->addLayout(verticalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalSpacer_6 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_6);

        pushButton = new QPushButton(editVideoDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setFocusPolicy(Qt::NoFocus);

        verticalLayout_5->addWidget(pushButton);

        pushButton_2 = new QPushButton(editVideoDialog);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setFocusPolicy(Qt::NoFocus);

        verticalLayout_5->addWidget(pushButton_2);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_4);

        pushButton_3 = new QPushButton(editVideoDialog);
        pushButton_3->setObjectName("pushButton_3");
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy2);
        pushButton_3->setMinimumSize(QSize(0, 24));
        pushButton_3->setFocusPolicy(Qt::NoFocus);

        verticalLayout_5->addWidget(pushButton_3);

        verticalSpacer_7 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_7);


        horizontalLayout_2->addLayout(verticalLayout_5);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_5 = new QSpacerItem(20, 8, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout->addItem(verticalSpacer_5);

        progressBar = new QProgressBar(editVideoDialog);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(0);

        verticalLayout->addWidget(progressBar);

        verticalSpacer_8 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_8);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        retranslateUi(editVideoDialog);

        QMetaObject::connectSlotsByName(editVideoDialog);
    } // setupUi

    void retranslateUi(QDialog *editVideoDialog)
    {
        editVideoDialog->setWindowTitle(QCoreApplication::translate("editVideoDialog", "\303\232prava videa", nullptr));
        label->setText(QCoreApplication::translate("editVideoDialog", "N\303\241zev:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("editVideoDialog", ".mp3", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("editVideoDialog", ".mp4", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("editVideoDialog", ".wav", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("editVideoDialog", ".ogg", nullptr));

        label_2->setText(QCoreApplication::translate("editVideoDialog", "Za\304\215\303\241tek:", nullptr));
        timeEdit->setDisplayFormat(QCoreApplication::translate("editVideoDialog", "HH:mm:ss", nullptr));
        label_3->setText(QCoreApplication::translate("editVideoDialog", "Konec:", nullptr));
        timeEdit_2->setDisplayFormat(QCoreApplication::translate("editVideoDialog", "HH:mm:ss", nullptr));
        pushButton->setText(QCoreApplication::translate("editVideoDialog", "Reset hodnot", nullptr));
        pushButton_2->setText(QCoreApplication::translate("editVideoDialog", "Odej\303\255t", nullptr));
        pushButton_3->setText(QCoreApplication::translate("editVideoDialog", "Potvrdit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class editVideoDialog: public Ui_editVideoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITVIDEODIALOG_H
