#pragma once
#include "Models/CategoryModel.hpp"
#include "Managers/DatabaseManager.hpp"
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QListView>
#include <QPoint>
#include <QMenu>

class CategoryPage : public QWidget
{
    Q_OBJECT
public:
    CategoryPage(std::shared_ptr<BookManager::Manager::DatabaseManager> databaseManager, QWidget *parent = nullptr);

private slots:
    void deleteCategoriesSelected();
    void openMenu(const QPoint& pos);

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