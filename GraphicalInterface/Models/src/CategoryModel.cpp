#include "Models/CategoryModel.hpp"
#include <iostream>
#include <QString>

int CategoryModel::rowCount(const QModelIndex &parent) const
{
    return categoryList.count();
}

int CategoryModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant CategoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(index.row() >= categoryList.size())
        return QVariant();
    switch(role)
    {
        case CategoryRole::CategoryName:
        case Qt::DisplayRole:
        case Qt::EditRole:
            return QString::fromStdString(categoryList.at(index.row()).getName());
        case CategoryRole::CategoryId:
            return categoryList.at(index.row()).getId();
        case CategoryRole::CategoryObject:
            return QVariant::fromValue(categoryList.at(index.row()));
        default:
            return QVariant();
    }
}

Qt::ItemFlags CategoryModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CategoryModel::setData(
        const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        categoryList.replace(index.row(), value.value<BookManager::Category::Category>());
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

bool CategoryModel::insertRows(int position, int rows, const QModelIndex&)
{
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for(int row = 0; row < rows; row++)
    {
        categoryList.insert(position, BookManager::Category::Category());
    }
    endInsertRows();
    return true;
}

bool  CategoryModel::removeRows(int position, int rows, const QModelIndex&)
{
    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    for(int row = 0; row < rows; row++)
    {
        categoryList.removeAt(position);
    }
    endRemoveRows();
    return true;
}

void CategoryModel::sort(int column, Qt::SortOrder order)
{
    std::sort(categoryList.begin(), categoryList.end());
}

QList<BookManager::Category::Category> CategoryModel::getList()
{
    return categoryList;
}

void CategoryModel::resetList(const QList<BookManager::Category::Category> &newCategories)
{
    beginResetModel();
    categoryList = newCategories;
    endResetModel();
}