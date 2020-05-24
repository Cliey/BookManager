#pragma once
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

class CategoryPage : public QWidget
{
public:
    CategoryPage(QWidget *parent = nullptr);

private:
    QLabel* right;
    QWidget* left;
};