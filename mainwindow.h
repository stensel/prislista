#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "databasemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:
        void on_CreatePb_clicked();

        void on_ReadAgreementPb_clicked();

        void on_ReadPricelistPb_clicked();

private:
        Ui::MainWindow *ui;

        DatabaseManager *dbm;
};

#endif // MAINWINDOW_H
