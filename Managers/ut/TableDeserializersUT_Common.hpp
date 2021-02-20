#pragma once
#include <gtest/gtest.h>
#include "Managers/Utils/TableDeserializers.hpp"
#include "Utils/DatabaseManagerTestCommon.hpp"
#include "Utils/TableDeserializerUtils.hpp"

#include <vector>
#include <cstdio>

using namespace BookManager::Manager;

class TableDeserializersCommon : public TableDeserializerUtils
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

    std::shared_ptr<TableDeserializers> sut;
};