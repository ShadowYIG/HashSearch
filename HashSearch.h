#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HashSearch.h"

class HashSearch : public QMainWindow
{
    Q_OBJECT

public:
    HashSearch(QWidget *parent = Q_NULLPTR);

private:
    Ui::HashSearchClass ui;
};
