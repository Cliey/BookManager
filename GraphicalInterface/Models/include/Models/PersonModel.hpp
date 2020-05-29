#pragma once
#include <QAbstractTableModel>
#include <QList>
#include <QModelIndex>
#include <QVariant>
#include <Qt>
#include "EntityTypes/Person.hpp"
#include "EntityEnum/Role.hpp"


Q_DECLARE_METATYPE(BookManager::Entity::Person)
Q_DECLARE_METATYPE(BookManager::Entity::Role)


class PersonModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum PersonRole {
        PersonObject = Qt::UserRole +1,
        PersonId,
        PersonFirstName,
        PersonLastName,
        PersonFullName,
        PersonRole
    };

    PersonModel(const QList<BookManager::Entity::Person> &persons, QObject *parent = nullptr)
        :  QAbstractTableModel(parent), personList(persons) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index = QModelIndex()) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    void sort(int column,  Qt::SortOrder order = Qt::AscendingOrder) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

public slots:
    void resetList(QList<BookManager::Entity::Person> newPersonList);

private:
    QList<BookManager::Entity::Person> personList;
};