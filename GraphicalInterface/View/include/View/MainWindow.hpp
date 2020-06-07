#pragma once
#include "../../../../Category.hpp"
#include "EntityTypes/Person.hpp"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QTabWidget>
#include <QAction>
#include <QLineEdit>
#include "Managers/GeneralManager.hpp"
#include <memory>

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

private:
    void initToolBars();
    void initGeneralToolBar();
    QToolButton* initAddMenu();
    void initSearchToolBar();
    void initCentralZone();

    std::shared_ptr<BookManager::Manager::GeneralManager> generalManager;

    QToolBar *generalToolbar;

    QTabWidget *tabWidget;
    CategoryPage* categoryPage;
    PersonPage* personPage;

    QToolBar *searchToolbar;
    // QAction *searchAction;
    QLineEdit *searchInput;
};