#include "reportdialog.h"
#include "ui_reportdialog.h"

ReportDialog::ReportDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::ReportDialog) {
    ui->setupUi(this);
}

ReportDialog::~ReportDialog() {
    delete ui;
}

void ReportDialog::setReportText(const QString &text) {
    ui->reportTextEdit->setPlainText(text);
}