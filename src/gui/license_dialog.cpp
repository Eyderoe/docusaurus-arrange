#include "license_dialog.hpp"
#include "ui_license_dialog.h"


license_dialog::license_dialog (QWidget *parent) :
    QDialog(parent), ui(new Ui::license_dialog) {
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

license_dialog::~license_dialog () {
    delete ui;
}
