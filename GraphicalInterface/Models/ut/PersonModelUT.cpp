#include <gtest/gtest.h>
#include "Models/PersonModel.hpp"
#include <vector>
#include <memory>
#include <QList>

class PersonModelTest : public ::testing::Test
{
public:
    PersonModelTest()
    {
        personTest = {{1, "Jacques", "Edouard", BookManager::Entity::Role::Author},
            {2, "Charles", "Henry", BookManager::Entity::Role::Illustrator},
            {3, "Peter", "Jackson", BookManager::Entity::Role::Author},
            {4, "Richard", "Bordo", BookManager::Entity::Role::Illustrator}};

        QList<BookManager::Entity::Person> personList(personTest.begin(), personTest.end());
        sut = new PersonModel(personList);
    }

    ~PersonModelTest()
    {
        delete sut;
    }

    void comparePerson(int row, BookManager::Entity::Person expectedPerson)
    {
        QModelIndex index = sut->index(row, 0);
        QVariant data = sut->data(index, PersonModel::PersonRole::PersonObject);
        ASSERT_TRUE(data.isValid());
        BookManager::Entity::Person person = data.value<BookManager::Entity::Person>();
        EXPECT_EQ(person.getFirstName(), person.getFirstName());
        EXPECT_EQ(person.getLastName(), person.getLastName());
        EXPECT_EQ(person.getRole(), person.getRole());
        EXPECT_EQ(person.getId(), person.getId());
    }

    PersonModel* sut;
    std::vector<BookManager::Entity::Person> personTest;
};

TEST_F(PersonModelTest, testInsertAndRemoveRows)
{
    EXPECT_EQ(sut->columnCount(), 2);
    EXPECT_EQ(sut->rowCount(), 4);
    EXPECT_TRUE(sut->insertRows(4, 2));
    EXPECT_EQ(sut->rowCount(), 6);
    EXPECT_TRUE(sut->removeRows(4, 2));
    EXPECT_EQ(sut->rowCount(), 4);
}

TEST_F(PersonModelTest, testGetDataPersonObject)
{
    for(int i = 0; i < personTest.size(); i++)
    {
        comparePerson(i, personTest.at(i));
    }
}

TEST_F(PersonModelTest, testGetDataPersonFirstName)
{
    for(int i = 0; i < personTest.size(); i++)
    {
        QModelIndex index = sut->index(i, 0);
        QVariant data = sut->data(index, PersonModel::PersonRole::PersonFirstName);
        ASSERT_TRUE(data.isValid());
        auto expectedPerson = personTest.at(i);
        EXPECT_EQ(data.toString().toStdString(), expectedPerson.getFirstName());
    }
}

TEST_F(PersonModelTest, testGetDataPersonLastName)
{
    for(int i = 0; i < personTest.size(); i++)
    {
        QModelIndex index = sut->index(i, 0);
        QVariant data = sut->data(index, PersonModel::PersonRole::PersonLastName);
        ASSERT_TRUE(data.isValid());
        auto expectedPerson = personTest.at(i);
        EXPECT_EQ(data.toString().toStdString(), expectedPerson.getLastName());
    }
}

TEST_F(PersonModelTest, testGetDataPersonFullName)
{
    for(int i = 0; i < personTest.size(); i++)
    {
        QModelIndex index = sut->index(i, 0);
        QVariant data = sut->data(index, PersonModel::PersonRole::PersonFullName);
        ASSERT_TRUE(data.isValid());
        auto expectedPerson = personTest.at(i);
        EXPECT_EQ(data.toString().toStdString(), expectedPerson.getFullName());
    }
}

TEST_F(PersonModelTest, testGetDataPersonRole)
{
    for(int i = 0; i < personTest.size(); i++)
    {
        QModelIndex index = sut->index(i, 0);
        QVariant data = sut->data(index, PersonModel::PersonRole::PersonRole);
        ASSERT_TRUE(data.isValid());
        auto expectedPerson = personTest.at(i);
        EXPECT_EQ(data.value<BookManager::Entity::Role>(), expectedPerson.getRole());
    }
}

TEST_F(PersonModelTest, testGetDataCategoryId)
{
    for(int i = 0; i < personTest.size(); i++)
    {
        QModelIndex index = sut->index(i, 0);
        QVariant data = sut->data(index, PersonModel::PersonRole::PersonId);
        ASSERT_TRUE(data.isValid());
        auto expectedPerson = personTest.at(i);
        EXPECT_EQ(data.toInt(), expectedPerson.getId());
    }
}

TEST_F(PersonModelTest, testGetDataNull)
{
    QModelIndex invalidIndex = sut->index(10, 0);
    QVariant data = sut->data(invalidIndex, Qt::DisplayRole);
    EXPECT_TRUE(data.isNull());

    QModelIndex validIndex = sut->index(1, 0);
    data = sut->data(validIndex, Qt::StatusTipRole);
    EXPECT_TRUE(data.isNull());

    invalidIndex = sut->index(-2, 0);
    data = sut->data(invalidIndex, Qt::DisplayRole);
    EXPECT_TRUE(data.isNull());
}

TEST_F(PersonModelTest, testFlags)
{
    QModelIndex invalidIndex = sut->index(10, 0);
    EXPECT_EQ(sut->flags(invalidIndex), Qt::ItemIsEnabled);

    QModelIndex validIndex = sut->index(1, 0);
    Qt::ItemFlags expectedValidFlag = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    EXPECT_EQ(sut->flags(validIndex), expectedValidFlag);
}

TEST_F(PersonModelTest, setDataInvalidIndex)
{
    BookManager::Entity::Person personToAdd = {5, "Hesnot", "Fake", BookManager::Entity::Role::Author};
    QModelIndex invalidIndex = sut->index(10, 0);
    EXPECT_FALSE(sut->setData(invalidIndex, QVariant::fromValue(personToAdd)));
}

TEST_F(PersonModelTest, setDataValidIndex)
{
    BookManager::Entity::Person personToAdd = {5, "Hesnot", "Fake", BookManager::Entity::Role::Author};
    EXPECT_TRUE(sut->insertRows(4, 1));
    QModelIndex validIndex = sut->index(4, 0);
    ASSERT_TRUE(sut->setData(validIndex, QVariant::fromValue(personToAdd)));
    ASSERT_EQ(sut->rowCount(), 5);
    comparePerson(4, personToAdd);
}

TEST_F(PersonModelTest, testResetList)
{
    std::vector<BookManager::Entity::Person> newPersonVector = {{1, "Jacques", "Edouard", BookManager::Entity::Role::Author},
            {3, "Peter", "Jackson", BookManager::Entity::Role::Author}};

    QList<BookManager::Entity::Person> newPersonList(newPersonVector.begin(), newPersonVector.end());

    sut->resetList(newPersonList);
    for(int i = 0; i < newPersonVector.size(); i++)
    {
        comparePerson(i, newPersonVector.at(i));
    }
}