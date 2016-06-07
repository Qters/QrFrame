#ifndef QRMAINWINDOW_H
#define QRMAINWINDOW_H

#include <QMainWindow>

#include "qrframe_global.h"

NS_QRFRAME_BEGIN

/*!
 * \brief MainWindow in Qters' Framework
 */
class QRFRAMESHARED_EXPORT QrMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit QrMainWindow(QWidget *parent = 0);
    virtual ~QrMainWindow();

public:
    /*!
     * \brief
     */
    virtual bool init();

signals:

public slots:
};

NS_QRFRAME_END

#endif // QRMAINWINDOW_H
