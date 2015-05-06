#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"
#include "supplierdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dbm = new DatabaseManager();
    dbm->OpenDBSQLite("Pricelist", "Pricelist", "exit");

    sd = new SupplierData(dbm->GetDb());
    sd->CreateTables();
    sd->GetSupplierList(&supList);

    // Create model
    model = new QStringListModel(this);

    ReadDB();

    // Glue model and view together
    ui->SuppliersLv->setModel(model);
}

void MainWindow::ReadDB(void)
{
    QStringList List;

    sd->GetSupplierList(&supList);

    foreach (SupplierData::Supplier sup, supList)
    {
        List << sup.Name;
    }

    // Populate our model
    model->setStringList(List);
}

MainWindow::~MainWindow()
{
    delete dbm;
    delete ui;
}

void MainWindow::on_CreatePb_clicked()
{
    SupplierDialog *sdi;
    SupplierData::Supplier sup;
    sdi = new SupplierDialog(this);
    sdi->setModal(true);
    sdi->show();
    sdi->GetData(&sup);

    sd->PutSupplierItem(&sup);
}

void MainWindow::on_ReadAgreementPb_clicked()
{

}

void MainWindow::on_ReadPricelistPb_clicked()
{

}
