#include <gtest/gtest.h>
#include "Models/CategoryModel.hpp"
#include <vector>
#include <memory>
#include <QList>

class CategoryModelTest : public ::testing::Test
{
public:
    CategoryModelTest()
    {
        categoryTest = {
            {1, "Thriller"},
            {2, "Sci-Fi"},
            {3, "Fantasy"},
            {4, "Young Adult"}};

        QList<BookManager::Category::Category> categoryList(categoryTest.begin(), categoryTest.end());
        sut = new CategoryModel(categoryList);
    }

    ~CategoryModelTest()
    {
        delete sut;
    }

    void compareCategory(int row, BookManager::Category::Category expectedCategory)
    {
        QModelIndex index = sut->index(row, 0);
        QVariant data = sut->data(index, CategoryModel::CategoryRole::CategoryObject);
        ASSERT_TRUE(data.isValid());
        BookManager::Category::Category category = data.value<BookManager::Category::Category>();
        EXPECT_EQ(category.getName(), expectedCategory.getName());
        EXPECT_EQ(category.getId(), expectedCategory.getId());
    }

    CategoryModel* sut;
    std::vector<BookManager::Category::Category> categoryTest;
};

TEST_F(CategoryModelTest, testInsertAndRemoveRows)
{
    EXPECT_EQ(sut->columnCount(), 2);
    EXPECT_EQ(sut->rowCount(), 4);
    EXPECT_TRUE(sut->insertRows(4, 2));
    EXPECT_EQ(sut->rowCount(), 6);
    EXPECT_TRUE(sut->removeRows(4, 2));
    EXPECT_EQ(sut->rowCount(), 4);
    // print list
    for(int i = 0; i < 4; i++)
    {
        QModelIndex index = sut->index(i, 0);
        std::cout << sut->data(index, Qt::DisplayRole).toString().toStdString() << std::endl;
    }
}

TEST_F(CategoryModelTest, testGetDataCategoryObject)
{
    for(int i = 0; i < categoryTest.size(); i++)
    {
        compareCategory(i, categoryTest.at(i));
    }
}

TEST_F(CategoryModelTest, testGetDataCategoryName)
{
    for(int i = 0; i < categoryTest.size(); i++)
    {
        QModelIndex index = sut->index(i, 0);
        QVariant data = sut->data(index, CategoryModel::CategoryRole::CategoryName);
        ASSERT_TRUE(data.isValid());
        auto expectedCategory = categoryTest.at(i);
        EXPECT_EQ(data.toString().toStdString(), expectedCategory.getName());
    }
}

TEST_F(CategoryModelTest, testGetDataCategoryId)
{
    for(int i = 0; i < categoryTest.size(); i++)
    {
        QModelIndex index = sut->index(i, 0);
        QVariant data = sut->data(index, CategoryModel::CategoryRole::CategoryId);
        ASSERT_TRUE(data.isValid());
        auto expectedCategory = categoryTest.at(i);
        EXPECT_EQ(data.toInt(), expectedCategory.getId());
    }
}
TEST_F(CategoryModelTest, testGetDataNull)
{
    QModelIndex invalidIndex = sut->index(10, 0);
    QVariant data = sut->data(invalidIndex, Qt::DisplayRole);
    EXPECT_TRUE(data.isNull());

    QModelIndex validIndex = sut->index(1, 0);
    data = sut->data(validIndex, Qt::StatusTipRole);
    EXPECT_TRUE(data.isNull());
}

TEST_F(CategoryModelTest, testFlags)
{
    QModelIndex invalidIndex = sut->index(10, 0);
    EXPECT_EQ(sut->flags(invalidIndex), Qt::ItemIsEnabled);

    QModelIndex validIndex = sut->index(1, 0);
    Qt::ItemFlags expectedValidFlag = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    EXPECT_EQ(sut->flags(validIndex), expectedValidFlag);
}

TEST_F(CategoryModelTest, setDataInvalidIndex)
{
    BookManager::Category::Category categoryToAdd = {5, "Romance"};
    QModelIndex invalidIndex = sut->index(10, 0);
    EXPECT_FALSE(sut->setData(invalidIndex, QVariant::fromValue(categoryToAdd)));
}

TEST_F(CategoryModelTest, setDataValidIndex)
{
    BookManager::Category::Category categoryToAdd = {5, "Romance"};
    EXPECT_TRUE(sut->insertRows(4, 1));
    QModelIndex validIndex = sut->index(4, 0);
    ASSERT_TRUE(sut->setData(validIndex, QVariant::fromValue(categoryToAdd)));
    ASSERT_EQ(sut->rowCount(), 5);
    compareCategory(4, categoryToAdd);
}