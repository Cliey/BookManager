#pragma once
#include "Models/CategoryModel.hpp"
#include "Managers/DatabaseManager.hpp"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListView>
#include <QPoint>
#include <QMenu>

class CategoryPage : public QWidget
{
    Q_OBJECT
public:
    CategoryPage(std::shared_ptr<BookManager::Manager::DatabaseManager> databaseManager, QWidget *parent = nullptr);

    void insertCategory(const BookManager::Category::Category&);
    void updateList(const BookManager::Category::Category&);

private slots:
    void deleteCategoriesSelected();
    void openMenu(const QPoint& pos);
    void editCategorySelected();
    void editCategorySelected(QModelIndex index);

signals:
    void addCategory();
    void editCategory(const BookManager::Category::Category&);

private:
    void initLeftPane();
    void initList();
    void deleteCategorySelected(const QModelIndex& index);

    std::shared_ptr<BookManager::Manager::DatabaseManager> databaseManager;

    QLabel* right;
    QVBoxLayout* leftLayout;
    CategoryModel* categoryModel;
    QListView* categoryListView;
};