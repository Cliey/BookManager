#pragma once
#include "Models/PersonModel.hpp"
#include "Managers/DatabaseManager.hpp"
#include <QWidget>
#include <memory>

class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QTableView;
class QRadioButton;
class QGroupBox;

class PersonPage : public QWidget
{
    Q_OBJECT
public:
    PersonPage(std::shared_ptr<BookManager::Manager::DatabaseManager> databaseManager, QWidget *parent = nullptr);
    void insertPerson(const BookManager::Entity::Person&);
    void updateList(const BookManager::Entity::Person& person);

private slots:
    void deletePersonsSelected();
    void setFilter();
    void openMenu(const QPoint& pos);
    void editPersonSelected();
    void editPersonSelected(QModelIndex index);

signals:
    void addPerson();
    void editPerson(const BookManager::Entity::Person&);

private:
    void initLeftPane();
    void initPersonList();
    QHBoxLayout* initLeftPaneHeader();
    QGroupBox* initFilterButton();
    void deletePersonSelected(const QModelIndex& index);
    std::vector<BookManager::Entity::Person> getPersonFromDatabase();

    std::shared_ptr<BookManager::Manager::DatabaseManager> databaseManager;

    QLabel* right;
    QVBoxLayout* leftLayout;
    PersonModel* personModel;
    QTableView* personTableView;

    QRadioButton* buttonAllFilter;
    QRadioButton* buttonAuthorFilter;
    QRadioButton* buttonIllustratorFilter;
};