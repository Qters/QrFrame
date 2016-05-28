#ifndef QRTBLLOADINFO_H
#define QRTBLLOADINFO_H

#include "db/qrtblloadtype.h"

#include "entity/qrsqltable.h"

namespace Qters {

namespace QrFrame {

/*!
 * \brief table class, for 'load_info' in database
 */
class QrTblLoadInfo : public QrOrm::QrSqlTable
{
public:
    Q_OBJECT
    Q_PROPERTY(int id READ getId WRITE setId)
    Q_PROPERTY(int type_id READ getType_id WRITE setType_id)
    Q_PROPERTY(QString load_name READ getLoad_name WRITE setLoad_name)

    // QrSqlTable interface
public:
    virtual QString tableName() const { return "load_info"; }

public:
    int getId() const;
    void setId(int value);

    int getType_id() const;
    void setType_id(int value);

    QString getLoad_name() const;
    void setLoad_name(const QString &value);

private:
    int id;
    int type_id;
    QString load_name;
};

class QrTblLoadInfoHelper
{
public:
    static bool getLoadNamesByLoadType(QrTblLoadType::LoadType typeId, QVector<QString>& loadNames);
};

}   //  namespace QrFrame

}   //  namespace Qters

#endif // QRTBLLOADINFO_H
