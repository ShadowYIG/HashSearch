#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include "ui_HashSearch.h"
#include "HashProcessing.h"

class HashSearch : public QMainWindow
{
    Q_OBJECT

public:
    HashSearch(QWidget *parent = Q_NULLPTR);
    QString str2qstr(const string str);
    string qstr2str(const QString qstr);

private slots:
    void btn_file_click();
    void btn_rand_click();
    void btn_add_click();
    void btn_search_click();
    void btn_built_click();
    void text_length();

private:
    Ui::HashSearchClass ui;
    hashpro *phashdata;
};
