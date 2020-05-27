#pragma once
#include "Models/PersonModel.hpp"
#include "Managers/DatabaseManager.hpp"
#include <QWidget>
#include <memory>

class QTableWidget;
class QLabel;
class QVBoxLayout;

class PersonPage : public QWidget
{
public:
    PersonPage(std::shared_ptr<BookManager::Manager::DatabaseManager> databaseManager, QWidget *parent = nullptr);


private:
    void initLeftPane();


    std::shared_ptr<BookManager::Manager::DatabaseManager> databaseManager;

    QLabel* right;
    QVBoxLayout* leftLayout;
    PersonModel* personModel;
};