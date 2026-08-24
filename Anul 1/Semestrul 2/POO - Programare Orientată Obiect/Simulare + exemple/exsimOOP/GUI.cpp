#include "GUI.h"
#include <exception>

void GUI::initGUI() {

	QVBoxLayout* layoutMain = new QVBoxLayout;

	QHBoxLayout* layoutJOS = new QHBoxLayout;
	layoutJOS->addWidget(btnInchiriere);
	layoutJOS->addWidget(btnSortareMarime);
	layoutJOS->addWidget(btnSortarePret);
	layoutJOS->addWidget(btnNesortat);
	layoutJOS->addWidget(btnExit);

	layoutMain->addWidget(listaRochii);
	layoutMain->addLayout(layoutJOS);

	this->setLayout(layoutMain);
}

void GUI::reloadList(const vector<Rochie>& rochii) {
	listaRochii->clear();
	for (const auto& r : rochii) {

		QString text = QString::fromStdString(r.getDenumire()) + "|" 
			         + QString::fromStdString(r.getMarime()) + "|" 
			         + QString::number(r.getPret());
		QListWidgetItem* item = new QListWidgetItem(text);
		item->setData(Qt::UserRole, r.getCod());
		item->setBackground(r.getDisponibila() ? Qt::green : Qt::red);
		listaRochii->addItem(item);

	}

}

void GUI::connectSignals() {

	//exit
	QObject::connect(btnExit, &QPushButton::clicked, this, [this]() {
		close();
	});

	//sortMarime
	QObject::connect(btnSortareMarime, &QPushButton::clicked, this, [this]() {
		reloadList(service.sorteazaDupaMarime());
	});

	//sortPret
	QObject::connect(btnSortarePret, &QPushButton::clicked, this, [this]() {
		reloadList(service.sorteazaDupaPret());
	});

	//nesort
	QObject::connect(btnNesortat, &QPushButton::clicked, this, [this]() {
		reloadList(service.getAll());
	});

	//inchiriere
	QObject::connect(btnInchiriere, &QPushButton::clicked, this, [this]() {
		auto selectat = listaRochii->currentItem();
		if (selectat == nullptr) return;
		int cod = selectat->data(Qt::UserRole).toInt();

		try {
			service.inchiriaza(cod);
			reloadList(service.getAll());
		}
		catch (const std::exception&) {
			QMessageBox::warning(this, "Eroare", "Rochia este deja inchiriata.");
		}
	});
}