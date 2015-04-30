#include "databasemanager.h"
#include <QMessageBox>


DataObject::DataObject(QSqlDatabase *db, QString name, QString pre)
{
    DbName = name;
    Prefix = pre;
    SqlDb = db;

}

bool DataObject::CreateTables()
{
    QString qtbl;
    bool ret = false;

    if (SqlDb->isOpen())
    {
        QSqlQuery query;

        qtbl = "CREATE TABLE IF NOT EXISTS tbl_" + DbName + "_Agreement ";
        qtbl += "(Id INTEGER PRIMARY KEY, ";
        qtbl += "Product TEXT, Item TEXT, Title TEXT, Discount DOUBLE, ItemDiscount DOUBLE)";

        ret = query.exec(qtbl);
        qDebug() << qtbl;
        qDebug() << query.lastError().text();

        qtbl = "CREATE TABLE IF NOT EXISTS tbl_" + DbName + "_Pricelist ";
        qtbl += "(Id INTEGER PRIMARY KEY, ";
        qtbl += "Item TEXT, Title TEXT, Product TEXT, Unit TEXT, Listprice DOUBLE, Price1 DOUBLE, Price2 DOUBLE, Price3 DOUBLE, Price4 DOUBLE, Price5 DOUBLE, Price6 DOUBLE)";

        ret = query.exec(qtbl);
        qDebug() << qtbl;
        qDebug() << query.lastError().text();
    }

    return ret;
}

bool DataObject::PutAgreementItem(Agreement *a)
{
    bool ret = false;
    QString qstr;

    if (SqlDb->isOpen())
    {
        QSqlQuery query;

        qstr = "INSERT INTO tbl_" + DbName + "_Agreement ";
        qstr += "(Product, Item, Title, Discount, ItemDiscount) VALUES (";
        qstr += "'" + a->Product + "', ";
        qstr += "'" + a->Item + "', ";
        qstr += "'" + a->Title + "', ";
        qstr += QString::number(a->Discount) + ", ";
        qstr += QString::number(a->ItemDiscount) + ")";

        ret = query.exec(qstr);

        qDebug() << qstr;
        qDebug() << query.lastError().text();
    }
    return ret;
}

bool DataObject::PutPricelistItem(Pricelist *p)
{
    bool ret = false;
    QString qstr;
    int i;

    if (SqlDb->isOpen())
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
            qstr += ", " + QString::number(p->Price[i]);
        }

        qstr += ")";

        ret = query.exec(qstr);

        qDebug() << qstr;
        qDebug() << query.lastError().text();
    }

    return ret;
}

bool DataObject::GetAgreementList(QLinkedList<Agreement> *list)
{
    bool ret = false;
    QSqlQuery query;
    QSqlRecord rec;
    Agreement a;

    list->clear();

    if (SqlDb->isOpen())
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

bool DataObject::GetAgreementItem(Agreement *a, QString product)
{
    bool ret = false;
    QSqlQuery query;
    QSqlRecord rec;

    if (SqlDb->isOpen())
    {
        ret = query.exec(QString("SELECT * FROM tbl_%1_Agreement WHERE Product='%2'").arg(DbName, product));
        query.first();
        rec = query.record();
        a->Item = rec.value("Item").toString();
        a->Title = rec.value("Title").toString();
        a->Product = rec.value("Product").toString();
        a->Discount = rec.value("Discount").toDouble();
        a->ItemDiscount = rec.value("ItemDiscount").toDouble();
    }
    return ret;
}

SupplierData::SupplierData(QSqlDatabase *db)
{
    SqlDb = db;
}

bool SupplierData::CreateTables()
{
    QString qstr;
    bool ret = false;

    if (SqlDb->isOpen())
    {
        QSqlQuery query;

        qstr = "CREATE TABLE IF NOT EXISTS tbl_Suppliers ";
        qstr += "(Id INTEGER PRIMARY KEY, ";
        qstr += "Name TEXT, Prefix TEXT, ";
        qstr += "Ag_Product1 INT, Ag_Product2 INT, ";
        qstr += "Ag_Item1 INT, Ag_Item2 INT, ";
        qstr += "Ag_Title1 INT, Ag_Title2 INT, ";
        qstr += "Ag_Discount1 INT, Ag_Discount2 INT, ";
        qstr += "Ag_ItemDiscount1 INT, Ag_ItemDiscount2 INT, ";
        qstr += "Pl_Item1 INT, Pl_Item2 INT, ";
        qstr += "Pl_Title1 INT, Pl_Title2 INT, ";
        qstr += "Pl_Product1 INT, Pl_Product2 INT, ";
        qstr += "Pl_Unit1 INT, Pl_Unit2 INT, ";
        qstr += "Pl_Listprice1 INT, Pl_Listprice2 INT)";

        ret = query.exec(qstr);
        qDebug() << qstr;
        qDebug() << query.lastError().text();
    }

    return ret;
}

bool SupplierData::PutSupplierItem(Supplier *s)
{
    bool ret = false;
    QString qstr;

    if (SqlDb->isOpen())
    {
        QSqlQuery query;

        qstr = "INSERT INTO tbl_Suppliers";
        qstr += "(Name, Prefix, Ag_Product1, Ag_Product2, Ag_Item1, Ag_Item2, Ag_Title1, Ag_Title2, Ag_Discount1, Ag_Discount2, Ag_ItemDiscount1, Ag_ItemDiscount2, ";
        qstr += "Pl_Item1, Pl_Item2, Pl_Title1, Pl_Title2, Pl_Product1, Pl_Product2, Pl_Unit1, Pl_Unit2, Pl_Listprice1, Pl_Listprice2) VALUES (";
        qstr += "'" + s->Name + "', ";
        qstr += "'" + s->Prefix + "', ";
        qstr += QString::number(s->AgreementProduct[0]) + ", " + QString::number(s->AgreementProduct[1]) + ", ";
        qstr += QString::number(s->AgreementItem[0]) + ", " + QString::number(s->AgreementItem[1]) + ", ";
        qstr += QString::number(s->AgreementTitle[0]) + ", " + QString::number(s->AgreementTitle[1]) + ", ";
        qstr += QString::number(s->AgreementDiscount[0]) + ", " + QString::number(s->AgreementDiscount[1]) + ", ";
        qstr += QString::number(s->AgreementItemDiscount[0]) + ", " + QString::number(s->AgreementItemDiscount[1]) + ", ";
        qstr += QString::number(s->PricelistItem[0]) + ", " + QString::number(s->PricelistItem[1]) + ", ";
        qstr += QString::number(s->PricelistTitle[0]) + ", " + QString::number(s->PricelistTitle[1]) + ", ";
        qstr += QString::number(s->PricelistProduct[0]) + ", " + QString::number(s->PricelistProduct[1]) + ", ";
        qstr += QString::number(s->PricelistUnit[0]) + ", " + QString::number(s->PricelistUnit[1]) + ", ";
        qstr += QString::number(s->PricelistListprice[0]) + ", " + QString::number(s->PricelistListprice[1]) + ") ";

        ret = query.exec(qstr);
    }
    return ret;
}

bool SupplierData::GetSupplierList(QLinkedList<Supplier> *list)
{
    bool ret = false;
    QSqlQuery query;
    QSqlRecord rec;
    Supplier s;

    list->clear();

    if (SqlDb->isOpen())
    {
        ret = query.exec(QString("SELECT * FROM tbl_Suppliers"));

        if(ret)
        {
            query.first();
            do
            {
                rec = query.record();
                s.Name = rec.value("Name").toString();
                s.Prefix = rec.value("Prefix").toString();
                s.AgreementProduct[0] = rec.value("Ag_Product1").toInt();
                s.AgreementProduct[1] = rec.value("Ag_Product2").toInt();
                s.AgreementItem[0] = rec.value("Ag_Item1").toInt();
                s.AgreementItem[1] = rec.value("Ag_Item2").toInt();
                s.AgreementTitle[0] = rec.value("Ag_Title1").toInt();
                s.AgreementTitle[1] = rec.value("Ag_Title2").toInt();
                s.AgreementDiscount[0] = rec.value("Ag_Discount1").toInt();
                s.AgreementDiscount[1] = rec.value("Ag_Discount2").toInt();
                s.AgreementItemDiscount[0] = rec.value("Ag_ItemDiscount1").toInt();
                s.AgreementItemDiscount[1] = rec.value("Ag_ItemDiscount2").toInt();

                s.PricelistItem[0] = rec.value("Pl_Item1").toInt();
                s.PricelistItem[1] = rec.value("Pl_Item2").toInt();
                s.PricelistTitle[0] = rec.value("Pl_Title1").toInt();
                s.PricelistTitle[1] = rec.value("Pl_Title2").toInt();
                s.PricelistProduct[0] = rec.value("Pl_Product1").toInt();
                s.PricelistProduct[1] = rec.value("Pl_Product2").toInt();
                s.PricelistUnit[0] = rec.value("Pl_Unit1").toInt();
                s.PricelistUnit[1] = rec.value("Pl_Unit2").toInt();
                s.PricelistListprice[0] = rec.value("Pl_Listprice1").toInt();
                s.PricelistListprice[1] = rec.value("Pl_Listprice2").toInt();

                list->append(s);
            }
            while(query.next());
        }
    }
    return ret;
}

DatabaseManager::DatabaseManager()
{

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Prices");
    db.setUserName("Prices");
    db.setPassword("exit");

    if(db.open())
    {
        qDebug() << db.lastError();
        qFatal("Failed to connect.");
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
    return &db;
}
