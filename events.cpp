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
            QPointF initialPosition = QPointF(0, 0);
                   item->setPos(initialPosition); // Установка начальной позиции элемента
                   scene()->addItem(item);
                   event->acceptProposedAction();

                   // Испускание сигнала с текущими координатами элемента
                   emit itemDropped(text, initialPosition); // Испускание сигнала с координатами (0,0)

   }
}

void CustomGraphicsView::updateIconPosition(int index, QPointF newPosition) {
    int totalItems = scene()->items().count();
        // Начинаем с последнего элемента, уменьшаем индекс на каждой итерации
        for (int i = totalItems - 1; i >= 0; --i) {
            QGraphicsItem* item = scene()->items().at(i); // Получаем элемент по индексу
            if (auto* pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(item)) {
                // Вычисляем "обратный" индекс для сравнения с переданным индексом
                int reverseIndex = totalItems - 1 - i;
                if (reverseIndex == index) {
                    pixmapItem->setPos(newPosition);
                    return;
                }
            }
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


void CustomGraphicsView::resizeEvent(QResizeEvent *event) { //Обработчик события изменения размера виджета
    QGraphicsView::resizeEvent(event);
    getResize(); // Обновление размера сцены
}




