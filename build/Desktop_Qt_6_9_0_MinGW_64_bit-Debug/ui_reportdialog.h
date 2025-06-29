/********************************************************************************
** Form generated from reading UI file 'reportdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPORTDIALOG_H
#define UI_REPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ReportDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *reportTextEdit;

    void setupUi(QDialog *ReportDialog)
    {
        if (ReportDialog->objectName().isEmpty())
            ReportDialog->setObjectName("ReportDialog");
        ReportDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(ReportDialog);
        verticalLayout->setObjectName("verticalLayout");
        reportTextEdit = new QTextEdit(ReportDialog);
        reportTextEdit->setObjectName("reportTextEdit");
        reportTextEdit->setReadOnly(true);

        verticalLayout->addWidget(reportTextEdit);


        retranslateUi(ReportDialog);

        QMetaObject::connectSlotsByName(ReportDialog);
    } // setupUi

    void retranslateUi(QDialog *ReportDialog)
    {
        ReportDialog->setWindowTitle(QCoreApplication::translate("ReportDialog", "\350\241\214\347\250\213\346\212\245\345\221\212", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReportDialog: public Ui_ReportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPORTDIALOG_H
