#include "DatabaseManagerUT_Common.hpp"


class DatabaseManagerTest : public DatabaseManagerTestCommon
{
};

// Person
TEST_F(DatabaseManagerTest, testGetPersonVectorNoOffset)
{
    std::vector<BookManager::Entity::Person> expectedDeserializedTable{
        {1, "Jacques", "Edouard", BookManager::Entity::Role::Author},
        {2, "Charles", "Henry", BookManager::Entity::Role::Illustrator},
        {3, "Peter", "Jackson", BookManager::Entity::Role::Author},
        {4, "Richard", "Bordo", BookManager::Entity::Role::Illustrator}};
    std::vector<BookManager::Entity::Person> deserializedTable;

    deserializedTable = sut->getPersonVector(4, 0);
    expectPersonTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetPersonVectorWithOffset)
{
    std::vector<BookManager::Entity::Person> expectedDeserializedTable{
        {2, "Charles", "Henry", BookManager::Entity::Role::Illustrator},
        {3, "Peter", "Jackson", BookManager::Entity::Role::Author},
        {4, "Richard", "Bordo", BookManager::Entity::Role::Illustrator}};
    std::vector<BookManager::Entity::Person> deserializedTable;

    deserializedTable = sut->getPersonVector(3, 1);
    expectPersonTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetPersonVectorWithOffsetTooLarge)
{
    std::vector<BookManager::Entity::Person> deserializedTable;

    deserializedTable = sut->getPersonVector(10, 200);
    EXPECT_TRUE(deserializedTable.empty());
}

// Publisher
TEST_F(DatabaseManagerTest, testGetPublisherVectorNoOffset)
{
    std::vector<BookManager::Entity::Publisher> expectedDeserializedTable{
        {1, "12-25"},
        {2, "Mu"},
        {3, "Pocket"}};
    std::vector<BookManager::Entity::Publisher> deserializedTable;

    deserializedTable = sut->getPublisherVector(3, 0);
    expectIdAndName<BookManager::Entity::Publisher>(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetPublisherVectorWithOffset)
{
    std::vector<BookManager::Entity::Publisher> expectedDeserializedTable{
        {2, "Mu"},
        {3, "Pocket"}};
    std::vector<BookManager::Entity::Publisher> deserializedTable;

    deserializedTable = sut->getPublisherVector(3, 1);
    expectIdAndName<BookManager::Entity::Publisher>(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetPublisherVectorWithOffsetTooLarge)
{
    std::vector<BookManager::Entity::Publisher> deserializedTable;

    deserializedTable = sut->getPublisherVector(3, 200);
    EXPECT_TRUE(deserializedTable.empty());
}

// Category
TEST_F(DatabaseManagerTest, testGetCategoryVectorNoOffset)
{
    std::vector<BookManager::Category::Category> expectedDeserializedTable{
        {1, "Thriller"},
        {2, "Sci-Fi"},
        {3, "Fantasy"},
        {4, "Young Adult"}};
    std::vector<BookManager::Category::Category> deserializedTable;

    deserializedTable = sut->getCategoryVector(4, 0);
    expectIdAndName<BookManager::Category::Category>(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetCategoryVectorWithOffset)
{
    std::vector<BookManager::Category::Category> expectedDeserializedTable{
        {2, "Sci-Fi"},
        {3, "Fantasy"},
        {4, "Young Adult"}};
    std::vector<BookManager::Category::Category> deserializedTable;

    deserializedTable = sut->getCategoryVector(3, 1);
    expectIdAndName<BookManager::Category::Category>(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetCategoryVectorWithOffsetTooLarge)
{
    std::vector<BookManager::Category::Category> deserializedTable;

    deserializedTable = sut->getCategoryVector(3, 200);
    EXPECT_TRUE(deserializedTable.empty());
}

// Book Series
TEST_F(DatabaseManagerTest, testGetBookSerieVectorNoOffset)
{
    std::vector<BookManager::Entity::BookSerie> expectedDeserializedTable{
        {1, "Harry Potter"},
        {2, "Seigneur des Anneaux"},
        {3, "Star Wars"},
        {4, "Hunger Games"}};
    std::vector<BookManager::Entity::BookSerie> deserializedTable;

    deserializedTable = sut->getBookSerieVector(4, 0);
    expectIdAndName<BookManager::Entity::BookSerie>(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetBookSerieVectorWithOffset)
{
    std::vector<BookManager::Entity::BookSerie> expectedDeserializedTable{
        {2, "Seigneur des Anneaux"},
        {3, "Star Wars"},
        {4, "Hunger Games"}};
    std::vector<BookManager::Entity::BookSerie> deserializedTable;

    deserializedTable = sut->getBookSerieVector(3, 1);
    expectIdAndName<BookManager::Entity::BookSerie>(deserializedTable, expectedDeserializedTable);
}

TEST_F(DatabaseManagerTest, testGetBookSerieVectorWithOffsetTooLarge)
{
    std::vector<BookManager::Entity::BookSerie> deserializedTable;

    deserializedTable = sut->getBookSerieVector(3, 200);
    EXPECT_TRUE(deserializedTable.empty());
}