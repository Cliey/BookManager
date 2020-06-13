#pragma once
#include "Models/BookSeriesModel.hpp"
#include "Managers/DatabaseManager.hpp"
#include <QWidget>

class QLabel;
class QVBoxLayout;
class QListView;
class QPoint;

class BookSeriesPage : public QWidget
{
    Q_OBJECT
public:
    BookSeriesPage(std::shared_ptr<BookManager::Manager::DatabaseManager> databaseManager, QWidget* parent = nullptr);

    void insertBookSeries(const BookManager::Entity::BookSeries&);
    void updateList(const BookManager::Entity::BookSeries&);

private slots:
    void deleteBookSeriesSelected();
    void openMenu(const QPoint& pos);
    void editBookSeriesSelected();
    void editBookSeriesSelected(QModelIndex index);

signals:
    void addBookSeries();
    void editBookSeries(const BookManager::Entity::BookSeries&);

private:
    void initLeftPane();
    void initList();
    void deleteOneBookSeriesSelected(const QModelIndex& index);

    std::shared_ptr<BookManager::Manager::DatabaseManager> databaseManager;

    QLabel* right;
    QVBoxLayout* leftLayout;
    BookSeriesModel* bookSeriesModel;
    QListView* bookSeriesListView;
};

