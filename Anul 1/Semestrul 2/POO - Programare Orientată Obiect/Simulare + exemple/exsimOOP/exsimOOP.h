#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_exsimOOP.h"

class exsimOOP : public QMainWindow
{
    Q_OBJECT

public:
    exsimOOP(QWidget *parent = nullptr);
    ~exsimOOP();

private:
    Ui::exsimOOPClass ui;
};

