#include "pricelistdialog.h"
#include "ui_pricelistdialog.h"

PricelistDialog::PricelistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PricelistDialog)
{
    ui->setupUi(this);
}

PricelistDialog::~PricelistDialog()
{
    delete ui;
}
