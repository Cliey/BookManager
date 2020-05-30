#pragma once
#include <gtest/gtest.h>
#include "Managers/Utils/TableDeserializers.hpp"
#include "Utils/DatabaseManagerTestCommon.hpp"

#include "BookAbstract/Book.hpp"
#include "EntityTypes/BookSeries.hpp"
#include "EntityTypes/Person.hpp"
#include "EntityTypes/Publisher.hpp"
#include "../../Category.hpp"


#include <vector>
#include <cstdio>

using namespace BookManager::Manager;

class TableDeserializersCommon : public ::testing::Test
{
public:

    static void SetUpTestSuite()
    {
        DatabaseManagerTestCommon::initDbTest();
    }

    TableDeserializersCommon()
    {
        std::shared_ptr<SQLite::Database> db = std::make_shared<SQLite::Database>(databasePathForTest, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        db->exec("PRAGMA foreign_keys = ON");
        sut = std::make_shared<TableDeserializers>(db);
    }

    void expectPersonTable(std::vector<BookManager::Entity::Person> deserializedTable, std::vector<BookManager::Entity::Person> expectedDeserializedTable)
    {
        ASSERT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
        for(int i = 0; i < deserializedTable.size(); i++)
        {
            expectPersonTableOneElement(deserializedTable[i], expectedDeserializedTable[i]);
        }
    }

    void expectPersonTable(std::vector<std::shared_ptr<BookManager::Entity::Person>> deserializedTable, std::vector<std::shared_ptr<BookManager::Entity::Person>> expectedDeserializedTable)
    {
        ASSERT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
        for(int i = 0; i < deserializedTable.size(); i++)
        {
            EXPECT_EQ(deserializedTable[i] == nullptr, expectedDeserializedTable[i] == nullptr);
            if(deserializedTable[i])
            {
                expectPersonTableOneElement(*deserializedTable[i], *expectedDeserializedTable[i]);
            }
        }
    }

    template<class T> void expectIdAndName(std::vector<T> deserializedTable, std::vector<T> expectedDeserializedTable)
    {
        ASSERT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
        for(int i = 0; i < deserializedTable.size(); i++)
        {
            expectOneIdAndName<T>(deserializedTable[i], expectedDeserializedTable[i]);
        }
    }

    template<class T> void expectIdAndName(std::vector<std::shared_ptr<T>> deserializedTable, std::vector<std::shared_ptr<T>> expectedDeserializedTable)
    {
        ASSERT_EQ(deserializedTable.size(), expectedDeserializedTable.size());
        for(int i = 0; i < deserializedTable.size(); i++)
        {
            expectOneIdAndName<T>(deserializedTable[i], expectedDeserializedTable[i]);
        }
    }

    template<class T> void expectOneIdAndName(T deserializedElement, T expectedDeserializedElement)
    {
        EXPECT_EQ(deserializedElement.getId(), expectedDeserializedElement.getId());
        EXPECT_EQ(deserializedElement.getName(), expectedDeserializedElement.getName());
    }

    template<class T> void expectOneIdAndName(std::shared_ptr<T> deserializedElement, std::shared_ptr<T> expectedDeserializedElement)
    {
        EXPECT_EQ(deserializedElement == nullptr, expectedDeserializedElement == nullptr);
        if(deserializedElement)
        {
            expectOneIdAndName(*deserializedElement, *expectedDeserializedElement);
        }
    }

    std::shared_ptr<TableDeserializers> sut;
private:
    void expectPersonTableOneElement(BookManager::Entity::Person deserializedElement, BookManager::Entity::Person expectedDeserializedElement)
    {
            EXPECT_EQ(deserializedElement.getId(), expectedDeserializedElement.getId());
            EXPECT_EQ(deserializedElement.getFirstName(), expectedDeserializedElement.getFirstName());
            EXPECT_EQ(deserializedElement.getLastName(), expectedDeserializedElement.getLastName());
            EXPECT_EQ(deserializedElement.getRole(), expectedDeserializedElement.getRole());
    }
};