#ifndef QRMAINWINDOW_H
#define QRMAINWINDOW_H

#include <QMainWindow>

#include "qrframe_global.h"

namespace Qters {

namespace QrFrame {

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

}   //  namespace QrFrame

}   //  namespace Qters

#endif // QRMAINWINDOW_H
