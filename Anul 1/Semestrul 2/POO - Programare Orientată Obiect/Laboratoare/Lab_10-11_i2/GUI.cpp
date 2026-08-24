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

	//stanga
	QVBoxLayout* layoutStg = new QVBoxLayout;
	layoutStg->addWidget(listaCarti);

	QHBoxLayout* layoutVizualizare = new QHBoxLayout;

	tabelCarti->setColumnCount(4);
	tabelCarti->setHorizontalHeaderLabels({ "Titlu", "Autor", "Gen", "An" });
	tabelCarti->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tabelCarti->setSelectionBehavior(QAbstractItemView::SelectRows);

	layoutVizualizare->addWidget(listaCarti);
	layoutVizualizare->addWidget(tabelCarti);

	layoutStg->addLayout(layoutVizualizare);

	QHBoxLayout* layoutSortareBar = new QHBoxLayout;
	comboSortare->addItem("Titlu");
	comboSortare->addItem("Autor");
	comboSortare->addItem("An si Gen");
	layoutSortareBar->addWidget(new QLabel("Sortare:"));
	layoutSortareBar->addWidget(comboSortare);
	layoutSortareBar->addWidget(btnSortare);
	layoutStg->addLayout(layoutSortareBar);

	QHBoxLayout* layoutFiltrareBar = new QHBoxLayout;
	comboFiltru->addItem("Titlu");
	comboFiltru->addItem("An");
	layoutFiltrareBar->addWidget(new QLabel("Filtrare:"));
	layoutFiltrareBar->addWidget(comboFiltru);
	layoutFiltrareBar->addWidget(editFiltru);
	layoutFiltrareBar->addWidget(btnFiltru);
	layoutFiltrareBar->addWidget(btnReload);
	layoutStg->addLayout(layoutFiltrareBar);

	//dreapta
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
	layoutDr->addWidget(btnCauta);
	layoutDr->addWidget(btnPopuleaza);
	layoutDr->addWidget(btnUndo);
	layoutDr->addWidget(btnCos);
	layoutDr->addWidget(btnExit);

	widgetDinamic->setLayout(layoutDinamic);
	layoutDr->addWidget(widgetDinamic);

	layoutMain->addLayout(layoutStg);
	layoutMain->addLayout(layoutDr);
	
	this->setLayout(layoutMain);

}

void GUI::reloadList(const std::vector<Carte>& carti) {
	listaCarti->clear();
	for (const auto& c : carti) {
		std::string text = c.getTitlu() + "|" + c.getAutor() + "|" + c.getGen() + "|" + std::to_string(c.getAnAparitie());
		listaCarti->addItem(QString::fromStdString(text));
	}

	tabelCarti->clearContents();
	tabelCarti->setRowCount(carti.size());
	int rand = 0;
	for (const auto& c : carti) {
		tabelCarti->setItem(rand, 0, new QTableWidgetItem(QString::fromStdString(c.getTitlu())));
		tabelCarti->setItem(rand, 1, new QTableWidgetItem(QString::fromStdString(c.getAutor())));
		tabelCarti->setItem(rand, 2, new QTableWidgetItem(QString::fromStdString(c.getGen())));
		tabelCarti->setItem(rand, 3, new QTableWidgetItem(QString::number(c.getAnAparitie())));
		rand++;
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

	// cautare
	QObject::connect(btnCauta, &QPushButton::clicked, this, [this]() {

		std::string titlu = editTitlu->text().toStdString();

		if (titlu.empty()) {
			QMessageBox::warning(this, "Atentie", "Introduceti un titlu in casuta pentru a cauta!");
			return;
		}

		try {

			Carte c = serv.cautaCarte(titlu);
			editAutor->setText(QString::fromStdString(c.getAutor()));
			editGen->setText(QString::fromStdString(c.getGen()));
			editAn->setText(QString::number(c.getAnAparitie()));
		}
		catch (const AppException& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.what()));

			editAutor->clear();
			editGen->clear();
			editAn->clear();
		}
		});

	// populare
	QObject::connect(btnPopuleaza, &QPushButton::clicked, this, [this]() {

		try {

			serv.populeazaBiblioteca();
			reloadList(serv.getCarti());
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

	//sortare
	QObject::connect(btnSortare, &QPushButton::clicked, this, [this]() {
		std::string criteriu = comboSortare->currentText().toStdString();

		if (criteriu == "Titlu") {
			reloadList(serv.sorteazaDupaTitlu());
		}
		else if (criteriu == "Autor") {
			reloadList(serv.sorteazaDupaAutor());
		}
		else if (criteriu == "An si Gen") {
			reloadList(serv.sorteazaDupaAnSiGen());
		}
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

	// filtrare
	QObject::connect(btnFiltru, &QPushButton::clicked, this, [this]() {
		std::string criteriu = comboFiltru->currentText().toStdString();
		std::string valoare = editFiltru->text().toStdString();

		if (valoare.empty()) {
			QMessageBox::warning(this, "Atentie", "Introduceti textul pentru filtrare!");
			return;
		}

		try {
			if (criteriu == "Titlu") {
				reloadList(serv.filtreazaDupaTitlu(valoare));
			}
			else if (criteriu == "An") {
				int an = std::stoi(valoare);
				reloadList(serv.filtreazaDupaAn(an));
			}
		}
		catch (const std::exception&) {
			QMessageBox::warning(this, "Eroare", "Valoare invalida pentru filtrare!");
		}
		});

	// arata toate
	QObject::connect(btnReload, &QPushButton::clicked, this, [this]() {
		reloadList(serv.getCarti());
		editFiltru->clear();
		});


	//pentru cos
	QObject::connect(btnCos, &QPushButton::clicked, this, [this]() {
		CosGUI* fereastraCos = new CosGUI{ cos };
		fereastraCos->show();
		});

	QObject::connect(tabelCarti, &QTableWidget::itemSelectionChanged, this, [this]() {
		auto rows = tabelCarti->selectionModel()->selectedRows();
		if (rows.isEmpty()) return;

		int row = rows.at(0).row();
		std::string titlu = tabelCarti->item(row, 0)->text().toStdString();

		try {
			Carte c = serv.cautaCarte(titlu);
			editTitlu->setText(QString::fromStdString(c.getTitlu()));
			editAutor->setText(QString::fromStdString(c.getAutor()));
			editGen->setText(QString::fromStdString(c.getGen()));
			editAn->setText(QString::number(c.getAnAparitie()));
		}
		catch (...) {}
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