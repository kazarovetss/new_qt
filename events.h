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

class Events
{
public:
    Events();
};

class CustomGraphicsView : public QGraphicsView{
    Q_OBJECT
signals:
    void itemDropped(const QString &itemName, const QPointF &position);
public:
    explicit CustomGraphicsView(QWidget *widget = nullptr);
public slots:
    void getResize();
    void updateIconPosition(const QString &itemName, const QPointF &newPosition);
protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent (QDragMoveEvent *event);
    void resizeEvent(QResizeEvent *event);

};
#endif // EVENTS_H
