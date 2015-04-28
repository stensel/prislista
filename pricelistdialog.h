#ifndef PRICELISTDIALOG_H
#define PRICELISTDIALOG_H

#include <QDialog>

namespace Ui {
class PricelistDialog;
}

class PricelistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PricelistDialog(QWidget *parent = 0);
    ~PricelistDialog();

private:
    Ui::PricelistDialog *ui;
};

#endif // PRICELISTDIALOG_H
