#include "GUI.h"
#include <QMessageBox>
#include <QHeaderView>
#include <algorithm>

GUI::GUI(QWidget* parent) : QMainWindow(parent) {
    repo = new Repository("tasks.txt");
    srv = new Service(*repo);

    // tabel
    tabel = new QTableWidget(this);
    tabel->setColumnCount(4);
    tabel->setHorizontalHeaderLabels({ "ID", "Descriere", "Programatori", "Stare" });
    tabel->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tabel->setSelectionBehavior(QAbstractItemView::SelectRows);
    tabel->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // campuri adaugare task
    inputId = new QLineEdit();
    inputId->setPlaceholderText("ID");
    inputDescriere = new QLineEdit();
    inputDescriere->setPlaceholderText("Descriere");
    inputProg1 = new QLineEdit();
    inputProg1->setPlaceholderText("Programator 1");
    inputProg2 = new QLineEdit();
    inputProg2->setPlaceholderText("Programator 2");
    inputProg3 = new QLineEdit();
    inputProg3->setPlaceholderText("Programator 3");

    // combo stare
    comboStare = new QComboBox();
    comboStare->addItem("open");
    comboStare->addItem("inprogress");
    comboStare->addItem("closed");

    btnAdauga = new QPushButton("Adauga Task");

    // layout adaugare
    QHBoxLayout* layoutAdauga = new QHBoxLayout();
    layoutAdauga->addWidget(new QLabel("ID:"));
    layoutAdauga->addWidget(inputId);
    layoutAdauga->addWidget(new QLabel("Descriere:"));
    layoutAdauga->addWidget(inputDescriere);
    layoutAdauga->addWidget(inputProg1);
    layoutAdauga->addWidget(inputProg2);
    layoutAdauga->addWidget(inputProg3);
    layoutAdauga->addWidget(new QLabel("Stare:"));
    layoutAdauga->addWidget(comboStare);
    layoutAdauga->addWidget(btnAdauga);

    // campuri search
    inputSearch = new QLineEdit();
    inputSearch->setPlaceholderText("Cauta dupa programator...");
    btnCauta = new QPushButton("Cauta");
    btnReset = new QPushButton("Reset");

    QHBoxLayout* layoutSearch = new QHBoxLayout();
    layoutSearch->addWidget(new QLabel("Programator:"));
    layoutSearch->addWidget(inputSearch);
    layoutSearch->addWidget(btnCauta);
    layoutSearch->addWidget(btnReset);

    QVBoxLayout* layoutPrincipal = new QVBoxLayout();
    layoutPrincipal->addLayout(layoutAdauga);
    layoutPrincipal->addLayout(layoutSearch);
    layoutPrincipal->addWidget(tabel);

    QWidget* central = new QWidget(this);
    central->setLayout(layoutPrincipal);
    setCentralWidget(central);

    // conectare semnale
    connect(btnAdauga, &QPushButton::clicked, this, &GUI::adaugaTask);
    connect(btnCauta, &QPushButton::clicked, this, &GUI::cautaDupaProgramator);
    connect(btnReset, &QPushButton::clicked, this, &GUI::reset);

    // creare ferestre aditionale
    winOpen = new StareWindow("open", *srv);
    winInprogress = new StareWindow("inprogress", *srv);
    winClosed = new StareWindow("closed", *srv);

    // adaugare ca observeri
    addObserver(this);
    addObserver(winOpen);
    addObserver(winInprogress);
    addObserver(winClosed);

    // conectare semnale de la ferestre la GUI
    connect(winOpen, &StareWindow::schimbaStare, this, &GUI::onSchimbaStare);
    connect(winInprogress, &StareWindow::schimbaStare, this, &GUI::onSchimbaStare);
    connect(winClosed, &StareWindow::schimbaStare, this, &GUI::onSchimbaStare);

    // afisare initiala
    afiseaza(srv->getSortedByStare());

    // 3 ferestre
    winOpen->show();
    winInprogress->show();
    winClosed->show();
}

/* destructor */
GUI::~GUI() {
    delete winOpen;
    delete winInprogress;
    delete winClosed;
    delete srv;
    delete repo;
}

/* actualizeaza tabel*/
void GUI::update() {
    afiseaza(srv->getSortedByStare());
}

void GUI::afiseaza(const std::vector<Task>& tasks) {
    tabel->setRowCount(0);
    for (const auto& t : tasks) {
        int rand = tabel->rowCount();
        tabel->insertRow(rand);
        tabel->setItem(rand, 0, new QTableWidgetItem(QString::number(t.getId())));
        tabel->setItem(rand, 1, new QTableWidgetItem(QString::fromStdString(t.getDescriere())));
        tabel->setItem(rand, 2, new QTableWidgetItem(QString::fromStdString(t.getProgramatoriStr())));
        tabel->setItem(rand, 3, new QTableWidgetItem(QString::fromStdString(t.getStare())));
    }
}

/* adauga task */
void GUI::adaugaTask() {
    if (inputId->text().isEmpty() || inputDescriere->text().isEmpty()) {
        QMessageBox::warning(this, "Eroare", "ID si Descriere sunt obligatorii!");
        return;
    }

    int id = inputId->text().toInt();
    std::string descriere = inputDescriere->text().toStdString();
    std::string stare = comboStare->currentText().toStdString();

    std::vector<std::string> programatori;
    if (!inputProg1->text().isEmpty()) programatori.push_back(inputProg1->text().toStdString());
    if (!inputProg2->text().isEmpty()) programatori.push_back(inputProg2->text().toStdString());
    if (!inputProg3->text().isEmpty()) programatori.push_back(inputProg3->text().toStdString());

    srv->adaugaTask(id, descriere, programatori, stare);

    inputId->clear();
    inputDescriere->clear();
    inputProg1->clear();
    inputProg2->clear();
    inputProg3->clear();

    notifyAll();
}

/* filtreaza taskurile dupa programator */
void GUI::cautaDupaProgramator() {
    std::string search = inputSearch->text().toStdString();
    auto filtrate = srv->filtreazaDupaProgramator(search);
    std::sort(filtrate.begin(), filtrate.end(),
        [](const Task& a, const Task& b) {
            auto prioritate = [](const std::string& s) {
                if (s == "open") return 0;
                if (s == "inprogress") return 1;
                return 2;
                };
            return prioritate(a.getStare()) < prioritate(b.getStare());
        });
    afiseaza(filtrate);
}

/* reseteaza tabelul */
void GUI::reset() {
    inputSearch->clear();
    afiseaza(srv->getSortedByStare());
}

void GUI::onSchimbaStare(int id, const std::string& stareNoua) {
    srv->schimbaStare(id, stareNoua);
    notifyAll();
}