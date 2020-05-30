#include <gtest/gtest.h>
#include <vector>
#include "TableDeserializersUT_Common.hpp"

using namespace BookManager::Manager;

class TableDeserializersTest : public TableDeserializersCommon
{
};

// Person
TEST_F(TableDeserializersTest, testGetPersonVectorNoOffset)
{
    std::vector<BookManager::Entity::Person> expectedDeserializedTable{
        {1, "Jacques", "Edouard", BookManager::Entity::Role::Author},
        {2, "Charles", "Henry", BookManager::Entity::Role::Illustrator},
        {3, "Peter", "Jackson", BookManager::Entity::Role::Author},
        {4, "Richard", "Bordo", BookManager::Entity::Role::Illustrator}};
    std::vector<BookManager::Entity::Person> deserializedTable;

    deserializedTable = sut->deserializePersonTable(4, 0);
    expectPersonTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(TableDeserializersTest, testGetPersonVectorWithRoleNoOffset_Author)
{
    std::vector<BookManager::Entity::Person> expectedDeserializedTable{
        {1, "Jacques", "Edouard", BookManager::Entity::Role::Author},
        {3, "Peter", "Jackson", BookManager::Entity::Role::Author}};
    std::vector<BookManager::Entity::Person> deserializedTable;

    deserializedTable = sut->deserializePersonTable(4, 0, BookManager::Entity::Role::Author);
    expectPersonTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(TableDeserializersTest, testGetPersonVectorWithRoleNoOffset_Illustrator)
{
    std::vector<BookManager::Entity::Person> expectedDeserializedTable{
        {2, "Charles", "Henry", BookManager::Entity::Role::Illustrator},
        {4, "Richard", "Bordo", BookManager::Entity::Role::Illustrator}};
    std::vector<BookManager::Entity::Person> deserializedTable;

    deserializedTable = sut->deserializePersonTable(4, 0, BookManager::Entity::Role::Illustrator);
    expectPersonTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(TableDeserializersTest, testGetPersonVectorWithRoleNoOffset_Undefined)
{
    std::vector<BookManager::Entity::Person> expectedDeserializedTable{
        {1, "Jacques", "Edouard", BookManager::Entity::Role::Author},
        {2, "Charles", "Henry", BookManager::Entity::Role::Illustrator},
        {3, "Peter", "Jackson", BookManager::Entity::Role::Author},
        {4, "Richard", "Bordo", BookManager::Entity::Role::Illustrator}};
    std::vector<BookManager::Entity::Person> deserializedTable;

    deserializedTable = sut->deserializePersonTable(4, 0, BookManager::Entity::Role::Undefined);
    expectPersonTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(TableDeserializersTest, testGetPersonVectorWithOffset)
{
    std::vector<BookManager::Entity::Person> expectedDeserializedTable{
        {2, "Charles", "Henry", BookManager::Entity::Role::Illustrator},
        {3, "Peter", "Jackson", BookManager::Entity::Role::Author},
        {4, "Richard", "Bordo", BookManager::Entity::Role::Illustrator}};
    std::vector<BookManager::Entity::Person> deserializedTable;

    deserializedTable = sut->deserializePersonTable(3, 1);
    expectPersonTable(deserializedTable, expectedDeserializedTable);
}

TEST_F(TableDeserializersTest, testGetPersonVectorWithOffsetTooLarge)
{
    std::vector<BookManager::Entity::Person> deserializedTable;

    deserializedTable = sut->deserializePersonTable(10, 200);
    EXPECT_TRUE(deserializedTable.empty());
}

// Publisher
TEST_F(TableDeserializersTest, testGetPublisherVectorNoOffset)
{
    std::vector<BookManager::Entity::Publisher> expectedDeserializedTable{
        {1, "12-25"},
        {2, "Mu"},
        {3, "Pocket"}};
    std::vector<BookManager::Entity::Publisher> deserializedTable;

    deserializedTable = sut->deserializePublisherTable(3, 0);
    expectIdAndName<BookManager::Entity::Publisher>(deserializedTable, expectedDeserializedTable);
}

TEST_F(TableDeserializersTest, testGetPublisherVectorWithOffset)
{
    std::vector<BookManager::Entity::Publisher> expectedDeserializedTable{
        {2, "Mu"},
        {3, "Pocket"}};
    std::vector<BookManager::Entity::Publisher> deserializedTable;

    deserializedTable = sut->deserializePublisherTable(3, 1);
    expectIdAndName<BookManager::Entity::Publisher>(deserializedTable, expectedDeserializedTable);
}

TEST_F(TableDeserializersTest, testGetPublisherVectorWithOffsetTooLarge)
{
    std::vector<BookManager::Entity::Publisher> deserializedTable;

    deserializedTable = sut->deserializePublisherTable(3, 200);
    EXPECT_TRUE(deserializedTable.empty());
}

// Category
TEST_F(TableDeserializersTest, testGetCategoryVectorNoOffset)
{
    std::vector<BookManager::Category::Category> expectedDeserializedTable{
        {1, "Thriller"},
        {2, "Sci-Fi"},
        {3, "Fantasy"},
        {4, "Young Adult"}};
    std::vector<BookManager::Category::Category> deserializedTable;

    deserializedTable = sut->deserializeCategoryTable(4, 0);
    expectIdAndName<BookManager::Category::Category>(deserializedTable, expectedDeserializedTable);
}

TEST_F(TableDeserializersTest, testGetCategoryVectorWithOffset)
{
    std::vector<BookManager::Category::Category> expectedDeserializedTable{
        {2, "Sci-Fi"},
        {3, "Fantasy"},
        {4, "Young Adult"}};
    std::vector<BookManager::Category::Category> deserializedTable;

    deserializedTable = sut->deserializeCategoryTable(3, 1);
    expectIdAndName<BookManager::Category::Category>(deserializedTable, expectedDeserializedTable);
}

TEST_F(TableDeserializersTest, testGetCategoryVectorWithOffsetTooLarge)
{
    std::vector<BookManager::Category::Category> deserializedTable;

    deserializedTable = sut->deserializeCategoryTable(3, 200);
    EXPECT_TRUE(deserializedTable.empty());
}

// Book Series
TEST_F(TableDeserializersTest, testGetBookSeriesVectorNoOffset)
{
    std::vector<BookManager::Entity::BookSeries> expectedDeserializedTable{
        {1, "Harry Potter"},
        {2, "Seigneur des Anneaux"},
        {3, "Star Wars"},
        {4, "Hunger Games"}};
    std::vector<BookManager::Entity::BookSeries> deserializedTable;

    deserializedTable = sut->deserializeBookSeriesTable(4, 0);
    expectIdAndName<BookManager::Entity::BookSeries>(deserializedTable, expectedDeserializedTable);
}

TEST_F(TableDeserializersTest, testGetBookSeriesVectorWithOffset)
{
    std::vector<BookManager::Entity::BookSeries> expectedDeserializedTable{
        {2, "Seigneur des Anneaux"},
        {3, "Star Wars"},
        {4, "Hunger Games"}};
    std::vector<BookManager::Entity::BookSeries> deserializedTable;

    deserializedTable = sut->deserializeBookSeriesTable(3, 1);
    expectIdAndName<BookManager::Entity::BookSeries>(deserializedTable, expectedDeserializedTable);
}

TEST_F(TableDeserializersTest, testGetBookSeriesVectorWithOffsetTooLarge)
{
    std::vector<BookManager::Entity::BookSeries> deserializedTable;

    deserializedTable = sut->deserializeBookSeriesTable(3, 200);
    EXPECT_TRUE(deserializedTable.empty());
}
