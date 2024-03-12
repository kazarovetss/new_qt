#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMimeData>
#include <QDrag>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringListModel *model = new QStringListModel();
            QStringList list;
            model->setStringList(list);
            ui->listView->setModel(model);

}

MainWindow::~MainWindow()
{
    delete ui;
}

