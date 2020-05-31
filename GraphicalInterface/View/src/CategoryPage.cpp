#include "View/CategoryPage.hpp"
#include "Utils/Exceptions.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
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
    QObject::connect(categoryListView, &QListView::doubleClicked, this,  qOverload<QModelIndex>(&CategoryPage::editCategorySelected));
}

void CategoryPage::deleteCategoriesSelected()
{
    QItemSelectionModel* selection = categoryListView->selectionModel();
    QModelIndexList listIndexes = selection->selectedIndexes();
    std::sort(listIndexes.rbegin(), listIndexes.rend()); // reverse iterator, greater to lower
    for(auto& index : listIndexes)
    {
        deleteCategorySelected(index);
    }
}

void CategoryPage::deleteCategorySelected(const QModelIndex& index)
{
    auto category = categoryModel->data(index, CategoryModel::CategoryRole::CategoryObject).value<BookManager::Category::Category>();
    try
    {
        databaseManager->deleteCategory(category.getId(), false);
        categoryModel->removeRow(index.row());
        return;
    }
    catch(const Utils::Exceptions::EC_ForeignKeyFound& e)
    {
        auto response = QMessageBox::critical(this, "Error deleting Category" , e.getStr(), QMessageBox::Yes | QMessageBox::No);
        if(response == QMessageBox::Yes)
        {
            e.executeCallback();
            categoryModel->removeRow(index.row());
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void CategoryPage::openMenu(const QPoint& pos)
{
    // Idea of the contextMenu
    QMenu menuItem;
    QAction* actionAdd = menuItem.addAction(tr("Add category", "Add a category"));
    QObject::connect(actionAdd, &QAction::triggered, [this](){ emit addCategory(); });
    QAction* actionEdit = menuItem.addAction(tr("Edit category", "Edit a category"));
    QObject::connect(actionEdit, &QAction::triggered, this,  qOverload<>(&editCategorySelected));
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
    actionEdit->setEnabled(false);
    actionCopyCategoryName->setEnabled(false);
    selectedAction = menuItem.exec(QCursor::pos());
    return;
}

void CategoryPage::editCategorySelected()
{
    QItemSelectionModel *selection = categoryListView->selectionModel();
    QModelIndex index = selection->currentIndex();
    editCategorySelected(index);
}

void CategoryPage::editCategorySelected(QModelIndex index)
{
    auto category = categoryModel->data(index, CategoryModel::CategoryRole::CategoryObject).value<BookManager::Category::Category>();
    emit editCategory(category);
}


void CategoryPage::insertCategory(const BookManager::Category::Category& category)
{
    int nbRowModel = categoryModel->rowCount();
    if(categoryModel->insertRow(nbRowModel))
    {
        QModelIndex index = categoryModel->index(nbRowModel, 0);
        //nbRowModel = previous one, so if insert is OK it's new index to add
        categoryModel->setData(index, QVariant::fromValue(category));  // Not OK
        categoryModel->sort(CategoryModel::CategoryColumn::Name);
    }
}

void CategoryPage::updateList(const BookManager::Category::Category& category)
{
    auto categoryList = categoryModel->getList();
    if(auto found = std::find(categoryList.begin(), categoryList.end(), category.getId()); found != categoryList.end())
        *found = category;

    categoryModel->resetList(categoryList);
    categoryModel->sort(CategoryModel::CategoryColumn::Name);
}