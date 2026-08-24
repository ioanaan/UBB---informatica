#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Pacticc.h"

class Pacticc : public QMainWindow
{
    Q_OBJECT

public:
    Pacticc(QWidget *parent = nullptr);
    ~Pacticc();

private:
    Ui::PacticcClass ui;
};

