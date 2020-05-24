#pragma once
#include "Models/CategoryModel.hpp"
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QListView>
#include <QPoint>
#include <QMenu>

class CategoryPage : public QWidget
{
    Q_OBJECT
public:
    CategoryPage(QWidget *parent = nullptr);

private slots:
    void deleteCategoriesSelected();
    void openMenu(const QPoint& pos);
private:
    void initLeftPane();
    void initList();

    QLabel* right;
    QVBoxLayout* leftLayout;
    CategoryModel* categoryModel;
    QListView* categoryListView;
};