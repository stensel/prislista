#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QtSql>
#include <QFile>
#include <QLinkedList>

class DatabaseManager;

class DataObject : public QObject
{
    Q_OBJECT
    public:
        struct Agreement
        {
            QString Product;
            QString Item;
            QString Title;
            double Discount;
            double ItemDiscount;
        };

        struct Pricelist
        {
            QString Item;
            QString Title;
            QString Product;
            QString Unit;
            double Listprice;
            double Price[6];
        };

        DataObject(QString name, QString pre);
        bool PutAgreementItem(Agreement *a);
        bool PutPricelistItem(Pricelist *p);
        bool CreateTables();
        void GetAgreementList(QLinkedList<Agreement> *list);
        void GetAgreementItem(Agreement *a, QString product);

    private:
        QString DbName;
        QString Prefix;
        QSqlDatabase *SqlDb;

};

class SupplierData : public QObject
{
    Q_OBJECT
    public:
        struct Supplier
        {
            QString Name;
            QString Prefix;
            QString TableName;
            bool FixedFile;
            int AgreementProduct[2];
            int AgreementItem[2];
            int AgreementTitle[2];
            int AgreementDiscount[2];
            int AgreementItemDiscount[2];

            int PricelistItem[2];
            int PricelistTitle[2];
            int PricelistProduct[2];
            int PricelistUnit[2];
            int PricelistListprice[2];
            int PricelistPrice[2];
        };

        SupplierData();
    private:
        Supplier Data;
        QSqlDatabase *SqlDb;
};

class DatabaseManager : public QObject
{
    Q_OBJECT
    public:
        DatabaseManager();
        ~DatabaseManager();

        QSqlError lastError();
        QSqlDatabase *GetDb();
    private:
        QSqlDatabase db;
        bool dbOk;
};

#endif // DATABASEMANAGER_H
