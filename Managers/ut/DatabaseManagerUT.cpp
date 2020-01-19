#include "Managers/DatabaseManager.hpp"
#include <gtest/gtest.h>

using namespace BookManager::Manager;

class DatabaseManagerTest : public ::testing::Test
{
public:
    DatabaseManagerTest()
    {
        sut = DatabaseManager::getDbManager();
    }

    // std::string getLogMessage(std::string logOutput)
    // {
    //     return (strrchr(logOutput.c_str(), '-') + 2);
    // }

    std::shared_ptr<DatabaseManager> sut;
};

TEST_F(DatabaseManagerTest, testLoad)
{
    SQLite::Database database("./data/BookManager.db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    sut->deserializePersonTable(database, 2, 0);
}

