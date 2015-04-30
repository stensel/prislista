#ifndef SUPPLIERDIALOG_H
#define SUPPLIERDIALOG_H

#include <QDialog>
#include "databasemanager.h"

namespace Ui {
class SupplierDialog;
}

class SupplierDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SupplierDialog(QWidget *parent = 0);
    ~SupplierDialog();

    void GetData(SupplierData::Supplier *sup);
    void SetData(SupplierData::Supplier *sup);

private slots:


    void on_AgreementFixed_clicked();

private:
    Ui::SupplierDialog *ui;
};

#endif // SUPPLIERDIALOG_H
