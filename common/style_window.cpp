#include <QPushButton>
#include <QListWidget>
#include "style_window.hpp"

StyleWindow::StyleWindow(const QString &title, QWidget *parent)
    : QDockWidget(title, parent)
{
    setFeatures(QDockWidget::DockWidgetFloatable);
    setFloating(true);

    QListWidget *customerList = new QListWidget(this);
     customerList->addItems(QStringList()
             << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
             << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
             << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
             << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
             << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
             << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
    setWidget(customerList);
    //setWidget(new QPushButton("asdf"));
}

StyleWindow::StyleWindow(QWidget *parent)
    : QDockWidget(parent)
{
}
