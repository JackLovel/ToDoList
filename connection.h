#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QSqlDatabase>
#include "info.h"

class Connection : QObject
{
    Q_OBJECT
public:
    Connection();
    ~Connection();

    void connectDb();
    QString databaseName = "Info.db";

    void selectAll();
    void insertDb(Info *info);
    void updateDb(Info *info);
};

#endif // CONNECTION_H
