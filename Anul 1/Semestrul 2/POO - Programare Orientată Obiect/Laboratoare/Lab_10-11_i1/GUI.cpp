#include <QWidget>
#include <QMessageBox>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include "GUI.h"
#include "CosGUI.h"

void GUI::initGUI() {

	QHBoxLayout* layoutMain = new QHBoxLayout;
	layoutMain->addWidget(listaCarti);

	QVBoxLayout* layoutDr = new QVBoxLayout;
	QFormLayout* formLayout = new QFormLayout;
	formLayout->addRow("Titlu:", editTitlu);
	formLayout->addRow("Autor:", editAutor);
	formLayout->addRow("Gen:", editGen);
	formLayout->addRow("An:", editAn);
	layoutDr->addLayout(formLayout);

	layoutDr->addWidget(btnAdauga);
	layoutDr->addWidget(btnSterge);
	layoutDr->addWidget(btnModifica);
	layoutDr->addWidget(btnUndo);
	layoutDr->addWidget(btnSortTitlu);
	layoutDr->addWidget(btnSortAutor);
	layoutDr->addWidget(btnCos);
	layoutDr->addWidget(btnExit);

	widgetDinamic->setLayout(layoutDinamic);
	layoutDr->addWidget(widgetDinamic);

	layoutMain->addLayout(layoutDr);
	
	this->setLayout(layoutMain);

}

void GUI::reloadList(const std::vector<Carte>& carti) {

	listaCarti->clear();

	for (const auto& c : carti) {
		std::string textLista = c.getTitlu() + "|" +
			c.getAutor() + "|" +
			c.getGen() + "|" +
			std::to_string(c.getAnAparitie());

		listaCarti->addItem(QString::fromStdString(textLista));
	}
}

void GUI::connectSignals() {

	//exit
	QObject::connect(btnExit, &QPushButton::clicked, this, [this]() {
		close();
		});

	//adauga
	QObject::connect(btnAdauga, &QPushButton::clicked, this, [this]() {

		try {
			std::string titlu = editTitlu->text().toStdString();
			std::string autor = editAutor->text().toStdString();
			std::string gen = editGen->text().toStdString();
			int an = editAn->text().toInt();

			serv.adaugaCarte(titlu, autor, gen, an);

			reloadList(serv.getCarti());

			editTitlu->clear();
			editAutor->clear();
			editGen->clear();
			editAn->clear();
		}
		catch (const AppException& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.what()));
		}

		});

	//sterge
	QObject::connect(btnSterge, &QPushButton::clicked, this, [this]() {

		try {
			std::string titlu = editTitlu->text().toStdString();

			serv.stergeCarte(titlu);

			reloadList(serv.getCarti());

			editTitlu->clear();
		}
		catch (const AppException& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.what()));
		}

		});

	//modifica
	QObject::connect(btnModifica, &QPushButton::clicked, this, [this]() {

		if (listaCarti->selectedItems().isEmpty()) {
			QMessageBox::warning(this, "Atentie", "Selectati o carte din lista pentru a o modifica!");
			return;
		}

		std::string textSelectat = listaCarti->selectedItems().at(0)->text().toStdString();
		size_t pozitieBara = textSelectat.find("|");
		std::string titluVechi = textSelectat.substr(0, pozitieBara);

		try {

			std::string titluNou = editTitlu->text().toStdString();
			std::string autorNou = editAutor->text().toStdString();
			std::string genNou = editGen->text().toStdString();
			int anNou = editAn->text().toInt();

			serv.modificaCarte(titluVechi, titluNou, autorNou, genNou, anNou);

			reloadList(serv.getCarti());

			editTitlu->clear();
			editAutor->clear();
			editGen->clear();
			editAn->clear();
		}
		catch (const AppException& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.what()));
		}

		});

	//undo
	QObject::connect(btnUndo, &QPushButton::clicked, this, [this]() {

		try {
			serv.undo();
			reloadList(serv.getCarti());
		}
		catch (const AppException& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.what()));
		}
			
		});

	//sortare titlu
	QObject::connect(btnSortTitlu, &QPushButton::clicked, this, [this]() {
		reloadList(serv.sorteazaDupaTitlu());
		});

	//sortare autor
	QObject::connect(btnSortAutor, &QPushButton::clicked, this, [this]() {
		reloadList(serv.sorteazaDupaAutor());
		});



	//stergere/modifcare cu click
	QObject::connect(listaCarti, &QListWidget::itemSelectionChanged, this, [this]() {
		
		if (listaCarti->selectedItems().isEmpty()) {
			
			editTitlu->clear();
			editAutor->clear();
			editGen->clear();
			editAn->clear();
			return;
		}

		std::string textSelectat = listaCarti->selectedItems().at(0)->text().toStdString();

		size_t pozitieBara = textSelectat.find('|');
		std::string titlu = textSelectat.substr(0, pozitieBara);

		try {
			
			Carte c = serv.cautaCarte(titlu);

			editTitlu->setText(QString::fromStdString(c.getTitlu()));
			editAutor->setText(QString::fromStdString(c.getAutor()));
			editGen->setText(QString::fromStdString(c.getGen()));
			editAn->setText(QString::number(c.getAnAparitie()));

		}
		catch (const AppException& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.what()));
		}
		});


	//pentru cos
	QObject::connect(btnCos, &QPushButton::clicked, this, [this]() {
		CosGUI* fereastraCos = new CosGUI{ cos };
		fereastraCos->show();
		});
}


void GUI::incarcaButoaneDinamic() {

	std::map<std::string, int> dict;
	for (const auto& c : serv.getCarti()) {

		dict[c.getGen()]++;
	}

	for (const auto& pereche : dict) {

		std::string gen = pereche.first;
		int numar = pereche.second;

		QPushButton* btn = new QPushButton(QString::fromStdString(gen));
		layoutDinamic->addWidget(btn);

		QObject::connect(btn, &QPushButton::clicked, this, [this, gen, numar]() {

			QMessageBox::information(this, "Info Gen", QString::fromStdString("Exista " + std::to_string(numar) + " carti de genul " + gen + "."));

			});
	}
}