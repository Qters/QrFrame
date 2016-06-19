#ifndef QRTBLLOADINFO_H
#define QRTBLLOADINFO_H

#include "entity/qrsqltable.h"

#include "qrframe_global.h"

NS_QRFRAME_BEGIN

/*!
 * \brief table class, for 'load_info' in database
 */
class QRFRAMESHARED_EXPORT QrTblLoadInfo : public QrOrm::QrSqlTable
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId WRITE setId)
    Q_PROPERTY(QString load_name READ getLoad_name WRITE setLoad_name)

    // QrSqlTable interface
public:
    virtual QString tableName() const { return "load_info"; }

public:
    int getId() const;
    void setId(int value);

    QString getLoad_name() const;
    void setLoad_name(const QString &value);

private:
    int id;
    QString load_name;
};

class QRFRAMESHARED_EXPORT QrTblLoadInfoHelper
{
public:
    static bool getLoadServices(QVector<QString>& loadNames);
};

NS_QRFRAME_END

#endif // QRTBLLOADINFO_H
