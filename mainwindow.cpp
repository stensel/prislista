#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dbm = new DatabaseManager();

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
