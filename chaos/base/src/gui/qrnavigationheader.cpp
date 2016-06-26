#include "gui/qrnavigationheader.h"

#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>

NS_CHAOS_BASE_BEGIN

class QrNavigationHeaderPrivate{
    QR_DECLARE_PUBLIC(QrNavigationHeader)
public:
    QrNavigationHeaderPrivate(QrNavigationHeader *q) : q_ptr(q) {}

public:
    void loadUI();

public:
    QPushButton* autoHide = nullptr;
    QPushButton* search = nullptr;
};

void QrNavigationHeaderPrivate::loadUI()
{
    Q_Q(QrNavigationHeader);
    autoHide = new QPushButton(q);
    autoHide->setCursor(Qt::PointingHandCursor);

    search = new QPushButton(q);
    search->setCursor(Qt::PointingHandCursor);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(autoHide, 0, Qt::AlignLeft);
    mainLayout->addWidget(search, 0, Qt::AlignRight);
    q->setLayout(mainLayout);
}

NS_CHAOS_BASE_END


USING_NS_CHAOS_BASE;

QrNavigationHeader::QrNavigationHeader(QWidget* parent)
    : QFrame(parent), d_ptr(new QrNavigationHeaderPrivate(this))
{
    d_ptr->loadUI();
}

