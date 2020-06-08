#include <gtest/gtest.h>
#include "Models/BookSeriesModel.hpp"
#include <vector>
#include <memory>
#include <QList>

class BookSeriesModelTest : public ::testing::Test
{
public:
    BookSeriesModelTest()
    {
        bookSeriesTest = {
            {1, "Harry Potter"},
            {2, "Star Wars"},
            {3, "Twilight"},
            {4, "Narnia"}};

        QList<BookManager::Entity::BookSeries> bookSeriesList(bookSeriesTest.begin(), bookSeriesTest.end());
        sut = new BookSeriesModel(bookSeriesList);
    }

    ~BookSeriesModelTest()
    {
        delete sut;
    }

    void compareBookSeries(int row, BookManager::Entity::BookSeries expectedBookSeries)
    {
        QModelIndex index = sut->index(row, 0);
        QVariant data = sut->data(index, BookSeriesModel::BookSeriesRole::BookSeriesObject);
        ASSERT_TRUE(data.isValid());
        BookManager::Entity::BookSeries bookSeries = data.value<BookManager::Entity::BookSeries>();
        EXPECT_EQ(bookSeries.getName(), expectedBookSeries.getName());
        EXPECT_EQ(bookSeries.getId(), expectedBookSeries.getId());
    }

    BookSeriesModel* sut;
    std::vector<BookManager::Entity::BookSeries> bookSeriesTest;
};

TEST_F(BookSeriesModelTest, testInsertAndRemoveRows)
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

TEST_F(BookSeriesModelTest, testGetDataBookSeriesObject)
{
    for(int i = 0; i < bookSeriesTest.size(); i++)
    {
        compareBookSeries(i, bookSeriesTest.at(i));
    }
}

TEST_F(BookSeriesModelTest, testGetDataBookSeriesName)
{
    for(int i = 0; i < bookSeriesTest.size(); i++)
    {
        QModelIndex index = sut->index(i, 0);
        QVariant data = sut->data(index, BookSeriesModel::BookSeriesRole::BookSeriesName);
        ASSERT_TRUE(data.isValid());
        auto expectedBookSeries = bookSeriesTest.at(i);
        EXPECT_EQ(data.toString().toStdString(), expectedBookSeries.getName());
    }
}

TEST_F(BookSeriesModelTest, testGetDataBookSeriesId)
{
    for(int i = 0; i < bookSeriesTest.size(); i++)
    {
        QModelIndex index = sut->index(i, 0);
        QVariant data = sut->data(index, BookSeriesModel::BookSeriesRole::BookSeriesId);
        ASSERT_TRUE(data.isValid());
        auto expectedBookSeries = bookSeriesTest.at(i);
        EXPECT_EQ(data.toInt(), expectedBookSeries.getId());
    }
}
TEST_F(BookSeriesModelTest, testGetDataNull)
{
    QModelIndex invalidIndex = sut->index(10, 0);
    QVariant data = sut->data(invalidIndex, Qt::DisplayRole);
    EXPECT_TRUE(data.isNull());

    QModelIndex validIndex = sut->index(1, 0);
    data = sut->data(validIndex, Qt::StatusTipRole);
    EXPECT_TRUE(data.isNull());
}

TEST_F(BookSeriesModelTest, testFlags)
{
    QModelIndex invalidIndex = sut->index(10, 0);
    EXPECT_EQ(sut->flags(invalidIndex), Qt::ItemIsEnabled);

    QModelIndex validIndex = sut->index(1, 0);
    Qt::ItemFlags expectedValidFlag = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    EXPECT_EQ(sut->flags(validIndex), expectedValidFlag);
}

TEST_F(BookSeriesModelTest, setDataInvalidIndex)
{
    BookManager::Entity::BookSeries bookSeriesToAdd = {5, "Asterix"};
    QModelIndex invalidIndex = sut->index(10, 0);
    EXPECT_FALSE(sut->setData(invalidIndex, QVariant::fromValue(bookSeriesToAdd)));
}

TEST_F(BookSeriesModelTest, setDataValidIndex)
{
    BookManager::Entity::BookSeries bookSeriesToAdd = {5, "Asterix"};
    EXPECT_TRUE(sut->insertRows(4, 1));
    QModelIndex validIndex = sut->index(4, 0);
    ASSERT_TRUE(sut->setData(validIndex, QVariant::fromValue(bookSeriesToAdd)));
    ASSERT_EQ(sut->rowCount(), 5);
    compareBookSeries(4, bookSeriesToAdd);
}