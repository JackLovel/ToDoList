#ifndef INFO_H
#define INFO_H

#include <QObject>
/**
 * 信息类
 */
class Info
{
public:
    Info();
    Info(int id, QString description, QString createDate, QString operation);
    void toString();

    int id;
    QString description;
    QString createDate;
    QString operation;
};

#endif // INFO_H
