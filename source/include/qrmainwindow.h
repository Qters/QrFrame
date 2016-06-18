#ifndef QRMAINWINDOW_H
#define QRMAINWINDOW_H

#include <QtWidgets/qmainwindow.h>

#include "qrframe_global.h"

NS_QRFRAME_BEGIN

/*!
 * \brief MainWindow in Qters' Framework
 */
class QRFRAMESHARED_EXPORT QrMainWindow : public QMainWindow
{
public:
    explicit QrMainWindow(QWidget *parent = 0);
    virtual ~QrMainWindow();

public:
    /*!
     * \brief   all plugins will be loaded before init.
     */
    virtual bool init();
};

NS_QRFRAME_END

#endif // QRMAINWINDOW_H
