#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dbm = new DatabaseManager();
    sd = new SupplierData(dbm->GetDb());
    sd->GetSupplierList(&supList);

    // Create model
    model = new QStringListModel(this);

    // Make data
    QStringList List;
    List << "Clair de Lune" << "Reverie" << "Prelude";

    foreach (SupplierData::Supplier s, supList)
    {
        List << s.Name;
    }

    // Populate our model
    model->setStringList(List);

    // Glue model and view together
    ui->SuppliersLv->setModel(model);
}

MainWindow::~MainWindow()
{
    delete dbm;
    delete ui;
}

void MainWindow::on_CreatePb_clicked()
{

}

void MainWindow::on_ReadAgreementPb_clicked()
{

}

void MainWindow::on_ReadPricelistPb_clicked()
{

}
