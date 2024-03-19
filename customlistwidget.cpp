#include "customlistwidget.h"

CustomListWidget::CustomListWidget(QWidget *parent) : QListWidget(parent) {
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    addIconsWithLabels();
}

void CustomListWidget::addIconsWithLabels()// Функция для добавления элементов в QListWidget
{
    QListWidgetItem *item1 = new QListWidgetItem(QIcon(":/img/green.jpg"), "Зеленый");
    this->addItem(item1);

    QListWidgetItem *item2 = new QListWidgetItem(QIcon(":/img/red.jpg"), "Красный");
    this->addItem(item2);

    QListWidgetItem *item3 = new QListWidgetItem(QIcon(":/img/orange.jpg"), "Оранжевый");
    this->addItem(item3);

    QListWidgetItem *item4 = new QListWidgetItem(QIcon(":/img/blue.png"), "Синий");
    this->addItem(item4);

    QListWidgetItem *item5 = new QListWidgetItem(QIcon(":/img/yellow.png"), "Желтый");
    this->addItem(item5);
}

void CustomListWidget::mousePressEvent(QMouseEvent *event) { // Переопределение события нажатия мыши для реализации перетаскивания элементов
    QListWidget::mousePressEvent(event);

    if (event->button() != Qt::LeftButton) return;  // Если нажата не левая кнопка мыши, обработка прекращается

    QListWidgetItem *item = itemAt(event->pos());  // Получение элемента под курсором мыши
    if (!item) return;

    QByteArray itemData;  // Подготовка данных элемента для перетаскивания
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = item->icon().pixmap(32, 32);
    QString text = item->text();
    dataStream << pixmap << text; // Запись данных в поток

    QMimeData *mimeData = new QMimeData; // Создание объекта QMimeData и установка данных элемента
    mimeData->setData("application/vnd.text.listwidgetitem", itemData);

    QDrag *drag = new QDrag(this); // Создание объекта QDrag для реализации операции перетаскивания
    drag->setMimeData(mimeData); // Установка данных для перетаскивания
    drag->setPixmap(pixmap);
    drag->setHotSpot(QPoint(0, 0));
    drag->exec(Qt::CopyAction | Qt::MoveAction); // Начало операции перетаскивания с возможностью копирования или перемещения
}
