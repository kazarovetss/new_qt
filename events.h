#ifndef EVENTS_H
#define EVENTS_H
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QGraphicsView>
#include <QListWidget>
#include <QMimeData>
#include <QGraphicsPixmapItem>
#include <QStandardItemModel>
#include <QStringListModel>
//#include "ui_mainwindow.h"
//#include "customlistwidget.h"
class Events
{
public:
    Events();
};

class CustomGraphicsView : public QGraphicsView{
    Q_OBJECT
signals:
    void itemDrop(QString);
public:
    explicit CustomGraphicsView(QWidget *widget = nullptr);
public slots:
    void getResize();
protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent (QDragMoveEvent *event);
    void resizeEvent(QResizeEvent *event);
    using QGraphicsView::QGraphicsView;
};
#endif // EVENTS_H
