#include "Models/PersonModel.hpp"
#include "Utils/EnumUtils.hpp"

PersonModel::rowCount(const QModelIndex &parent) const
{
    return personList.count();
}

PersonModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant PersonModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(index.row() >= personList.size())
        return QVariant();
    switch(role)
    {
        case Qt::DisplayRole:
        case Qt::EditRole:
            if(index.column() == 0)
                return QString::fromStdString(Utils::EnumUtils::roleString(personList.at(index.row()).getRole()));
            else if(index.column() == 1)
                return QString::fromStdString(personList.at(index.row()).getFullName());
        case PersonModel::PersonRole::PersonId:
            return personList.at(index.row()).getId();
        case PersonModel::PersonRole::PersonFullName:
             return QString::fromStdString(personList.at(index.row()).getFullName());
        case PersonModel::PersonRole::PersonFirstName:
            return QString::fromStdString(personList.at(index.row()).getFirstName());
        case PersonModel::PersonRole::PersonLastName:
            return QString::fromStdString(personList.at(index.row()).getLastName());
        case PersonModel::PersonRole::PersonRole:
            return QVariant::fromValue(personList.at(index.row()).getRole());
        case PersonModel::PersonRole::PersonObject:
            return QVariant::fromValue(personList.at(index.row()));
        default:
            return QVariant();
    }
}

Qt::ItemFlags PersonModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool PersonModel::setData(
        const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        personList.replace(index.row(), value.value<BookManager::Entity::Person>());
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

bool PersonModel::insertRows(int position, int rows, const QModelIndex&)
{
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    for(int row = 0; row < rows; row++)
    {
        personList.insert(position, BookManager::Entity::Person());
    }
    endInsertRows();
    return true;
}

bool  PersonModel::removeRows(int position, int rows, const QModelIndex&)
{
    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    for(int row = 0; row < rows; row++)
    {
        personList.removeAt(position);
    }
    endRemoveRows();
    return true;
}

void PersonModel::sort(int column, Qt::SortOrder order)
{
    std::sort(personList.begin(), personList.end());
}

QVariant PersonModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Role");
            case 1:
                return tr("Full Name");
            default:
                return QVariant();
        }
    }
    return QVariant();
}

QList<BookManager::Entity::Person> PersonModel::getList()
{
    return personList;
}

void PersonModel::resetList(QList<BookManager::Entity::Person> newPersonList)
{
    beginResetModel();
    personList = newPersonList;
    endResetModel();
}