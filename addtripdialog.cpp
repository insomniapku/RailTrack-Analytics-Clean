#include "addtripdialog.h"
#include "ui_addtripdialog.h"

AddTripDialog::AddTripDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::AddTripDialog) {
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    // 初始化下拉框
    ui->fromComboBox->addItems(cities);
    ui->toComboBox->addItems(cities);
}

AddTripDialog::~AddTripDialog() {
    delete ui;
}

QString AddTripDialog::getFromCity() const {
    return ui->fromComboBox->currentText();
}

QString AddTripDialog::getToCity() const {
    return ui->toComboBox->currentText();
}
