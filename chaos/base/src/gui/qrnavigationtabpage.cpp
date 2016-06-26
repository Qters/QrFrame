#include "gui/qrnavigationtabpage.h"

#include <QtGui/qstandarditemmodel.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtCore/qdebug.h>

#include "gui/qrnavigationtabpageview.h"
#include "db/qrtblnavigation.h"

NS_CHAOS_BASE_BEGIN

class QrNavigationTabPagePrivate{
    QR_DECLARE_PUBLIC(QrNavigationTabPage)
public:
    QrNavigationTabPagePrivate(QrNavigationTabPage *q) :q_ptr(q) {}

public:
    void loadUI();
    void clearModel();
    void initModel(QString parentKey,
                   QStandardItem *rootItem,
                   QrNavigationDbData *data);
    void connectConfigs();

public:
    QrNavigationTabView *view = nullptr;
    QStandardItemModel *data = nullptr;
    QMap<QStandardItem*, QPushButton*> dataItemMapBtn;  //  store to call button click event when view click event happen
    QMap<QPushButton*, QString> buttonMapKey;   //   store to remove pushbutton of button container when reinit
};

void QrNavigationTabPagePrivate::loadUI()
{
    Q_Q(QrNavigationTabPage);
    view = new QrNavigationTabView(q);
    data = new QStandardItemModel(view);

    view->setModel(data);
    view->setFocusPolicy(Qt::NoFocus);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(view);

    q->setLayout(mainLayout);
}

void QrNavigationTabPagePrivate::clearModel()
{
    this->data->clear();

    Q_Q(QrNavigationTabPage);
    Q_FOREACH(QPushButton* pushbtn, dataItemMapBtn) {
        emit q->removeButton(this->buttonMapKey[pushbtn], pushbtn);
        delete pushbtn;
        pushbtn = nullptr;
    }
    this->dataItemMapBtn.clear();
}

void QrNavigationTabPagePrivate::initModel(QString parentKey,
                                           QStandardItem *rootItem,
                                           QrNavigationDbData *dbData)
{
    Q_Q(QrNavigationTabPage);
    Q_FOREACH(QrNavigationDbData* data, dbData->children) {
        QStandardItem *item = new QStandardItem(data->display);
        rootItem->appendRow(item);
        if (! data->children.empty()) {
            initModel(parentKey.isEmpty() ? data->key
                        : parentKey+"."+data->key,
                      item,
                      data);
        } else {    //  leaf node
            auto itemPath = parentKey + "." + data->key;
            auto itemButton = new QPushButton(itemPath);
            buttonMapKey[itemButton] = itemPath;
            dataItemMapBtn[item] = itemButton;

            emit q->addButton(itemPath, itemButton);
        }
    }
}

void QrNavigationTabPagePrivate::connectConfigs()
{
    QObject::connect(this->view, &QrNavigationTabView::clicked, [this](const QModelIndex &index){
        if (! index.isValid()) {
            return;
        }
        auto item = this->data->itemFromIndex(index);
        if (! this->dataItemMapBtn.contains(item)) {
            return ;
        }
        dataItemMapBtn[item]->click();
        qDebug() << "click " << this->buttonMapKey[dataItemMapBtn[item]];
    });
}

NS_CHAOS_BASE_END

USING_NS_CHAOS_BASE;

QrNavigationTabPage::QrNavigationTabPage(QWidget* parent)
    :QWidget(parent), d_ptr(new QrNavigationTabPagePrivate(this))
{
    d_ptr->loadUI();
}

void QrNavigationTabPage::initModelByDbData(QrNavigationDbData *dbData)
{
    Q_D(QrNavigationTabPage);
    d->clearModel();
    auto rootItem = d->data->invisibleRootItem();
    d->initModel("", rootItem, dbData);
    d->connectConfigs();
}
