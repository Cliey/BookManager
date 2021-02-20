#pragma once
#include <gtest/gtest.h>
#include "BookAbstract/Book.hpp"
#include "EntityTypes/BookSeries.hpp"
#include "EntityTypes/Person.hpp"
#include "EntityTypes/Publisher.hpp"
#include "../../Category.hpp"


class TableDeserializerUtils : public ::testing::Test
{
protected:

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

private:
    void expectPersonTableOneElement(BookManager::Entity::Person deserializedElement, BookManager::Entity::Person expectedDeserializedElement)
    {
            EXPECT_EQ(deserializedElement.getId(), expectedDeserializedElement.getId());
            EXPECT_EQ(deserializedElement.getFirstName(), expectedDeserializedElement.getFirstName());
            EXPECT_EQ(deserializedElement.getLastName(), expectedDeserializedElement.getLastName());
            EXPECT_EQ(deserializedElement.getRole(), expectedDeserializedElement.getRole());
    }
};