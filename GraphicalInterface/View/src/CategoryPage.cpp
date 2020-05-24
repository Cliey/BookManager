#include "View/CategoryPage.hpp"
#include <QHBoxLayout>


CategoryPage::CategoryPage(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout();
    right =  new QLabel("Something here later");
    left =  new QWidget();
    layout->addWidget(left, 50);
    layout->addWidget(right, 50);

    setLayout(layout);
}