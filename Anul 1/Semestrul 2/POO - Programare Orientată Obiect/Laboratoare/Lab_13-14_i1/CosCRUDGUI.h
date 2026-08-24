#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "cos.h"

class CosCRUDGUI : public QWidget, public Observer {
private:
    Cos& cos;

    QListWidget* listaCos = new QListWidget;
    QLineEdit* editTitlu = new QLineEdit;
    QLineEdit* editNumar = new QLineEdit;

    QPushButton* btnAdauga = new QPushButton{ "&Adauga" };
    QPushButton* btnGenereaza = new QPushButton{ "&Genereaza" };
    QPushButton* btnGoleste = new QPushButton{ "&Goleste" };

    void initGUI();
    void connectSignals();
    void reloadList();

public:
    CosCRUDGUI(Cos& cos, QWidget* parent = nullptr);
    //observer
    void update() override;
    //remove observer
    ~CosCRUDGUI();
};