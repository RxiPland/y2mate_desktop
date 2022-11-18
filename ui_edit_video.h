/********************************************************************************
** Form generated from reading UI file 'edit_video.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_VIDEO_H
#define UI_EDIT_VIDEO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_edit_video
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QSpacerItem *verticalSpacer_2;
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

    void setupUi(QDialog *edit_video)
    {
        if (edit_video->objectName().isEmpty())
            edit_video->setObjectName(QString::fromUtf8("edit_video"));
        edit_video->resize(431, 205);
        verticalLayout_5 = new QVBoxLayout(edit_video);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(edit_video);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        lineEdit = new QLineEdit(edit_video);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setReadOnly(false);
        lineEdit->setClearButtonEnabled(false);

        verticalLayout_3->addWidget(lineEdit);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(edit_video);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        timeEdit = new QTimeEdit(edit_video);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setCurrentSection(QDateTimeEdit::SecondSection);
        timeEdit->setCurrentSectionIndex(2);
        timeEdit->setTime(QTime(0, 0, 0));

        verticalLayout_2->addWidget(timeEdit);

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        label_2 = new QLabel(edit_video);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        timeEdit_2 = new QTimeEdit(edit_video);
        timeEdit_2->setObjectName(QString::fromUtf8("timeEdit_2"));
        timeEdit_2->setCurrentSection(QDateTimeEdit::SecondSection);
        timeEdit_2->setCurrentSectionIndex(2);
        timeEdit_2->setTime(QTime(0, 0, 0));

        verticalLayout_2->addWidget(timeEdit_2);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_2 = new QPushButton(edit_video);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(edit_video);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        pushButton_3 = new QPushButton(edit_video);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_4->addLayout(horizontalLayout);


        verticalLayout_5->addLayout(verticalLayout_4);


        retranslateUi(edit_video);

        QMetaObject::connectSlotsByName(edit_video);
    } // setupUi

    void retranslateUi(QDialog *edit_video)
    {
        edit_video->setWindowTitle(QCoreApplication::translate("edit_video", "y2mate - \303\272prava videa", nullptr));
        label_3->setText(QCoreApplication::translate("edit_video", "N\303\241zev:", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("edit_video", "N\303\241zev videa", nullptr));
        label->setText(QCoreApplication::translate("edit_video", "Za\304\215\303\241tek:", nullptr));
        timeEdit->setDisplayFormat(QCoreApplication::translate("edit_video", "HH:mm:ss", nullptr));
        label_2->setText(QCoreApplication::translate("edit_video", "Konec:", nullptr));
        timeEdit_2->setDisplayFormat(QCoreApplication::translate("edit_video", "HH:mm:ss", nullptr));
        pushButton_2->setText(QCoreApplication::translate("edit_video", "Reset hodnot", nullptr));
        pushButton->setText(QCoreApplication::translate("edit_video", "Zru\305\241it \303\272pravu", nullptr));
        pushButton_3->setText(QCoreApplication::translate("edit_video", "Potvrdit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class edit_video: public Ui_edit_video {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_VIDEO_H
