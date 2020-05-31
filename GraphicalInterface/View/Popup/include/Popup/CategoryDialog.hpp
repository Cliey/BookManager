#pragma once
#include "../../../../Category.hpp"
#include <QDialog>
#include <QWidget>
#include <QColor>
#include <iostream>
#include <optional>

class QFormLayout;
class QLineEdit;
class QPushButton;

namespace
{
const QString pushButtonColorStylesheet("border: 1px groove grey; background: %1;");
} // namespace

class CategoryDialog : public QDialog
{
    Q_OBJECT
public:
    CategoryDialog(QWidget* parent = nullptr);
    CategoryDialog(BookManager::Category::Category categoryToEdit, QWidget* parent = nullptr);

private slots:
    void openColorDialog();
    void acceptRole();

signals:
    void accepted(const BookManager::Category::Category&);

private:
    void initWindow();
    void initFormLayout();
    QColor getColorBase();
    BookManager::Category::Category getCategoryObject();

    QFormLayout* formLayout;
    QColor colorChoosen;
    QLineEdit* categoryName;
    QPushButton* categoryColor;
    std::optional<int> idCategoryEdited;
};
