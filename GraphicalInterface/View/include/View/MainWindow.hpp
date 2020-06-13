#pragma once
#include "../../../../Category.hpp"
#include "EntityTypes/Person.hpp"
#include "EntityTypes/BookSeries.hpp"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QTabWidget>
#include <QAction>
#include <QLineEdit>
#include "Managers/GeneralManager.hpp"
#include <memory>

class BookSeriesPage;
class CategoryPage;
class PersonPage;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void toggleSearch();
    void openSettingsWindow();
    void openCategoryDialog();
    void openCategoryDialog(const BookManager::Category::Category& categoryToEdit);
    void openAuthorDialog();
    void openAuthorDialog(const BookManager::Entity::Person& personToEdit);
    void openBookSeriesDialog();
    void openBookSeriesDialog(const BookManager::Entity::BookSeries& personToEdit);

private:
    void initToolBars();
    void initGeneralToolBar();
    QToolButton* initAddMenu();
    void initSearchToolBar();
    void initCentralZone();

    std::shared_ptr<BookManager::Manager::GeneralManager> generalManager;

    QToolBar *generalToolbar;

    QTabWidget *tabWidget;
    BookSeriesPage* bookSeriesPage;
    CategoryPage* categoryPage;
    PersonPage* personPage;

    QToolBar *searchToolbar;
    // QAction *searchAction;
    QLineEdit *searchInput;
};