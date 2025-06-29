/********************************************************************************
** Form generated from reading UI file 'addtripdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTRIPDIALOG_H
#define UI_ADDTRIPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddTripDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *labelFrom;
    QLabel *labelTo;
    QComboBox *fromComboBox;
    QComboBox *toComboBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddTripDialog)
    {
        if (AddTripDialog->objectName().isEmpty())
            AddTripDialog->setObjectName("AddTripDialog");
        AddTripDialog->resize(300, 150);
        verticalLayout = new QVBoxLayout(AddTripDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        labelFrom = new QLabel(AddTripDialog);
        labelFrom->setObjectName("labelFrom");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelFrom);

        labelTo = new QLabel(AddTripDialog);
        labelTo->setObjectName("labelTo");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelTo);

        fromComboBox = new QComboBox(AddTripDialog);
        fromComboBox->setObjectName("fromComboBox");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, fromComboBox);

        toComboBox = new QComboBox(AddTripDialog);
        toComboBox->setObjectName("toComboBox");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, toComboBox);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(AddTripDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(AddTripDialog);

        QMetaObject::connectSlotsByName(AddTripDialog);
    } // setupUi

    void retranslateUi(QDialog *AddTripDialog)
    {
        AddTripDialog->setWindowTitle(QCoreApplication::translate("AddTripDialog", "\346\267\273\345\212\240\350\241\214\347\250\213", nullptr));
        labelFrom->setText(QCoreApplication::translate("AddTripDialog", "\345\247\213\345\217\221\345\234\260", nullptr));
        labelTo->setText(QCoreApplication::translate("AddTripDialog", "\347\233\256\347\232\204\345\234\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddTripDialog: public Ui_AddTripDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTRIPDIALOG_H
