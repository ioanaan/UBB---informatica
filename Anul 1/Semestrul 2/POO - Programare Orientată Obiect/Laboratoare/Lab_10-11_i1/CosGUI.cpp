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

void CosGUI::initGUI() {
	QHBoxLayout* layoutMain = new QHBoxLayout;
	layoutMain->addWidget(listaCos);

	QVBoxLayout* layoutDr = new QVBoxLayout;
	QFormLayout* formLayout = new QFormLayout;

	formLayout->addRow("Titlu:", editTitlu);
	formLayout->addRow("Numar carti:", editNumarCarti);
	layoutDr->addLayout(formLayout);

	layoutDr->addWidget(btnAdauga);
	layoutDr->addWidget(btnGenereaza);
	layoutDr->addWidget(btnGoleste);
	layoutDr->addWidget(btnExit);

	layoutMain->addLayout(layoutDr);

	this->setLayout(layoutMain);
}

void CosGUI::reloadCosList() {
	listaCos->clear();

	for (const auto& c : cos.getCarti()) {
		std::string textLista = c.getTitlu() + "|" +
			c.getAutor() + "|" +
			c.getGen() + "|" +
			std::to_string(c.getAnAparitie());

		listaCos->addItem(QString::fromStdString(textLista));
	}
}

void CosGUI::connectSignals() {

	//exit
	QObject::connect(btnExit, &QPushButton::clicked, this, [this]() {
		close();
		});

	//goleste
	QObject::connect(btnGoleste, &QPushButton::clicked, this, [this]() {
		cos.goleste();
		reloadCosList();
		});

	//adauga
	QObject::connect(btnAdauga, &QPushButton::clicked, this, [this]() {
		std::string titlu = editTitlu->text().toStdString();

		try {
			cos.adauga(titlu);

			reloadCosList();

			editTitlu->clear();
		}
		catch (const AppException& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.what()));
		}

		});

	//genereaza
	QObject::connect(btnGenereaza, &QPushButton::clicked, this, [this]() {
		int numar = editNumarCarti->text().toInt();

		try {
			cos.genereaza(static_cast<size_t>(numar));

			reloadCosList();

			editNumarCarti->clear();

		}
		catch (const AppException& ex) {
			QMessageBox::warning(this, "Eroare", QString::fromStdString(ex.what()));
		}

		});
}