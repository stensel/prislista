#include "agreementdialog.h"
#include "ui_agreementdialog.h"

AgreementDialog::AgreementDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgreementDialog)
{
    ui->setupUi(this);
}

AgreementDialog::~AgreementDialog()
{
    delete ui;
}
