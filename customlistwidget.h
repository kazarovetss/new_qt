#define MYLISTWIDGET_H

#include <QListWidget>
#include <QListWidget>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>

class CustomListWidget : public QListWidget {
Q_OBJECT

public:
    CustomListWidget(QWidget *parent = nullptr);
protected:
    void addIconsWithLabels();
    void mousePressEvent(QMouseEvent *event);
    // Здесь могут быть перегруженные функции или новые методы
};
