#include "Models/BookSeriesModel.hpp"
#include <iostream>
#include <QString>

int BookSeriesModel::rowCount(const QModelIndex &parent) const
{
    return bookSeriesList.count();
}

int BookSeriesModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant BookSeriesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(index.row() >= bookSeriesList.size())
        return QVariant();
    switch(role)
    {
        case BookSeriesRole::BookSeriesName:
        case Qt::DisplayRole:
        case Qt::EditRole:
            return QString::fromStdString(bookSeriesList.at(index.row()).getName());
        case BookSeriesRole::BookSeriesId:
            return bookSeriesList.at(index.row()).getId();
        case BookSeriesRole::BookSeriesObject:
            return QVariant::fromValue(bookSeriesList.at(index.row()));
        default:
            return QVariant();
    }
}

Qt::ItemFlags BookSeriesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool BookSeriesModel::setData(
        const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        bookSeriesList.replace(index.row(), value.value<BookManager::Entity::BookSeries>());
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

bool BookSeriesModel::insertRows(int position, int rows, const QModelIndex&)
{
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for(int row = 0; row < rows; row++)
    {
        bookSeriesList.insert(position, BookManager::Entity::BookSeries());
    }
    endInsertRows();
    return true;
}

bool  BookSeriesModel::removeRows(int position, int rows, const QModelIndex&)
{
    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    for(int row = 0; row < rows; row++)
    {
        bookSeriesList.removeAt(position);
    }
    endRemoveRows();
    return true;
}

void BookSeriesModel::sort(int column, Qt::SortOrder order)
{
    std::sort(bookSeriesList.begin(), bookSeriesList.end());
}

QList<BookManager::Entity::BookSeries> BookSeriesModel::getList()
{
    return bookSeriesList;
}

void BookSeriesModel::resetList(const QList<BookManager::Entity::BookSeries> &newCategories)
{
    beginResetModel();
    bookSeriesList = newCategories;
    endResetModel();
}