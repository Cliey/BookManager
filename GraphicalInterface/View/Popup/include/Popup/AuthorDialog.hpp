#pragma once
#include "EntityTypes/Person.hpp"
#include "EntityEnum/Role.hpp"
#include <QDialog>
#include <QWidget>
#include <optional>

class QFormLayout;
class QRadioButton;
class QLineEdit;

class AuthorDialog : public QDialog
{
    Q_OBJECT
public:
    AuthorDialog(QWidget* parent = nullptr);
    AuthorDialog(BookManager::Entity::Person personToEdit, QWidget* parent = nullptr);

private slots:
    void acceptRole();

signals:
    void accepted(const BookManager::Entity::Person&);

private:
    void initWindow();
    void initFormLayout();
    void checkRoleRadioButton(BookManager::Entity::Role role);
    BookManager::Entity::Person getPersonObject();

    BookManager::Entity::Role getRole();
    QString getRoleStr();

    QFormLayout* formLayout;
    QRadioButton* buttonAuthor;
    QRadioButton* buttonIllustrator;
    QLineEdit* lastName;
    QLineEdit* firstName;

    std::optional<int> idPersonEdited;
};

