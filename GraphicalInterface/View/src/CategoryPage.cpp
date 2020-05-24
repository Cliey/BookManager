#include "View/CategoryPage.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <QPushButton>
#include <QMenu>
#include <QAction>

#include <QListWidgetItem>
#include <iostream>

CategoryPage::CategoryPage(std::shared_ptr<BookManager::Manager::DatabaseManager> databaseManager, QWidget *parent)
    : databaseManager(databaseManager), QWidget(parent)
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
    QObject::connect(buttonDeleteCategory, &QPushButton::clicked, this, &CategoryPage::deleteCategoriesSelected);

    headerLayout->addWidget(headerName);
    headerLayout->addWidget(buttonDeleteCategory);

    leftLayout->addLayout(headerLayout);
    leftLayout->addWidget(categoryListView);
}

void CategoryPage::initList()
{
    auto categoryVect = databaseManager->getCategoryVector(20, 0);
    QList<BookManager::Category::Category> categoryList(categoryVect.begin(), categoryVect.end());

    categoryModel = new CategoryModel(categoryList);
    categoryListView = new QListView();
    categoryModel->sort(CategoryModel::CategoryColumn::Name);
    categoryListView->setModel(categoryModel);
    categoryListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    categoryListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    categoryListView->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(categoryListView, &QListView::customContextMenuRequested, this, &CategoryPage::openMenu);
}

void CategoryPage::deleteCategoriesSelected()
{
    QItemSelectionModel* selection = categoryListView->selectionModel();
    QModelIndexList listIndexes = selection->selectedIndexes();
    std::sort(listIndexes.rbegin(), listIndexes.rend()); // reverse iterator, greater to lower
    for(auto& index : listIndexes)
    {
        auto categoryId = categoryModel->data(index, CategoryModel::CategoryRole::CategoryId);
        databaseManager->deleteCategory(categoryId.toInt(), false);
        // If book with this category : popup a warning.
        // Have to refactor how to manage it. For now : does nothing
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