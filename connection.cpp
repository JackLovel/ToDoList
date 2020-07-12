#include "connection.h"

#include <QSqlDatabase>
#include <qapplication.h>
#include <qmessagebox.h>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

Connection::Connection()
{
    connectDb();
}

Connection::~Connection()
{

}
void Connection::connectDb()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);
    db.open();
    if (!db.isOpen()) {
        qDebug() << "数据库无法打开";
        return; // error
    }

    // 创建数据库
    QSqlQuery *query = new QSqlQuery("", db);
    QString initSql = "create table if not exists infos (id varchar(100) primary key, \
            description varchar(100),\
            createDate varchar(100),\
            operation varchar(100))";

    if(query->exec(initSql)) {
        qDebug() << "Create testResult Successful";
    } else {
        qDebug() << "Create testResult faild";
    }
}

void Connection::selectAll()
{
    connectDb();

    QString selectAllSql = "select * from infos";
    QSqlQuery query;
    query.prepare(selectAllSql);

    if (!query.exec()) {
        return; // error
    } else {
        while(query.next()) {
            Info *info = new Info();
            info->id = query.value(0).toString();
            info->description = query.value(1).toString();
            info->createDate = query.value(2).toInt();
            info->operation = query.value(3).toInt();
//                studentVector.push_back(s); // 把数据库中所有数据写到 集合中
        }
     }
}

// 插入数据
void Connection::insertDb(Info *info)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);

    if (db.open()) {
        QSqlQuery query;
        QString createSql = "create table if not exists infos (id varchar(100) primary key, \
                description varchar(100),\
                createDate varchar(100),\
                operation varchar(100))";

            query.prepare(createSql);
            if (!query.exec()) {
                qDebug() << "数据库已存在";
            }

        QString insertSql = "insert into infos values(?, ?, ?, ?)";
        query.prepare(insertSql);
        query.bindValue(0, info->id);
        query.bindValue(1, info->description);
        query.bindValue(2, info->createDate);
        query.bindValue(3, info->operation);

        if (!query.exec()) {
            return;
        } else {
            qDebug() << "插入记录";
        }
    }


    db.close();
}
