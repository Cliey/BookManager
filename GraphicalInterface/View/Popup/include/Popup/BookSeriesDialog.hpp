#pragma once
#include "EntityTypes/BookSeries.hpp"
#include <QDialog>
#include <QWidget>
#include <optional>

class QFormLayout;
class QLineEdit;
class QPushButton;

class BookSeriesDialog : public QDialog
{
    Q_OBJECT
public:
    BookSeriesDialog(QWidget* parent = nullptr);
    BookSeriesDialog(BookManager::Entity::BookSeries bookSeriesToEdit, QWidget* parent = nullptr);

private slots:
    void acceptRole();

signals:
    void accepted(const BookManager::Entity::BookSeries&);

private:
    void initWindow();
    void initFormLayout();
    BookManager::Entity::BookSeries getBookSeriesObject();

    QFormLayout* formLayout;
    QColor colorChoosen;
    QLineEdit* bookSeriesName;
    std::optional<int> idBookSeriesEdited;
};
