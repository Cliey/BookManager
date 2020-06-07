#include "Popup/CategoryDialog.hpp"
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QColorDialog>
#include <QMessageBox>

CategoryDialog::CategoryDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Add a Category");
    initWindow();
}

CategoryDialog::CategoryDialog(BookManager::Category::Category categoryToEdit, QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Modify a Category");
    initWindow();
    categoryName->setText(QString::fromStdString(categoryToEdit.getName()));
    idCategoryEdited = categoryToEdit.getId();
}

void CategoryDialog::initWindow()
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
void CategoryDialog::initFormLayout()
{
    formLayout = new QFormLayout();
    categoryName = new QLineEdit();
    categoryColor = new QPushButton();
    categoryColor->setStyleSheet(pushButtonColorStylesheet.arg("white"));
    QHBoxLayout* layoutNameColor = new QHBoxLayout();
    layoutNameColor->addWidget(categoryName);
    layoutNameColor->addWidget(categoryColor);

    formLayout->addRow(tr("Category Name: "), layoutNameColor);
    // formLayout->addRow(tr("Color: "), categoryColor);
    QObject::connect(categoryColor, &QPushButton::clicked, this, &CategoryDialog::openColorDialog);

}

QColor CategoryDialog::getColorBase()
{
    if(!categoryColor->text().isEmpty())
        return QColor(categoryColor->text());
    return QColor("#ffffff");
}

void CategoryDialog::openColorDialog()
{
    auto colorBase = getColorBase();
    colorChoosen = QColorDialog::getColor(colorBase, this);
    if(colorChoosen.isValid())
    {
        categoryColor->setStyleSheet(pushButtonColorStylesheet.arg(colorChoosen.name()));
    }
}

BookManager::Category::Category CategoryDialog::getCategoryObject()
{
    std::string categoryNameStr{categoryName->text().toStdString()};
    if(idCategoryEdited)
    {
        return {idCategoryEdited.value(), categoryNameStr};
    }
    return {0, categoryNameStr};
}

void CategoryDialog::acceptRole()
{
    if(categoryName->text().isEmpty())
    {
        QMessageBox::critical(this, tr("Error") , tr("The name of the category is empty."), QMessageBox::Cancel);
        return;
    }
    BookManager::Category::Category category = getCategoryObject();
    emit accepted(category);
    this->close();
}