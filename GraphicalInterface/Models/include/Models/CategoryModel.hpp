#pragma once
#include <QAbstractListModel>
#include <QList>
#include <QModelIndex>
#include <QVariant>
#include <Qt>
#include "../../../../Category.hpp"


Q_DECLARE_METATYPE(BookManager::Category::Category)

class CategoryModel : public QAbstractListModel
{
public:

    enum CategoryRole {
        CategoryObject = Qt::UserRole + 1,
        CategoryId,
        CategoryName
    };

    enum CategoryColumn {
        Name = 0
    };

    CategoryModel(const QList<BookManager::Category::Category> &categories, QObject *parent = nullptr)
        : QAbstractListModel(parent), categoryList(categories) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index = QModelIndex()) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;
    void resetList(const QList<BookManager::Category::Category> &newCategories);

    QList<BookManager::Category::Category> getList();

private:
    QList<BookManager::Category::Category> categoryList;
};