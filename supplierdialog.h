#ifndef SUPPLIERDIALOG_H
#define SUPPLIERDIALOG_H

#include <QDialog>

namespace Ui {
class SupplierDialog;
}

class SupplierDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SupplierDialog(QWidget *parent = 0);
    ~SupplierDialog();

private:
    Ui::SupplierDialog *ui;
};

#endif // SUPPLIERDIALOG_H
