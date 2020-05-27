#pragma once
#include <QDialog>
#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <memory>
#include "Managers/SettingsManager.hpp"

Q_DECLARE_METATYPE(BookManager::Manager::Enum::DisplayBookEnum)

namespace BookManager
{
    namespace Manager
    {
        struct GeneralSettings;
        struct BookSettings;
    } // namespace Manager
} // namespace BookManager

class SettingsDialog : public QDialog
{
Q_OBJECT

public:
    SettingsDialog(std::shared_ptr<BookManager::Manager::SettingsManager> settingsManager, QWidget* parent = nullptr);

private slots:
    void saveSettings();

private:
    void initGeneralSettings();
    int getIndexFromObjectPerPage();
    void initBookSettings();
    int getIndexFromDisplayType();

    BookManager:: Manager::GeneralSettings getNewGeneralSettings();
    BookManager:: Manager::BookSettings getNewBooksSettings();

    std::shared_ptr<BookManager::Manager::SettingsManager> settingsManager;

    QGroupBox* generalSettingsGroup;
    QComboBox* objectPerPage;
    QGroupBox* bookSettingsGroup;
    QComboBox* displayType;
};