#include "Managers/DatabaseManager.hpp"
#include "EntityTypes/Person.hpp"
#include "EntityTypes/Publisher.hpp"
#include <gtest/gtest.h>
#include <vector>

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

    void expectPersonTable(std::vector<BookManager::Entity::Person> deserializedTable, std::vector<BookManager::Entity::Person> expectedDeserializedTable)
    {
        EXPECT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
        for(int i = 0; i < deserializedTable.size(); i++)
        {
            EXPECT_EQ(deserializedTable[i].getId(), expectedDeserializedTable[i].getId());
            EXPECT_EQ(deserializedTable[i].getFirstName(), expectedDeserializedTable[i].getFirstName());
            EXPECT_EQ(deserializedTable[i].getLastName(), expectedDeserializedTable[i].getLastName());
            EXPECT_EQ(deserializedTable[i].getRole(), expectedDeserializedTable[i].getRole());
        }
    }

    void expectPublisherTable(std::vector<BookManager::Entity::Publisher> deserializedTable, std::vector<BookManager::Entity::Publisher> expectedDeserializedTable)
    {
        EXPECT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
        for(int i = 0; i < deserializedTable.size(); i++)
        {
            EXPECT_EQ(deserializedTable[i].getId(), expectedDeserializedTable[i].getId());
            EXPECT_EQ(deserializedTable[i].getName(), expectedDeserializedTable[i].getName());
        }
    }
    std::shared_ptr<DatabaseManager> sut;
};

TEST_F(DatabaseManagerTest, testDeserializePersonTableNoOffset)
{
    std::vector<BookManager::Entity::Person> expectedDeserializedTable{
        {1, "Jacques", "Edouard", BookManager::Entity::Role::Author},
        {2, "Charles", "Henry", BookManager::Entity::Role::Illustrator},
        {3, "Peter", "Jackson", BookManager::Entity::Role::Author},
        {4, "Richard", "Bordo", BookManager::Entity::Role::Illustrator}};
    std::vector<BookManager::Entity::Person> deserializedTable;
    SQLite::Database database("./data/BookManager.db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    deserializedTable = sut->deserializePersonTable(database, 4, 0);
    expectPersonTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testDeserializePersonTableWithOffset)
{
    std::vector<BookManager::Entity::Person> expectedDeserializedTable{
        {2, "Charles", "Henry", BookManager::Entity::Role::Illustrator},
        {3, "Peter", "Jackson", BookManager::Entity::Role::Author},
        {4, "Richard", "Bordo", BookManager::Entity::Role::Illustrator}};
    std::vector<BookManager::Entity::Person> deserializedTable;
    SQLite::Database database("./data/BookManager.db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    deserializedTable = sut->deserializePersonTable(database, 3, 1);
    expectPersonTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testDeserializePersonTableWithOffsetTooLarge)
{
    std::vector<BookManager::Entity::Person> deserializedTable;
    SQLite::Database database("./data/BookManager.db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    deserializedTable = sut->deserializePersonTable(database, 10, 200);
    EXPECT_TRUE(deserializedTable.empty());
}

TEST_F(DatabaseManagerTest, testDeserializePublisherTableNoOffset)
{
    std::vector<BookManager::Entity::Publisher> expectedDeserializedTable{
        {1, "12-25"},
        {2, "Mu"},
        {3, "Pocket"}};
    std::vector<BookManager::Entity::Publisher> deserializedTable;
    SQLite::Database database("./data/BookManager.db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    deserializedTable = sut->deserializePublisherTable(database, 3, 0);
    expectPublisherTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testDeserializePublisherTableWithOffset)
{
    std::vector<BookManager::Entity::Publisher> expectedDeserializedTable{
        {2, "Mu"},
        {3, "Pocket"}};
    std::vector<BookManager::Entity::Publisher> deserializedTable;
    SQLite::Database database("./data/BookManager.db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    deserializedTable = sut->deserializePublisherTable(database, 3, 1);
    expectPublisherTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testDeserializePublisherTableWithOffsetTooLarge)
{
    std::vector<BookManager::Entity::Publisher> deserializedTable;
    SQLite::Database database("./data/BookManager.db", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    deserializedTable = sut->deserializePublisherTable(database, 3, 200);
    EXPECT_TRUE(deserializedTable.empty());
}