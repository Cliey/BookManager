#pragma once
#include <QWidget>
#include <QGridLayout>

class BookPage : public QWidget
{
public:
    BookPage(QWidget *parent = nullptr);

private:
    void initRightPane();
    void createLabelAndData(QString label, QString data, int row);

    QWidget* right;
    QGridLayout* gridLayout;
};