#include "StareWindow.h"

/* initializeaza pentru o stare */
StareWindow::StareWindow(const std::string& stare, Service& srv, QWidget* parent)
    : QWidget(parent), stare(stare), srv(srv) {

    setWindowTitle(QString::fromStdString(stare));

    lista = new QListWidget(this);

    btnOpen = new QPushButton("Open");
    btnInprogress = new QPushButton("Inprogress");
    btnClosed = new QPushButton("Closed");

    QHBoxLayout* layoutButoane = new QHBoxLayout();
    layoutButoane->addWidget(btnOpen);
    layoutButoane->addWidget(btnInprogress);
    layoutButoane->addWidget(btnClosed);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(new QLabel(QString::fromStdString("Taskuri: " + stare)));
    layout->addWidget(lista);
    layout->addLayout(layoutButoane);
    setLayout(layout);

    connect(btnOpen, &QPushButton::clicked, this, &StareWindow::onOpen);
    connect(btnInprogress, &QPushButton::clicked, this, &StareWindow::onInprogress);
    connect(btnClosed, &QPushButton::clicked, this, &StareWindow::onClosed);

    afiseaza();
}

/* afis task cu starea coresp */
void StareWindow::afiseaza() {
    lista->clear();
    for (const auto& t : srv.getAll()) {
        if (t.getStare() == stare) {
            QString text = QString::fromStdString(
                std::to_string(t.getId()) + " - " + t.getDescriere() + " - " + t.getProgramatoriStr()
            );
            lista->addItem(text);
        }
    }
}

/* update */
void StareWindow::update() {
    afiseaza();
}

/* schimba starea open */
void StareWindow::onOpen() {
    int index = lista->currentRow();
    if (index < 0) return;
    std::vector<Task> taskuri;
    for (const auto& t : srv.getAll())
        if (t.getStare() == stare)
            taskuri.push_back(t);
    if (index < (int)taskuri.size())
        emit schimbaStare(taskuri[index].getId(), "open");
}

/* schimba starea inprogress */
void StareWindow::onInprogress() {
    int index = lista->currentRow();
    if (index < 0) return;
    std::vector<Task> taskuri;
    for (const auto& t : srv.getAll())
        if (t.getStare() == stare)
            taskuri.push_back(t);
    if (index < (int)taskuri.size())
        emit schimbaStare(taskuri[index].getId(), "inprogress");
}

/* schimba starea closed */
void StareWindow::onClosed() {
    int index = lista->currentRow();
    if (index < 0) return;
    std::vector<Task> taskuri;
    for (const auto& t : srv.getAll())
        if (t.getStare() == stare)
            taskuri.push_back(t);
    if (index < (int)taskuri.size())
        emit schimbaStare(taskuri[index].getId(), "closed");
}