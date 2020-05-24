#include "View/CategoryPage.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <QPushButton>
#include <QMenu>
#include <QAction>

#include <QListWidgetItem>
#include <iostream>

CategoryPage::CategoryPage(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout();
    right =  new QLabel("Something here later");
    initLeftPane();
    layout->addLayout(leftLayout, 50);
    layout->addWidget(right, 50);

    setLayout(layout);
}

void CategoryPage::initLeftPane()
{
    leftLayout = new QVBoxLayout();
    initList();
    QHBoxLayout* headerLayout = new QHBoxLayout();

    QLabel* headerName = new QLabel("Categories");
    QFont fontLabel;
    fontLabel.setPointSize(16);
    headerName->setFont(fontLabel);

    QPushButton* buttonDeleteCategory = new QPushButton();
    buttonDeleteCategory->setIcon(QIcon(":/icons/trash.png"));
    buttonDeleteCategory->setFixedSize(28, 28);
    buttonDeleteCategory->setIconSize(QSize(20, 20));
    QObject::connect(buttonDeleteCategory, SIGNAL(clicked()), this, SLOT(deleteCategoriesSelected()));

    headerLayout->addWidget(headerName);
    headerLayout->addWidget(buttonDeleteCategory);

    leftLayout->addLayout(headerLayout);
    leftLayout->addWidget(categoryListView);
}

void CategoryPage::initList()
{
    QList<BookManager::Category::Category> categoryTest = {
        {1, "Thriller"},
        {2, "Sci-Fi"},
        {3, "Fantasy"},
        {4, "Young Adult"}};

    // Here DatabaseManager -> getCategory

    categoryModel = new CategoryModel(categoryTest);
    categoryListView = new QListView();
    categoryListView->setModel(categoryModel);
    categoryListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    categoryListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    categoryListView->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(categoryListView, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(openMenu(const QPoint&)));
}

void CategoryPage::deleteCategoriesSelected()
{
    QItemSelectionModel* selection = categoryListView->selectionModel();
    QModelIndexList listIndexes = selection->selectedIndexes();
    std::sort(listIndexes.rbegin(), listIndexes.rend()); // reverse iterator, greater to lower
    for(auto& index : listIndexes)
    {
        categoryModel->removeRow(index.row());
    }
}

void CategoryPage::openMenu(const QPoint& pos)
{
    // Idea of the contextMenu
    QMenu menuItem;
    QAction* actionAdd = menuItem.addAction(tr("Add category", "Add a category"));
    QAction* actionSearchBook = menuItem.addAction(tr("Search books", "Search book with the selected category"));
    QAction* actionCopyCategoryName = menuItem.addAction(tr("Copy Name", "Copy category name"));

    QModelIndex pointedItem = categoryListView->indexAt(pos);
    QAction* selectedAction;
    if(pointedItem.isValid())
    {
        selectedAction = menuItem.exec(QCursor::pos());
        return;
    }
    actionSearchBook->setEnabled(false);
    actionCopyCategoryName->setEnabled(false);
    selectedAction = menuItem.exec(QCursor::pos());
    return;
}