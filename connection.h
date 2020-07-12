#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QSqlDatabase>
#include "info.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection();
    ~Connection();

    void connectDb();
    QString databaseName = "Info.db";
    QVector<Info*> infos;

    void loadData();
    void insertDb(Info *info);
    void updateDb(Info *info);

signals:
    void sendAllData(QVector<Info*> infos);
};

#endif // CONNECTION_H
