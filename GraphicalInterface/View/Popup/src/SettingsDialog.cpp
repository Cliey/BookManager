#include "Popup/SettingsDialog.hpp"
#include "Managers/Utils/SettingsEnum.hpp"
#include "Managers/Utils/SettingsTypes.hpp"
#include "Utils/EnumUtils.hpp"
#include <iostream>
#include <QGridLayout>
#include <QFormLayout>
#include <QDialogButtonBox>

SettingsDialog::SettingsDialog(std::shared_ptr<BookManager::Manager::SettingsManager> settingsManager, QWidget *parent)
    : settingsManager(settingsManager), QDialog(parent)
{
    setWindowTitle("Settings");
    QGridLayout* layout = new QGridLayout();

    initGeneralSettings();
    initBookSettings();

    QGroupBox* personSettingsGroup = new QGroupBox("Author Settings");

    layout->addWidget(generalSettingsGroup, 0, 0);
    layout->addWidget(bookSettingsGroup, 0, 1);
    layout->addWidget(personSettingsGroup, 1, 0);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Close);
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, &saveSettings);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, this, &close);


    layout->addWidget(buttonBox, 1, 1);
    setLayout(layout);
}

void SettingsDialog::initGeneralSettings()
{
    generalSettingsGroup = new QGroupBox("General Settings");

    QFormLayout* formGeneralSettings = new QFormLayout();
    objectPerPage = new QComboBox();
    objectPerPage->addItem("20", 20);
    objectPerPage->addItem("50", 50);
    objectPerPage->addItem("100", 100);
    objectPerPage->setCurrentIndex(this->getIndexFromObjectPerPage());
    formGeneralSettings->addRow("Number of object per page : ", objectPerPage);

    generalSettingsGroup->setLayout(formGeneralSettings);
}

int SettingsDialog::getIndexFromObjectPerPage()
{
    int objectPerPage = settingsManager->getGeneralSettings().objectsPerPage;
    switch(objectPerPage)
    {
        default:
        case 20:
            return 0;
        case 50:
            return 1;
        case 100:
            return 2;
    }
}

void SettingsDialog::initBookSettings()
{
    bookSettingsGroup = new QGroupBox("Book Settings");
    QFormLayout* formBookSettings = new QFormLayout();
    displayType = new QComboBox();
    displayType->addItem(tr("List", "Display books in a list"), QVariant::fromValue(BookManager::Manager::Enum::DisplayBookEnum::listView));
    displayType->addItem(tr("Bookshelf", "Display books as if they were on a bookshelf"), QVariant::fromValue(BookManager::Manager::Enum::DisplayBookEnum::bookshelfView));
    displayType->addItem(tr("Cover", "Display books only with the cover"), QVariant::fromValue(BookManager::Manager::Enum::DisplayBookEnum::coverView));
    displayType->setCurrentIndex(this->getIndexFromDisplayType());
    formBookSettings->addRow("Display Type : ", displayType);

    bookSettingsGroup->setLayout(formBookSettings);
}

int SettingsDialog::getIndexFromDisplayType()
{
    using namespace BookManager::Manager::Enum;
    auto displayType = settingsManager->getBookSettings().displayType;
    switch(displayType)
    {
        default:
        case DisplayBookEnum::listView:
            return 0;
        case DisplayBookEnum::bookshelfView:
            return 1;
        case DisplayBookEnum::coverView:
            return 2;
    }
}

BookManager:: Manager::GeneralSettings SettingsDialog::getNewGeneralSettings()
{
    auto generalSettings = settingsManager->getGeneralSettings();
    generalSettings.objectsPerPage = objectPerPage->currentData().toInt();
    return generalSettings;
}

BookManager:: Manager::BookSettings SettingsDialog::getNewBooksSettings()
{
    auto booksSettings = settingsManager->getBookSettings();
    booksSettings.displayType = displayType->currentData().value<BookManager::Manager::Enum::DisplayBookEnum>();
    return booksSettings;
}

void SettingsDialog::saveSettings()
{
    settingsManager->setGeneralSettings(getNewGeneralSettings());
    settingsManager->setBookSettings(getNewBooksSettings());
    settingsManager->saveSettings();

    this->close();
}