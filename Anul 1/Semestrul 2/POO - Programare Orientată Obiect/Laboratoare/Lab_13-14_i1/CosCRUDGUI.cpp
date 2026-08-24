#include "CosCRUDGUI.h"
#include <QMessageBox>
#include <QFormLayout>

CosCRUDGUI::CosCRUDGUI(Cos& cos, QWidget* parent)
    : QWidget(parent), cos{ cos } {
    cos.addObserver(this);
    initGUI();
    connectSignals();
    reloadList();
}

CosCRUDGUI::~CosCRUDGUI() {
    cos.removeObserver(this);
}

void CosCRUDGUI::update() {
    reloadList();
}

void CosCRUDGUI::initGUI() {
    setWindowTitle("Cos CRUD");
    auto* mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(listaCos);

    auto* rightLayout = new QVBoxLayout;
    auto* form = new QFormLayout;
    form->addRow("Titlu:", editTitlu);
    form->addRow("Nr carti:", editNumar);
    rightLayout->addLayout(form);
    rightLayout->addWidget(btnAdauga);
    rightLayout->addWidget(btnGenereaza);
    rightLayout->addWidget(btnGoleste);
    rightLayout->addStretch();
    mainLayout->addLayout(rightLayout);
}

void CosCRUDGUI::reloadList() {
    listaCos->clear();
    for (const auto& c : cos.getCarti()) {
        std::string text = c.getTitlu() + " | " + c.getAutor() +
            " | " + c.getGen() + " | " +
            std::to_string(c.getAnAparitie());
        listaCos->addItem(QString::fromStdString(text));
    }
}

void CosCRUDGUI::connectSignals() {
    QObject::connect(btnGoleste, &QPushButton::clicked, this, [this]() {
        cos.goleste();
        });

    QObject::connect(btnAdauga, &QPushButton::clicked, this, [this]() {
        try {
            cos.adauga(editTitlu->text().toStdString());
            editTitlu->clear();
        }
        catch (const AppException& ex) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.what()));
        }
        });

    QObject::connect(btnGenereaza, &QPushButton::clicked, this, [this]() {
        try {
            cos.genereaza(static_cast<size_t>(editNumar->text().toInt()));
            editNumar->clear();
        }
        catch (const AppException& ex) {
            QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.what()));
        }
        });
}