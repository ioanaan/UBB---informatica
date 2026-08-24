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

	QListWidget* listaEchipamente = new QListWidget;

	QLineEdit* fBrand = new QLineEdit;

	QPushButton* btnSortareMarime = new QPushButton{ "&Sorteaza marime" };
	QPushButton* btnFiltrareBrand = new QPushButton{ "&Filtrare brand" };
	QPushButton* btnReset = new QPushButton{ "&Reset" };
	QPushButton* btnExit = new QPushButton{ "&Exit" };

	void initGUI();
	void connectSignals();
	void reloadList(const vector<Echipament>& echipamente);

public:
	GUI(Service& service) : service{ service } {
		initGUI();
		connectSignals();
		reloadList(service.getAll());
	}

};