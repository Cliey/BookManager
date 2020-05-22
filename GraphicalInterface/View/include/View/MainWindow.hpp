#pragma once
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QTabWidget>
#include <QAction>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void toggleSearch();

private:
    void initToolBars();
    void initGeneralToolBar();
    QToolButton* initAddMenu();
    void initSearchToolBar();
    void initCentralZone();


    QToolBar *generalToolbar;
    QTabWidget *tabWidget;

    QToolBar *searchToolbar;
    // QAction *searchAction;
    QLineEdit *searchInput;
};