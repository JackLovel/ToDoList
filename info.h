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
    Info(QString id, QString description, QString createDate, QString operation);
    void toString();

    QString id;
    QString description;
    QString createDate;
    QString operation;
};

#endif // INFO_H
