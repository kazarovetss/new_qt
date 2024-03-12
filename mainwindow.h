#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPixmap>
#include<QGraphicsScene>
#include <QDataStream>
#include <QGraphicsPathItem>
#include <QStandardItemModel>
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
    void updateListViewModel(QStringListModel *model) {
        qDebug() << "Обновление модели списка";
            ui->listView->setModel(model);}
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    CustomGraphicsView *customGraphicsView;
};
#endif // MAINWINDOW_H
