#pragma once
#include "EntityTypes/BookSeries.hpp"
#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>
#include <QVariant>
#include <Qt>


Q_DECLARE_METATYPE(BookManager::Entity::BookSeries)

class BookSeriesModel : public QAbstractListModel
{
public:

    enum BookSeriesRole {
        BookSeriesObject = Qt::UserRole + 1,
        BookSeriesId,
        BookSeriesName
    };

    enum BookSeriesColumn {
        Name = 0
    };

    BookSeriesModel(const QList<BookManager::Entity::BookSeries> &categories, QObject *parent = nullptr)
        : QAbstractListModel(parent), bookSeriesList(categories) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index = QModelIndex()) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;
    void resetList(const QList<BookManager::Entity::BookSeries> &newCategories);

    QList<BookManager::Entity::BookSeries> getList();

private:
    QList<BookManager::Entity::BookSeries> bookSeriesList;
};