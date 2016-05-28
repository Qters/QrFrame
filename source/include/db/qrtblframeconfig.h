﻿#ifndef QRTBLCONFIG_H
#define QRTBLCONFIG_H

#include "entity/qrsqltable.h"

namespace Qters {

namespace QrFrame {

/*!
 * \brief table class, for 'config' in database
 */
class QrTblFrameConfig : public QrOrm::QrSqlTable
{
public:
    Q_OBJECT
    Q_PROPERTY(int id READ getId WRITE setId)
    Q_PROPERTY(QString type READ getType WRITE setType)
    Q_PROPERTY(QString key READ getKey WRITE setKey)
    Q_PROPERTY(QString value READ getValue WRITE setValue)

    // QrSqlTable interface
public:
    virtual QString tableName() const override {return "frame_config";}

public:
    int getId() const;
    void setId(int value);

    QString getKey() const;
    void setKey(const QString &value);

    QString getValue() const;
    void setValue(const QString &value);

    QString getType() const;
    void setType(const QString & value);

private:
    int id;
    QString type;
    QString key;
    QString value;
};

class QrTblFrameConfigHelper
{
public:
    static bool getValueByKey(const QString& key, QString *configValue);
    static bool setVauleByKey(const QString& key, const QString& configValue);
    static bool getKeyValuesByType(const QString& type, QMap<QString, QString> *configValues);

private:
    static bool getKeyValuesBy(const QString& by, const QString& value, QMap<QString, QString> *configValues);
};

}   //  namespace QrFrame

}   //  namespace Qters

#endif // QRTBLCONFIG_H
