#ifndef AGREEMENTDIALOG_H
#define AGREEMENTDIALOG_H

#include <QDialog>

namespace Ui {
class AgreementDialog;
}

class AgreementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AgreementDialog(QWidget *parent = 0);
    ~AgreementDialog();

private:
    Ui::AgreementDialog *ui;
};

#endif // AGREEMENTDIALOG_H
