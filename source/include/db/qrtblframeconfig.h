#ifndef QRTBLCONFIG_H
#define QRTBLCONFIG_H

#include "entity/qrsqltable.h"

#include "qrframe_global.h"

NS_QRFRAME_BEGIN

/*!
 * \brief table class, for 'config' in database
 */
class QRFRAMESHARED_EXPORT QrTblFrameConfig : public QrOrm::QrSqlTable
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

class QRFRAMESHARED_EXPORT QrTblFrameConfigHelper
{
public:
    static bool getValueBy(const QString& type, const QString& key, QString *configValue);
    static bool setVauleBy(const QString& type, const QString& key, const QString& configValue);
    static bool getKeyValuesByType(const QString& type, QMap<QString, QString> *configValues);

private:
    static bool getKeyValuesBy(const QString& by, const QString& value, QMap<QString, QString> *configValues);
};

NS_QRFRAME_END

#endif // QRTBLCONFIG_H
