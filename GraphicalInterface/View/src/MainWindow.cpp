#include "View/MainWindow.hpp"
#include "View/BookPage.hpp"
#include "View/CategoryPage.hpp"
#include "View/PersonPage.hpp"
#include "Popup/CategoryDialog.hpp"
#include "Popup/SettingsDialog.hpp"
#include <QToolButton>
#include <QAction>
#include <QMenu>
#include <QIcon>
#include <QWidget>
#include <QResource>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QShortcut>
#include <QKeySequence>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    generalManager = std::make_shared<BookManager::Manager::GeneralManager>();
    generalManager->startApp();
    Q_INIT_RESOURCE(resource);
    setWindowTitle(tr("BookManager"));
    initToolBars();
    initCentralZone();
}

void MainWindow::initToolBars()
{
    initGeneralToolBar();
    initSearchToolBar();
}

void MainWindow::initGeneralToolBar()
{
    QToolButton* toolButtonAdd = initAddMenu();

    QAction* actionSettings = new QAction(tr("Settings"), this);
    actionSettings->setIcon(QIcon(":/icons/settings.jpg"));
    QObject::connect(actionSettings, &QAction::triggered, this, &MainWindow::openSettingsWindow);

    QAction* actionExit = new QAction(tr("&Exit"), this);
    actionExit->setIcon(QIcon(":/icons/exit.jpg"));
    QObject::connect(actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));


    generalToolbar = addToolBar("File");
    generalToolbar->addWidget(toolButtonAdd);
    generalToolbar->addAction(actionSettings);
    generalToolbar->addAction(actionExit);
    generalToolbar->addSeparator();

    generalToolbar->setFloatable(false);
    generalToolbar->setMovable(false);
    generalToolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

QToolButton* MainWindow::initAddMenu()
{
    QMenu* menuAdd = new QMenu(tr("Add"));
    QAction* actionAddBook = new QAction(tr("Add &Book"), this);
    QAction* actionAddBookSeries = new QAction(tr("Add Book &Serie"), this);
    QAction* actionAddAuthor = new QAction(tr("Add &Author"), this);
    QAction* actionAddCategory = new QAction(tr("Add &Category"), this);
    QObject::connect(actionAddCategory, &QAction::triggered, this, qOverload<>(&MainWindow::openCategoryDialog));
    menuAdd->addAction(actionAddBook);
    menuAdd->addAction(actionAddBookSeries);
    menuAdd->addAction(actionAddAuthor);
    menuAdd->addAction(actionAddCategory);

    QToolButton* toolButtonAdd = new QToolButton();
    toolButtonAdd->setText(tr("Add..."));
    // Default action by clicking on the icon :
    // If TabMenu is book : addBook, if category addCategory etc..
    toolButtonAdd->setIcon(QIcon(":/icons/add.jpg"));
    toolButtonAdd->setMenu(menuAdd);
    toolButtonAdd->setPopupMode(QToolButton::MenuButtonPopup);
    toolButtonAdd->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    return toolButtonAdd;
}

void MainWindow::openSettingsWindow()
{
    SettingsDialog settingDialog(generalManager->getSettingsManager(), this);
    settingDialog.exec();
}

void MainWindow::openCategoryDialog()
{
    CategoryDialog* categoryDialog = new CategoryDialog(this);
    QObject::connect(categoryDialog, &CategoryDialog::accepted,
        [this](const BookManager::Category::Category& category){
            auto [addSuccess, newId] = generalManager->getDatabaseManager()->insertCategory(category);
            BookManager::Category::Category categoryWithNewId(newId, category.getName());
            categoryPage->insertCategory(categoryWithNewId);
        });
    categoryDialog->exec();
}

void MainWindow::openCategoryDialog(const BookManager::Category::Category& categoryToEdit)
{
    CategoryDialog* categoryDialog = new CategoryDialog(categoryToEdit, this);
    QObject::connect(categoryDialog, &CategoryDialog::accepted,
        [this](const BookManager::Category::Category& category){
            generalManager->getDatabaseManager()->updateCategory(category);
            categoryPage->updateList(category);
        });
    categoryDialog->exec();
}

void MainWindow::initSearchToolBar()
{
    searchToolbar = addToolBar("Search");
    QWidget* searchWidget = new QWidget();
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchInput = new QLineEdit();
    searchInput->setPlaceholderText("Search...");
    QPushButton* searchButton = new QPushButton("Ok");
    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(searchButton);
    searchWidget->setLayout(searchLayout);
    searchToolbar->addWidget(searchWidget);
    searchToolbar->setVisible(false);
    searchToolbar->setFloatable(false);
    searchToolbar->setMovable(false);

    QShortcut* shortcut = new QShortcut(QKeySequence(tr("Ctrl+F", "Search")), this);
    QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(toggleSearch()));
}

void MainWindow::initCentralZone()
{
    BookPage* bookPage = new BookPage();
    categoryPage = new CategoryPage(generalManager->getDatabaseManager());
    PersonPage* personPage = new PersonPage(generalManager->getDatabaseManager());
    tabWidget = new QTabWidget();
    tabWidget->addTab(bookPage, "Book");
    tabWidget->addTab(categoryPage, "Category");
    QObject::connect(categoryPage, &CategoryPage::addCategory, this, qOverload<>(&MainWindow::openCategoryDialog));
    QObject::connect(categoryPage, &CategoryPage::editCategory, this, qOverload<const BookManager::Category::Category&>(&MainWindow::openCategoryDialog));
    tabWidget->addTab(personPage, "Author");

    tabWidget->setTabPosition(QTabWidget::TabPosition::West);
    this->setCentralWidget(tabWidget);
}

void MainWindow::toggleSearch()
{
    searchToolbar->setVisible(!searchToolbar->isVisible());
}