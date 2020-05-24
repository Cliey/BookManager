#include "View/MainWindow.hpp"
#include "View/BookPage.hpp"
#include "View/CategoryPage.hpp"
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
    QAction* actionAddBookSerie = new QAction(tr("Add Book &Serie"), this);
    QAction* actionAddAuthor = new QAction(tr("Add &Author"), this);
    QAction* actionAddCategory = new QAction(tr("Add &Category"), this);
    menuAdd->addAction(actionAddBook);
    menuAdd->addAction(actionAddBookSerie);
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
    CategoryPage* categoryPage = new CategoryPage();
    tabWidget = new QTabWidget();
    tabWidget->addTab(bookPage, "Book");
    tabWidget->addTab(categoryPage, "Category");

    tabWidget->setTabPosition(QTabWidget::TabPosition::West);
    this->setCentralWidget(tabWidget);
}

void MainWindow::toggleSearch()
{
    searchToolbar->setVisible(!searchToolbar->isVisible());
}