#include "Popup/AuthorDialog.hpp"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QLineEdit>
#include <QMessageBox>

AuthorDialog::AuthorDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Add an Author");
    initWindow();
}

AuthorDialog::AuthorDialog(BookManager::Entity::Person personToEdit, QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Edit an Author");
    initWindow();
    firstName->setText(QString::fromStdString(personToEdit.getFirstName()));
    lastName->setText(QString::fromStdString(personToEdit.getLastName()));
    checkRoleRadioButton(personToEdit.getRole());
    idPersonEdited = personToEdit.getId();

}

void AuthorDialog::checkRoleRadioButton(BookManager::Entity::Role role)
{
    switch(role)
    {
        case BookManager::Entity::Role::Author:
            buttonAuthor->setChecked(true);
            break;
        case BookManager::Entity::Role::Illustrator:
            buttonIllustrator->setChecked(true);
            break;
        default:
        case BookManager::Entity::Role::Undefined:
            break;
    }
}

void AuthorDialog::initWindow()
{
    setAttribute(Qt::WA_DeleteOnClose);
    QVBoxLayout* layout = new QVBoxLayout();
    QDialogButtonBox* buttonBox = new QDialogButtonBox();
    QPushButton* buttonSaveAndAddMore = new QPushButton("Add another");
    buttonBox->addButton(QDialogButtonBox::Save);
    // buttonBox->addButton(buttonSaveAndAddMore, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(QDialogButtonBox::Close);
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, &acceptRole);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, this, &close);

    initFormLayout();
    layout->addLayout(formLayout);
    layout->addWidget(buttonBox);
    setLayout(layout);
}

void AuthorDialog::initFormLayout()
{
    formLayout = new QFormLayout();

    QHBoxLayout* authorIllustratorLayout = new QHBoxLayout();
    buttonAuthor = new QRadioButton(tr("Author"));
    buttonIllustrator = new QRadioButton(tr("Illustrator"));
    authorIllustratorLayout->addWidget(buttonAuthor);
    authorIllustratorLayout->addWidget(buttonIllustrator);
    formLayout->addRow(tr("Author/Illustrator: "), authorIllustratorLayout);
    lastName = new QLineEdit();
    firstName = new QLineEdit();
    formLayout->addRow(tr("Last Name: "), lastName);
    formLayout->addRow(tr("First Name: "), firstName);
}

BookManager::Entity::Role AuthorDialog::getRole()
{
    if(buttonAuthor->isChecked())
        return BookManager::Entity::Role::Author;
    if(buttonIllustrator->isChecked())
        return BookManager::Entity::Role::Illustrator;
    return BookManager::Entity::Role::Undefined;
}

QString AuthorDialog::getRoleStr()
{
    if(buttonAuthor->isChecked())
        return buttonAuthor->text();
    if(buttonIllustrator->isChecked())
        return buttonIllustrator->text();
    return "Undefined";
}

BookManager::Entity::Person AuthorDialog::getPersonObject()
{
    std::string firstNameStr = firstName->text().toStdString();
    std::string lastNameStr = lastName->text().toStdString();
    if(idPersonEdited)
        return {idPersonEdited.value(), firstNameStr, lastNameStr, this->getRole()};
    return {0, firstNameStr, lastNameStr, this->getRole()};
}

void AuthorDialog::acceptRole()
{
    if(lastName->text().isEmpty())
    {
        QMessageBox::critical(this, tr("Error") , QString(tr("The Last Name of the %1 is empty.")).arg(getRoleStr()), QMessageBox::Cancel);
        return;
    }
    if(firstName->text().isEmpty())
    {
        QMessageBox::critical(this, tr("Error") , QString(tr("The First Name of the %1 is empty.")).arg(getRoleStr()), QMessageBox::Cancel);
        return;
    }
    BookManager::Entity::Person person = getPersonObject();
    emit accepted(person);
    this->close();
}