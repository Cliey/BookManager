#include "GraphicalInterface/MainWindow.hpp"
#include "GraphicalInterface/BookPage.hpp"
#include <QToolButton>
#include <QAction>
#include <QMenu>
#include <QIcon>
#include <QWidget>

MainWindow::MainWindow()
{
    setToolBar();
    setCentralZone();

}

void MainWindow::setToolBar()
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
    // action : if TabMenu is book : addBook, if category addCategory etc..
    toolButtonAdd->setIcon(QIcon("icons/addIcon.jpg"));
    toolButtonAdd->setMenu(menuAdd);
    toolButtonAdd->setPopupMode(QToolButton::MenuButtonPopup);
    toolButtonAdd->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    QAction* actionExit = new QAction(tr("&Exit"), this);
    QObject::connect(actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));

    QToolBar *generalToolbar = addToolBar("File");
    generalToolbar->addWidget(toolButtonAdd);
    generalToolbar->addSeparator();
    generalToolbar->addAction(actionExit);

    generalToolbar->setFloatable(false);
    generalToolbar->setMovable(false);
}

void MainWindow::setCentralZone()
{
    tabWidget = new QTabWidget();

    BookPage* bookPage = new BookPage();
    tabWidget->addTab(bookPage, "Book");
    tabWidget->setTabPosition(QTabWidget::TabPosition::West);

    this->setCentralWidget(tabWidget);
}