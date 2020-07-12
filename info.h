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

    QString id; // 序号
    QString description; // 介绍
    QString createDate; // 创建时间
    QString operation; // 操作
};

#endif // INFO_H
