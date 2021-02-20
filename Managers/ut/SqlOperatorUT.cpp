#include <gtest/gtest.h>
#include <memory>
#include "Managers/Utils/SqlOperator/Logical/AndOperator.hpp"
#include "Managers/Utils/SqlOperator/Logical/OrOperator.hpp"
#include "Managers/Utils/SqlOperator/Logical/InOperator.hpp"
#include "Managers/Utils/SqlOperator/Logical/BetweenOperator.hpp"
#include "Managers/Utils/SqlOperator/Logical/NotOperator.hpp"
#include "Managers/Utils/SqlOperator/Comparison/IsOperator.hpp"
#include "Managers/Utils/SqlOperator/Comparison/LessThanOperator.hpp"
#include "Managers/Utils/SqlOperator/WhereOperator.hpp"
#include "Managers/Utils/SqlOperator/MacroSqlOperator.hpp"
#include <any>
#include <vector>

using namespace BookManager::Manager::SqlOperator;
class SqlOperatorUT : public ::testing::Test
{
protected:

};

TEST_F(SqlOperatorUT, testAndOperatorWith_String_Int)
{
    std::shared_ptr<IsOperator<std::string>> is = std::make_shared<IsOperator<std::string>>("name", "Jean");
    std::shared_ptr<LessThanOperator<int>> less = std::make_shared<LessThanOperator<int>>("salary", 5000);
    AndOperator andOperator(is, less);
    EXPECT_EQ("name = Jean AND salary < 5000", andOperator());

}

TEST_F(SqlOperatorUT, testOrOperatorWith_String_Int)
{
    std::shared_ptr<IsOperator<std::string>> is = std::make_shared<IsOperator<std::string>>("name", "Jean");
    std::shared_ptr<LessThanOperator<int>> less = std::make_shared<LessThanOperator<int>>("salary", 5000);
    OrOperator orOperator(is, less);
    EXPECT_EQ("name = Jean OR salary < 5000", orOperator());

}

TEST_F(SqlOperatorUT, testInOperator_String)
{
    std::vector<std::string> vectorTest = {"first", "second"};
    InOperator<std::string> inOperator("field", vectorTest);
    EXPECT_EQ("field IN (first, second)", inOperator());
}

TEST_F(SqlOperatorUT, testInOperator_Int)
{
    std::vector<int> vectorTest = {5, 10, 20};
    InOperator<int> inOperator("price", vectorTest);
    EXPECT_EQ("price IN (5, 10, 20)", inOperator());
}

TEST_F(SqlOperatorUT, testBetweenOperator_String)
{
    std::vector<std::string> vectorTest = {"first", "second"};
    BetweenOperator<std::string> betweenOperator("field", "value1", "value2");
    EXPECT_EQ("field BETWEEN value1 AND value2", betweenOperator());
}

TEST_F(SqlOperatorUT, testBetweenOperator_Int)
{
    BetweenOperator<int> betweenOperator("price", 5, 20);
    EXPECT_EQ("price BETWEEN 5 AND 20", betweenOperator());
}


TEST_F(SqlOperatorUT, testNotOperator)
{
    std::shared_ptr<IsOperator<std::string>> is = std::make_shared<IsOperator<std::string>>("name", "Jean");
    NotOperator notOperator(is);
    EXPECT_EQ("NOT (name = Jean)", notOperator());
}

TEST_F(SqlOperatorUT, testLikeOperator)
{
    LikeOperator<int> likeOperatorInt("price", 5);
    EXPECT_EQ("price LIKE 5", likeOperatorInt());

    LikeOperator<std::string> likeOperatorString("name", "Jean-%");
    EXPECT_EQ("name LIKE Jean-%", likeOperatorString());
}

TEST_F(SqlOperatorUT, testWhereOperatorWithComparisionOperator)
{
    std::shared_ptr<IsOperator<std::string>> is = std::make_shared<IsOperator<std::string>>("name", "Jean");
    WhereOperator whereOperator(is);
    EXPECT_EQ("WHERE name = Jean", whereOperator.get());
}

TEST_F(SqlOperatorUT, testWhereOperatorWithLogicalOperator)
{
    std::shared_ptr<IsOperator<std::string>> is = std::make_shared<IsOperator<std::string>>("name", "Jean");
    std::shared_ptr<LessThanOperator<int>> less = std::make_shared<LessThanOperator<int>>("salary", 5000);
    std::shared_ptr<AndOperator> andOperator = std::make_shared<AndOperator>(is, less);
    WhereOperator whereOperator(andOperator);
    EXPECT_EQ("WHERE name = Jean AND salary < 5000", whereOperator.get());
}

TEST_F(SqlOperatorUT, testWhereComparisonOperatorWithMacro)
{
    WhereOperator whereIS(IS("name", "Jean"));
    EXPECT_EQ("WHERE name = Jean", whereIS.get());
    WhereOperator whereIS_NOT(IS_NOT("name", "Jean"));
    EXPECT_EQ("WHERE name <> Jean", whereIS_NOT.get());

    WhereOperator whereLT(LT("salary", 2000));
    EXPECT_EQ("WHERE salary < 2000", whereLT.get());
    WhereOperator whereLTE(LTE("salary", 2000));
    EXPECT_EQ("WHERE salary <= 2000", whereLTE.get());


    WhereOperator whereGT(GT("price", 10.5));
    EXPECT_EQ("WHERE price > 10.5", whereGT.get());
    WhereOperator whereGTE(GTE("price", 10.5));
    EXPECT_EQ("WHERE price >= 10.5", whereGTE.get());

    WhereOperator whereLikeStr(LIKE("field", "value"));
    EXPECT_EQ("WHERE field LIKE value", whereLikeStr.get());
}

TEST_F(SqlOperatorUT, testWhereLogicalOperatorWithMacro)
{
    WhereOperator whereAND(AND(IS("name", "Jean"), LT("salary", 2000)));
    EXPECT_EQ("WHERE name = Jean AND salary < 2000", whereAND.get());
    WhereOperator whereOR(OR(IS("name", "Jean"), IS("name", "Bob")));
    EXPECT_EQ("WHERE name = Jean OR name = Bob", whereOR.get());

    WhereOperator whereBETWEEN(BETWEEN("price", 10, 20));
    EXPECT_EQ("WHERE price BETWEEN 10 AND 20", whereBETWEEN.get());
    WhereOperator whereNOT(NOT(IS("name", "Bob")));
    EXPECT_EQ("WHERE NOT (name = Bob)", whereNOT.get());

    std::vector<std::string> vectorTestStr = {"first", "second"};
    WhereOperator whereINStr(IN("field", vectorTestStr));
    EXPECT_EQ("WHERE field IN (first, second)", whereINStr.get());
    std::vector<int> vectorTestInt = {5, 10, 20};
    WhereOperator whereINInt(IN("price", vectorTestInt));
    EXPECT_EQ("WHERE price IN (5, 10, 20)", whereINInt.get());
}

TEST_F(SqlOperatorUT, testWhereOperatorWithComplexOperator)
{
    WhereOperator whereComplex(OR(
        AND(IS("name", "Jean"), LT("salary", 2000)),
        AND(IS("name", "Bob"), GT("salary", 2300))));
    EXPECT_EQ("WHERE ((name = Jean AND salary < 2000) OR (name = Bob AND salary > 2300))", whereComplex.get());
}