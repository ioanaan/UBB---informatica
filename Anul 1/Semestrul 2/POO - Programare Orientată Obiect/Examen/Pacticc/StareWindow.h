#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "Observer.h"
#include "service.h"

class StareWindow : public QWidget, public Observer {
    Q_OBJECT
public:
    StareWindow(const std::string& stare, Service& srv, QWidget* parent = nullptr);

    void update() override;

signals:
    void schimbaStare(int id, const std::string& stareNoua);

private slots:
    void onOpen();
    void onInprogress();
    void onClosed();

private:
    std::string stare;
    Service& srv;

    QListWidget* lista;
    QPushButton* btnOpen;
    QPushButton* btnInprogress;
    QPushButton* btnClosed;


    void afiseaza();
};