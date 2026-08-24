#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_simulare.h"

class simulare : public QMainWindow
{
    Q_OBJECT

public:
    simulare(QWidget *parent = nullptr);
    ~simulare();

private:
    Ui::simulareClass ui;
};

