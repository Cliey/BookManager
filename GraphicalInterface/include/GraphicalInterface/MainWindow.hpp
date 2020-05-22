#pragma once
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QTabWidget>

class MainWindow : public QMainWindow
{
public:
    MainWindow();

private:
    void setToolBar();
    void setCentralZone();

    QToolBar *generalToolbar;
    QTabWidget *tabWidget;
};