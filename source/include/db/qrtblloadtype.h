﻿#ifndef QRTBLLOADTYPE_H
#define QRTBLLOADTYPE_H

#include "entity/qrsqltable.h"

#include "qrframe_global.h"

NS_QRFRAME_BEGIN

/*!
 * \brief table class, for 'load_type' in database
 */
class QRFRAMESHARED_EXPORT QrTblLoadType : public QrOrm::QrSqlTable
{
public:
    Q_OBJECT
    Q_PROPERTY(int id READ getId WRITE setId)
    Q_PROPERTY(int type READ getType WRITE setType)
    Q_PROPERTY(QString note READ getNote WRITE setNote)

public:
    enum class LoadType{
        Module = 1,
        Service = 2,
    };

    // QrSqlTable interface
public:
    virtual QString tableName() const { return "load_type"; }

public:
    int getId() const;
    void setId(int value);

    int getType() const;
    void setType(int value);

    QString getNote() const;
    void setNote(const QString &value);

private:
    int id;
    int type;
    QString note;
};

class QRFRAMESHARED_EXPORT QrTblLoadTypeHelper
{
public:
    static bool getLoadTypes(QVector<QrTblLoadType::LoadType>& loadTypes);
};

NS_QRFRAME_END

#endif // QRTBLLOADTYPE_H
