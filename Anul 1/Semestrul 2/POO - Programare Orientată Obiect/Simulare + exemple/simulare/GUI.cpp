#include "GUI.h"
#include <exception>

void GUI::initGUI() {

	QVBoxLayout* layoutMain = new QVBoxLayout;

	QHBoxLayout* layoutJOS = new QHBoxLayout;
	layoutJOS->addWidget(btnSortareMarime);
	layoutJOS->addWidget(btnFiltrareBrand);
	layoutJOS->addWidget(btnReset);
	layoutJOS->addWidget(btnExit);

	layoutMain->addWidget(listaEchipamente);
	layoutMain->addLayout(layoutJOS);

	this->setLayout(layoutMain);
}

void GUI::reloadList(const vector<Echipament>& echipamente) {
	listaEchipamente->clear();
	for (const auto& e : echipamente) {

		QString text = QString::fromStdString(e.getCategorie()) + "|"
			+ QString::fromStdString(e.getBrand()) + "|"
			+ QString::fromStdString(e.getMarime());
		QListWidgetItem* item = new QListWidgetItem(text);
		item->setData(Qt::UserRole, e.getCod());
		listaEchipamente->addItem(item);

	}

}

void GUI::connectSignals() {

	//exit
	QObject::connect(btnExit, &QPushButton::clicked, this, [this]() {
		close();
		});

	//reset
	QObject::connect(btnReset, &QPushButton::clicked, this, [this]() {
		reloadList(service.getAll());
		});
}