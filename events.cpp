#include "events.h"
Events::Events()
{

}

CustomGraphicsView::CustomGraphicsView(QWidget *widget):QGraphicsView(widget)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
        this->setScene(scene);
    setAcceptDrops(true);
}

void CustomGraphicsView::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/vnd.text.listwidgetitem")) {

        QByteArray itemData = event->mimeData()->data("application/vnd.text.listwidgetitem"); // Извлечение данных из события
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap; // Чтение pixmap и текста из потока данных
        QString text;
        dataStream >> pixmap >> text;

        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap); // Создание и добавление нового элемента сцены
        item->setFlag(QGraphicsItem::ItemIsSelectable, true);
        item->setData(0, text);
        item->setPos(10,10);
        scene()->addItem(item);
        event->acceptProposedAction();
    }

}

void CustomGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/vnd.text.listwidgetitem")) {
        event->acceptProposedAction(); // Принятие действия
    }
}

void CustomGraphicsView::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/vnd.text.listwidgetitem")) { // Проверка формата и принятие действия
        event->acceptProposedAction();
    }
}

void CustomGraphicsView::getResize() { // Слот для обновления размера сцены

    scene()->setSceneRect(0, 0, width()-2, height()-2);// Установка размера сцены равным размеру виджета минус 2 пикселя с каждой стороны
}

void CustomGraphicsView::CustomGraphicsView::resizeEvent(QResizeEvent *event) { //Обработчик события изменения размера виджета
    QGraphicsView::resizeEvent(event);
    getResize(); // Обновление размера сцены
}




