#include "databasemanager.h"
#include <QMessageBox>


DataObject::DataObject(QSqlDatabase *db ,QString name, QString pre)
{
    DbName = name;
    Prefix = pre;
    SqlDb = db;

}

bool DataObject::Create()
{
    QStringBuilder qtbl;
    bool ret = false;

    if (SqlDb.isOpen())
    {
        QSqlQuery query;

        qtbl = "CREATE TABLE IF NOT EXISTS tbl_" + DbName + "_Agreement ";
        qtbl += "(Id INTEGER PRIMARY KEY, ";
        qtbl += "Product TEXT, Item TEXT, Title TEXT, Discount DOUBLE, ItemDiscount DOUBLE)";

        ret = query.exec(qtbl);

        qtbl = "CREATE TABLE IF NOT EXISTS tbl_" + DbName + "_Pricelist ";
        qtbl += "(Id INTEGER PRIMARY KEY, ";
        qtbl += "Item TEXT, Title TEXT, Product TEXT, Unit TEXT, Listprice DOUBLE, Price1 DOUBLE, Price2 DOUBLE, Price3 DOUBLE, Price4 DOUBLE, Price5 DOUBLE, Price6 DOUBLE)";

        ret = query.exec(qtbl);
    }

    return ret;
}

DataObject::PutAgreementItem(Agreement *a)
{
    QStringBuilder qstr;

    if (SqlDb.isOpen())
    {
        QSqlQuery query;

        qstr = "INSERT INTO tbl_" + DbName + "_Agreement ";
        qstr += "(Product, Item, Title, Discount, ItemDiscount) VALUES (";
        qstr += "'" + a->Product + "', ";
        qstr += "'" + a->Item + "', ";
        qstr += "'" + a->Title + "', ";
        qstr += a->Discount + ", ";
        qstr += a->ItemDiscount + ")";

        ret = query.exec(qstr);

        qDebug() << qstr;
        qDebug() << query.lastError().text();
    }
}

DataObject::PutPricelistItem(Pricelist *p)
{
    QStringBuilder qstr;
    int i;

    if (SqlDb.isOpen())
    {
        QSqlQuery query;

        qstr = "INSERT INTO tbl_" + DbName + "_Pricelist ";
        qstr += "(Item, Title, Product, Unit, Listprice, Price1, Price2, Price3, Price4, Price5, Price6) VALUES (";
        qstr += "'" + p->Item + "', ";
        qstr += "'" + p->Title + "', ";
        qstr += "'" + p->Product + "', ";
        qstr += "'" + p->Unit + "', ";
        qstr += p->Listprice;

        for (i = 0; i <6; i++)
        {
            qstr += ", " + p->Price[i];
        }

        qstr += ")";

        ret = query.exec(qstr);

        qDebug() << qstr;
        qDebug() << query.lastError().text();
    }
}

DataObject::GetAgreementList(QLinkedList<Agreement> *list)
{
    bool ret = false;
    QSqlQuery query;
    QSqlRecord rec;
    Agreement a;

    list->clear();

    if (SqlDb.isOpen())
    {
        ret = query.exec(QString("SELECT * FROM tbl_%1_Agreement").arg(DbName));

        if(ret)
        {
            query.first();
            do
            {
                rec = query.record();
                a.Item = rec.value("Item").toString();
                a.Title = rec.value("Title").toString();
                a.Product = rec.value("Product").toString();
                a.Discount = rec.value("Discount").toDouble();
                a.ItemDiscount = rec.value("ItemDiscount").toDouble();
                list->append(a);
            }
            while(query.next());
        }
    }
    return ret;
}

DataObject::GetAgreementItem(Agreement *a, QString product)
{
    bool ret = false;
    QSqlQuery query;
    QSqlRecord rec;
    Agreement a;

    list->clear();

    if (SqlDb.isOpen())
    {
        ret = query.exec(QString("SELECT * FROM tbl_%1_Agreement WHERE Product='%2'").arg(DbName, product));
        query.first();
        rec = query.record();
        a.Item = rec.value("Item").toString();
        a.Title = rec.value("Title").toString();
        a.Product = rec.value("Product").toString();
        a.Discount = rec.value("Discount").toDouble();
        a.ItemDiscount = rec.value("ItemDiscount").toDouble();
    }
}

DatabaseManager::DatabaseManager()
{
    SqlDb = QSqlDatabase::addDatabase("QMYSQL");
    SqlDb.setHostName("localhost");
    SqlDb.setDatabaseName("Prices");
    SqlDb.setUserName("Prices");
    SqlDb.setPassword("exit");

    if(!SqlDb.open())
    {
        qDebug() << SqlDb.lastError();
        qFatal( "Failed to connect." );
    }
}

DatabaseManager::~DatabaseManager()
{
    db.close();
}

QSqlError DatabaseManager::lastError()
{
    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
}

QSqlDatabase *DatabaseManager::GetDb()
{
    return *db;
}
