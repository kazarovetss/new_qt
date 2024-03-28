#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPixmap>
#include<QGraphicsScene>
#include <QDataStream>
#include <QGraphicsPathItem>
#include <QStandardItemModel>
#include <QMap>
#include "ui_mainwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void updateModel(const QString &itemName);
    void addRowsAndColumns(int rows, int cols);
    void displayCoordinates(const QModelIndex &current, const QModelIndex &previous);// Слот для обновления модели
    void handleItemDropped(const QString &itemName, const QPointF &position);
    void onItemChanged(QStandardItem *item);
    int getCurrentListViewRow();
signals:
    void iconPositionChanged(const QString &itemName, const QPointF &newPosition);
private:
    QStringListModel *model;
    QStandardItemModel *tableModel;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    CustomGraphicsView *customGraphicsView;
    QVector<QPointF> coordinates;

};
#endif // MAINWINDOW_H
