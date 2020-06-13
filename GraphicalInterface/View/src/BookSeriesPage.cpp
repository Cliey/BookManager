#include "View/BookSeriesPage.hpp"
#include "Utils/Exceptions.hpp"
#include <QAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QListView>
#include <QPushButton>
#include <QMessageBox>
#include <QPoint>
#include <QMenu>
#include <iostream>

BookSeriesPage::BookSeriesPage(std::shared_ptr<BookManager::Manager::DatabaseManager> databaseManager, QWidget* parent)
    : databaseManager(databaseManager), QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout();
    right =  new QLabel("Something here later");
    initLeftPane();
    layout->addLayout(leftLayout, 50);
    layout->addWidget(right, 50);

    setLayout(layout);
}

void BookSeriesPage::initLeftPane()
{
    leftLayout = new QVBoxLayout();
    initList();
    QHBoxLayout* headerLayout = new QHBoxLayout();

    QLabel* headerName = new QLabel("Book Series");
    QFont fontLabel;
    fontLabel.setPointSize(16);
    headerName->setFont(fontLabel);

    QPushButton* buttonDeleteBookSeries = new QPushButton();
    buttonDeleteBookSeries->setIcon(QIcon(":/icons/trash.png"));
    buttonDeleteBookSeries->setFixedSize(28, 28);
    buttonDeleteBookSeries->setIconSize(QSize(20, 20));
    QObject::connect(buttonDeleteBookSeries, &QPushButton::clicked, this, &BookSeriesPage::deleteBookSeriesSelected);

    headerLayout->addWidget(headerName);
    headerLayout->addWidget(buttonDeleteBookSeries);

    leftLayout->addLayout(headerLayout);
    leftLayout->addWidget(bookSeriesListView);
}

void BookSeriesPage::initList()
{
    auto bookSeriesVect = databaseManager->getBookSeriesVector(20, 0);
    QList<BookManager::Entity::BookSeries> bookSeriesList(bookSeriesVect.begin(), bookSeriesVect.end());

    bookSeriesModel = new BookSeriesModel(bookSeriesList);
    bookSeriesListView = new QListView();
    bookSeriesModel->sort(BookSeriesModel::BookSeriesColumn::Name);
    bookSeriesListView->setModel(bookSeriesModel);
    bookSeriesListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    bookSeriesListView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    bookSeriesListView->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(bookSeriesListView, &QListView::customContextMenuRequested, this, &BookSeriesPage::openMenu);
    QObject::connect(bookSeriesListView, &QListView::doubleClicked, this,  qOverload<QModelIndex>(&BookSeriesPage::editBookSeriesSelected));
}

void BookSeriesPage::deleteBookSeriesSelected()
{
    QItemSelectionModel* selection = bookSeriesListView->selectionModel();
    QModelIndexList listIndexes = selection->selectedIndexes();
    std::sort(listIndexes.rbegin(), listIndexes.rend()); // reverse iterator, greater to lower
    for(auto& index : listIndexes)
    {
        deleteOneBookSeriesSelected(index);
    }
}

void BookSeriesPage::deleteOneBookSeriesSelected(const QModelIndex& index)
{
    auto bookSeries = bookSeriesModel->data(index, BookSeriesModel::BookSeriesRole::BookSeriesObject).value<BookManager::Entity::BookSeries>();
    try
    {
        databaseManager->deleteBookSeries(bookSeries.getId(), false);
        bookSeriesModel->removeRow(index.row());
        return;
    }
    catch(const Utils::Exceptions::EC_ForeignKeyFound& e)
    {
        auto response = QMessageBox::critical(this, "Error deleting Book Series" , e.getStr(), QMessageBox::Yes | QMessageBox::No);
        if(response == QMessageBox::Yes)
        {
            e.executeCallback();
            bookSeriesModel->removeRow(index.row());
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void BookSeriesPage::openMenu(const QPoint& pos)
{
    // Idea of the contextMenu
    QMenu menuItem;
    QAction* actionAdd = menuItem.addAction(tr("Add book series", "Add a book series"));
    QObject::connect(actionAdd, &QAction::triggered, [this](){ emit addBookSeries(); });
    QAction* actionEdit = menuItem.addAction(tr("Edit book series", "Edit a book series"));
    QObject::connect(actionEdit, &QAction::triggered, this,  qOverload<>(&editBookSeriesSelected));
    QAction* actionSearchBook = menuItem.addAction(tr("Search books", "Search book with the selected book series"));
    QAction* actionCopyBookSeriesName = menuItem.addAction(tr("Copy Name", "Copy book series name"));

    QModelIndex pointedItem = bookSeriesListView->indexAt(pos);
    QAction* selectedAction;
    if(pointedItem.isValid())
    {
        selectedAction = menuItem.exec(QCursor::pos());
        return;
    }
    actionSearchBook->setEnabled(false);
    actionEdit->setEnabled(false);
    actionCopyBookSeriesName->setEnabled(false);
    selectedAction = menuItem.exec(QCursor::pos());
    return;
}

void BookSeriesPage::editBookSeriesSelected()
{
    QItemSelectionModel *selection = bookSeriesListView->selectionModel();
    QModelIndex index = selection->currentIndex();
    editBookSeriesSelected(index);
}

void BookSeriesPage::editBookSeriesSelected(QModelIndex index)
{
    auto bookSeries = bookSeriesModel->data(index, BookSeriesModel::BookSeriesRole::BookSeriesObject).value<BookManager::Entity::BookSeries>();
    emit editBookSeries(bookSeries);
}

void BookSeriesPage::insertBookSeries(const BookManager::Entity::BookSeries& bookSeries)
{
    int nbRowModel = bookSeriesModel->rowCount();
    if(bookSeriesModel->insertRow(nbRowModel))
    {
        QModelIndex index = bookSeriesModel->index(nbRowModel, 0);
        //nbRowModel = previous one, so if insert is OK it's new index to add
        bookSeriesModel->setData(index, QVariant::fromValue(bookSeries));
        bookSeriesModel->sort(BookSeriesModel::BookSeriesColumn::Name);
    }
}

void BookSeriesPage::updateList(const BookManager::Entity::BookSeries& bookSeries)
{
    auto bookSeriesList = bookSeriesModel->getList();
    if(auto found = std::find(bookSeriesList.begin(), bookSeriesList.end(), bookSeries.getId()); found != bookSeriesList.end())
        *found = bookSeries;

    bookSeriesModel->resetList(bookSeriesList);
    bookSeriesModel->sort(BookSeriesModel::BookSeriesColumn::Name);
}