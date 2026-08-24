#pragma once
#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include "Subject.h"
#include "Observer.h"
#include "StareWindow.h"
#include "service.h"
#include "repo.h"

class GUI : public QMainWindow, public Subject, public Observer {
    Q_OBJECT
public:
    /* constructor */
    GUI(QWidget* parent = nullptr);

    /* destructor */
    ~GUI();

    /* actualizeaza tabel */
    void update() override;

private slots:
    /* filtreaza dupa programator*/
    void cautaDupaProgramator();

    /* adauga task */
    void adaugaTask();

    void reset();

    /* schimba stare task */
    void onSchimbaStare(int id, const std::string& stareNoua);

private:
    QTableWidget* tabel;
    QLineEdit* inputId;
    QLineEdit* inputDescriere;
    QLineEdit* inputProg1;
    QLineEdit* inputProg2;
    QLineEdit* inputProg3;
    QComboBox* comboStare;
    QLineEdit* inputSearch;
    QPushButton* btnAdauga;
    QPushButton* btnCauta;
    QPushButton* btnReset;

    Repository* repo;
    Service* srv;

    StareWindow* winOpen;
    StareWindow* winInprogress;
    StareWindow* winClosed;

    /* afiseaza task uri */
    void afiseaza(const std::vector<Task>& tasks);
};