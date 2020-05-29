#pragma once
#include "Models/PersonModel.hpp"
#include "Managers/DatabaseManager.hpp"
#include <QWidget>
#include <memory>

class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QTableView;

class PersonPage : public QWidget
{
    Q_OBJECT
public:
    PersonPage(std::shared_ptr<BookManager::Manager::DatabaseManager> databaseManager, QWidget *parent = nullptr);

private slots:
    void deletePersonsSelected();

private:
    void initLeftPane();
    void initPersonList();
    QHBoxLayout* initLeftPaneHeader();
    QHBoxLayout* initFilterButton();
    void deletePersonSelected(const QModelIndex& index);



    std::shared_ptr<BookManager::Manager::DatabaseManager> databaseManager;

    QLabel* right;
    QVBoxLayout* leftLayout;
    PersonModel* personModel;
    QTableView* personTableView;
};