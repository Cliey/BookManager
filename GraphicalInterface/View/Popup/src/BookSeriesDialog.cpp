#include "Popup/BookSeriesDialog.hpp"
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>

BookSeriesDialog::BookSeriesDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Add a Book Series");
    initWindow();
}

BookSeriesDialog::BookSeriesDialog(BookManager::Entity::BookSeries bookSeriesToEdit, QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Modify a Book Series");
    initWindow();
    bookSeriesName->setText(QString::fromStdString(bookSeriesToEdit.getName()));
    idBookSeriesEdited = bookSeriesToEdit.getId();
}

void BookSeriesDialog::initWindow()
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
void BookSeriesDialog::initFormLayout()
{
    formLayout = new QFormLayout();
    bookSeriesName = new QLineEdit();
    formLayout->addRow(tr("Book Series Name: "), bookSeriesName);
}

BookManager::Entity::BookSeries BookSeriesDialog::getBookSeriesObject()
{
    std::string bookSeriesNameStr{bookSeriesName->text().toStdString()};
    if(idBookSeriesEdited)
    {
        return {idBookSeriesEdited.value(), bookSeriesNameStr};
    }
    return {0, bookSeriesNameStr};
}

void BookSeriesDialog::acceptRole()
{
    if(bookSeriesName->text().isEmpty())
    {
        QMessageBox::critical(this, tr("Error") , tr("The name of the book series is empty."), QMessageBox::Cancel);
        return;
    }
    BookManager::Entity::BookSeries bookSeries = getBookSeriesObject();
    emit accepted(bookSeries);
    this->close();
}