#include "View/PersonPage.hpp"
#include <QHBoxLayout>
#include <QTableView>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QVBoxLayout>
#include <iostream>

PersonPage::PersonPage(std::shared_ptr<BookManager::Manager::DatabaseManager> databaseManager, QWidget *parent)
    : databaseManager(databaseManager), QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout();
    right =  new QLabel("Something here later");
    initLeftPane();
    layout->addLayout(leftLayout, 50);
    layout->addWidget(right, 50);

    setLayout(layout);
}

void PersonPage::initLeftPane()
{
    leftLayout = new QVBoxLayout();

    auto personVector = databaseManager->getPersonVector(20, 0);
    QList<BookManager::Entity::Person> personList(personVector.begin(), personVector.end());

    personModel = new PersonModel(personList);
    QTableView* personTableView = new QTableView();

    personTableView->setModel(personModel);
    personTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    personTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    personTableView->verticalHeader()->hide();

    leftLayout->addWidget(personTableView);
}