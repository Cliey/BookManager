#include <gtest/gtest.h>
#include <vector>
#include "Managers/Utils/QueryBuilder.hpp"
#include "Utils/DatabaseManagerTestCommon.hpp"
#include "Managers/Utils/SqlOperator/Comparison/IsOperator.hpp"
#include "Managers/Utils/SqlOperator/MacroSqlOperator.hpp"

using namespace BookManager::Manager;

class QueryBuilderTest : public ::testing::Test
{
public:
    QueryBuilderTest()
    {
        sut = std::make_shared<QueryBuilder>();
    }

    std::shared_ptr<QueryBuilder> sut;
};

TEST_F(QueryBuilderTest, SelectTest)
{
    std::string expectedQuery = "SELECT * FROM table";
    std::string actualQuery = sut->selectFrom("table").getQuery();
    EXPECT_EQ(expectedQuery, actualQuery);
}

TEST_F(QueryBuilderTest, LimitTest)
{
    std::string expectedQuery = "SELECT * FROM tableLimit LIMIT 10";
    std::string actualQuery = sut->selectFrom("tableLimit").limit(10).getQuery();
    EXPECT_EQ(expectedQuery, actualQuery);
}

TEST_F(QueryBuilderTest, OffsetTest)
{
    std::string expectedQuery = "SELECT * FROM tableOffset OFFSET 2";
    std::string actualQuery = sut->selectFrom("tableOffset").offset(2).getQuery();
    EXPECT_EQ(expectedQuery, actualQuery);
}

TEST_F(QueryBuilderTest, OrderByTest)
{
    std::string expectedQuery = "SELECT * FROM tableOrder ORDER BY name ASC";
    std::string actualQuery = sut->selectFrom("tableOrder").orderBy("name", QueryBuilder::Order::ASCENDANT).getQuery();
    EXPECT_EQ(expectedQuery, actualQuery);
}

TEST_F(QueryBuilderTest, WhereTestMacroSimple)
{
    std::string expectedQuery = "SELECT * FROM tableWhere WHERE name = Jean";
    std::string actualQuery = sut->selectFrom("tableWhere").where(IS("name", "Jean")).getQuery();
    std::cout << actualQuery << std::endl;
    EXPECT_EQ(expectedQuery, actualQuery);
}

TEST_F(QueryBuilderTest, WhereTestMacroComplex)
{
    std::string expectedQuery = "SELECT * FROM tableWhere WHERE name = Jean AND work <> butcher";
    std::string actualQuery = sut->selectFrom("tableWhere").where(AND(IS("name", "Jean"), IS_NOT("work", "butcher"))).getQuery();
    std::cout << actualQuery << std::endl;
    EXPECT_EQ(expectedQuery, actualQuery);
}

TEST_F(QueryBuilderTest, TwoWhereTest)
{
    std::string expectedQuery = "SELECT * FROM tableWhere WHERE name = Jean";
    std::string actualQuery = sut->selectFrom("tableWhere").where(IS("name", "Jean")).where(IS("role","writer")).getQuery();
    EXPECT_EQ(expectedQuery, actualQuery);
}
