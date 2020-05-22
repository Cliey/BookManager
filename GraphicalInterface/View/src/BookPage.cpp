#include "View/BookPage.hpp"
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLabel>

BookPage::BookPage(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout();
    QTextEdit* left =  new QTextEdit();
    initRightPane();
    layout->addWidget(left);
    layout->addWidget(right);

    setLayout(layout);
}

void BookPage::initRightPane()
{
    right =  new QWidget();
    gridLayout = new QGridLayout();
    QLabel* cover = new QLabel("Cover");
    gridLayout->addWidget(cover, 0, 0, 1, 2);
    createLabelAndData("Title", "The title of the book", 1);
    createLabelAndData("Authors", "Authors", 2);
    createLabelAndData("Category", "Best Category", 3);
    createLabelAndData("Published", "Someday", 4);

    right->setLayout(gridLayout);

}

void BookPage::createLabelAndData(QString label, QString data, int row)
{
    QLabel* labelInformation = new QLabel(label);
    QLabel* dataInformation = new QLabel(data);
    gridLayout->addWidget(labelInformation, row, 0);
    gridLayout->addWidget(dataInformation, row, 1);
}