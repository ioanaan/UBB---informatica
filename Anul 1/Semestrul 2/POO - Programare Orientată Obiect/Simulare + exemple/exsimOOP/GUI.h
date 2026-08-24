#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include "service.h"

class GUI : public QWidget {
private:
	Service& service;

	QListWidget* listaRochii = new QListWidget;

	QPushButton* btnInchiriere = new QPushButton{ "&Inchiriere" };
	QPushButton* btnSortareMarime = new QPushButton{ "&Sorteaza marime" };
	QPushButton* btnSortarePret = new QPushButton{ "&Sorteaza pret" };
	QPushButton* btnNesortat = new QPushButton{ "&Nesortat" };
	QPushButton* btnExit = new QPushButton{ "&Exit" };

	void initGUI();
	void connectSignals();
	void reloadList(const vector<Rochie>& rochii);

public:
	GUI(Service& service) : service{ service } {
		initGUI();
		connectSignals();
		reloadList(service.getAll());
	}

};