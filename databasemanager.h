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
