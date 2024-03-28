#include "events.h"
#include "ui_mainwindow.h"
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
            QPointF initialPosition = QPointF(100, 100); // Это можно сделать изменяемым свойством класса
                   item->setPos(initialPosition); // Установка начальной позиции элемента
                   scene()->addItem(item);
                   event->acceptProposedAction();

                   // Испускание сигнала с текущими координатами элемента
                   emit itemDropped(text, initialPosition); // Испускание сигнала с координатами (0,0)

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

void CustomGraphicsView::updateIconPosition(const QString &rowIndex, const QPointF &newPosition) {

    int index = rowIndex.toInt();
    int currentIndex = 0;

    foreach(QGraphicsItem *item, scene()->items()) {
        if(QGraphicsPixmapItem* pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(item)) {
            if(currentIndex == index) {
                pixmapItem->setPos(newPosition); // Обновление позиции иконки
                return;
            }
            currentIndex++;
        }
    }
}

void CustomGraphicsView::resizeEvent(QResizeEvent *event) { //Обработчик события изменения размера виджета
    QGraphicsView::resizeEvent(event);
    getResize(); // Обновление размера сцены
}




