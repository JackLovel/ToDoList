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
    }
}

void Connection::loadData()
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
        qDebug() << "数据库创建成功";
    }

    QString selectAllSql = "select * from infos";
    query->prepare(selectAllSql);

    if (!query->exec()) {
        return; // error
    } else {
        infos.clear(); // 清空之前的数据

        while(query->next()) {
            Info *info = new Info();
            info->id = query->value(0).toString();
            info->description = query->value(1).toString();
            info->createDate = query->value(2).toString();
            info->operation = query->value(3).toString();

            infos.push_back(info);
        }
     }

//    qDebug() << infos;
    emit sendAllData(infos);
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


// 修改数据
void Connection::updateDb(Info *info)
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

        QString updateSql = QString("update infos set description = %1 createDate = %2 operation = %3 where id = %4;")
                                .arg(info->description)
                                .arg(info->createDate)
                                .arg(info->operation)
                                .arg(info->id);
        query.prepare(updateSql);

        if (!query.exec()) {
            return;
        } else {
            qDebug() << "插入记录";
        }
    }


    db.close();
}
