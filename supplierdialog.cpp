#include "supplierdialog.h"
#include "ui_supplierdialog.h"

SupplierDialog::SupplierDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SupplierDialog)
{
    ui->setupUi(this);
}

SupplierDialog::~SupplierDialog()
{
    delete ui;
}

void SupplierDialog::on_AgreementFixed_clicked()
{
    if (ui->AgreementFixed->isChecked())
    {
        ui->A_C1L->setText("Start");
        ui->A_C2L->setText("Längd");
        ui->A_C2L->setVisible(true);
        ui->A_Product2->setVisible(true);
        ui->A_Item2->setVisible(true);
        ui->A_Title2->setVisible(true);
        ui->A_Discount2->setVisible(true);
        ui->A_ItemDiscount2->setVisible(true);

        ui->P_C1L->setText("Start");
        ui->P_C2L->setText("Längd");
        ui->P_Item2->setVisible(true);
        ui->P_Title2->setVisible(true);
        ui->P_Product2->setVisible(true);
        ui->P_Unit2->setVisible(true);
        ui->P_Listprice2->setVisible(true);
    }
    else
    {
        ui->A_C1L->setText("Fält");
        ui->A_C2L->setText("");
        ui->A_C2L->setVisible(false);
        ui->A_Product2->setVisible(false);
        ui->A_Item2->setVisible(false);
        ui->A_Title2->setVisible(false);
        ui->A_Discount2->setVisible(false);
        ui->A_ItemDiscount2->setVisible(false);

        ui->P_C1L->setText("Fält");
        ui->P_C2L->setText("");
        ui->P_Item2->setVisible(false);
        ui->P_Title2->setVisible(false);
        ui->P_Product2->setVisible(false);
        ui->P_Unit2->setVisible(false);
        ui->P_Listprice2->setVisible(false);
    }
}

void SupplierDialog::GetData(SupplierData::Supplier *sup)
{
    sup->FixedFile = ui->AgreementFixed->isChecked();
    sup->AgreementProduct[0] = ui->A_Product1->value();
    sup->AgreementItem[0] = ui->A_Item1->value();
    sup->AgreementTitle[0] = ui->A_Item1->value();
    sup->AgreementDiscount[0] = ui->A_Discount1->value();
    sup->AgreementItemDiscount[0] = ui->A_ItemDiscount1->value();

    if (ui->AgreementFixed->isChecked())
    {
        sup->AgreementProduct[1] = ui->A_Product2->value();
        sup->AgreementItem[1] = ui->A_Item2->value();
        sup->AgreementTitle[1] = ui->A_Item2->value();
        sup->AgreementDiscount[1] = ui->A_Discount2->value();
        sup->AgreementItemDiscount[1] = ui->A_ItemDiscount2->value();
    }
}

void SupplierDialog::SetData(SupplierData::Supplier *sup)
{
    ui->AgreementFixed->setChecked(sup->FixedFile);
    ui->A_Product1->setValue(sup->AgreementProduct[0]);
    ui->A_Item1->setValue(sup->AgreementItem[0]);
    ui->A_Title1->setValue(sup->AgreementTitle[0]);
    ui->A_Discount1->setValue(sup->AgreementDiscount[0]);
    ui->A_ItemDiscount1->setValue(sup->AgreementItemDiscount[0]);
    ui->A_Product2->setValue(sup->AgreementProduct[1]);
    ui->A_Item2->setValue(sup->AgreementItem[1]);
    ui->A_Title2->setValue(sup->AgreementTitle[1]);
    ui->A_Discount2->setValue(sup->AgreementDiscount[1]);
    ui->A_ItemDiscount2->setValue(sup->AgreementItemDiscount[1]);

    on_AgreementFixed_clicked();
}
