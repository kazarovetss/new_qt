#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMimeData>
#include <QDrag>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStringListModel(this); //Установка модели для QListView
    ui->listView->setModel(model);

    customGraphicsView = qobject_cast<CustomGraphicsView*>(ui->graphicsView); //Инициализация QGraphicsView созданного в Design

    connect(customGraphicsView, &CustomGraphicsView::itemDropped, this, &MainWindow::handleItemDropped); //подключение слота для обработки события drop и получения координат
    connect(ui->listView->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::displayCoordinates); //Подключение слота выбора элемента из QListView и отображения координат
    connect(this, &MainWindow::iconPositionChanged, customGraphicsView, &CustomGraphicsView::updateIconPosition);

    tableModel = new QStandardItemModel(0, 0, this);
    ui->tableView->setModel(tableModel);

    connect(tableModel, &QStandardItemModel::itemChanged, this, &MainWindow::onItemChanged);

    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->verticalHeader()->setVisible(false);


    addRowsAndColumns(2, 2); //Установка таблицы 2 на 2
}

void MainWindow::updateModel(const QString &itemName) { //Вывод наимонвания иконки в QListView
    QStringList list = model->stringList();
    list << itemName;
    model->setStringList(list);
}

void MainWindow::addRowsAndColumns(int rows, int cols) { //Добавление фиксированных наименований в таблице
    tableModel->setRowCount(rows);
    tableModel->setColumnCount(cols);

    QStandardItem *itemX = new QStandardItem("X");
    itemX->setEditable(false);
    tableModel->setItem(0, 0, itemX);

    QStandardItem *itemY = new QStandardItem("Y");
    itemY->setEditable(false);
    tableModel->setItem(1, 0, itemY);
}

void MainWindow::displayCoordinates(const QModelIndex &current, const QModelIndex &previous) { //отображение координат
    Q_UNUSED(previous)

    lastSelectedRow = current.row(); // Обновляем последний выбранный ряд

        if (lastSelectedRow == -1) {
            qDebug() << "Ничего не выбрано";
            return;
        } else {
            qDebug() << "Выбрано " << lastSelectedRow;
        }

        QPointF position = coordinates.at(lastSelectedRow);

        tableModel->setItem(0, 1, new QStandardItem(QString::number(position.x())));
        tableModel->setItem(1, 1, new QStandardItem(QString::number(position.y())));
}

void MainWindow::handleItemDropped(const QString &itemName, const QPointF &position) {

   updateModel(itemName);

   coordinates.append(position); // Добавление координат в конец вектора

   qDebug() << "Иконка была добавлена на позиции" << position;
}

void MainWindow::onItemChanged(QStandardItem *item) {
    if (item->column() != 1) return; // Реагируем на изменения во втором столбце

        if (lastSelectedRow == -1) return; // Если ничего не выбрано, выходим

        qreal value = item->text().toDouble();
        QPointF newPosition = coordinates.at(lastSelectedRow); // Используем lastSelectedRow

        if (item->row() == 0) {
            newPosition.setX(value);
        } else if (item->row() == 1) {
            newPosition.setY(value);
        }

        coordinates[lastSelectedRow] = newPosition; // Обновляем координаты для выбранной строки

        emit iconPositionChanged(lastSelectedRow, newPosition);
}

MainWindow::~MainWindow()
{
    delete ui;
}

