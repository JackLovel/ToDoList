#include "info.h"
#include <QDebug>

Info::Info()
{

}

Info::Info(QString id, QString description, QString createDate, QString operation)
{
    this->id = id;
    this->description = description;
    this->createDate = createDate;
    this->operation = operation;
}

void Info::toString()
{
    qDebug() << this->id << this->description << this->createDate << this->operation;
}
