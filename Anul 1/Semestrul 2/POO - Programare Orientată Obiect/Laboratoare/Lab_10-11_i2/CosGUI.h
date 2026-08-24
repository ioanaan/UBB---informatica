#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "cos.h"

class CosGUI : public QWidget {
private:
	Cos& cos;

	QListWidget* listaCos = new QListWidget;
	QLineEdit* editTitlu = new QLineEdit;
	QLineEdit* editNumarCarti = new QLineEdit;
	QLineEdit* editExport = new QLineEdit;

	QPushButton* btnAdauga = new QPushButton("&Adauga in cos");
	QPushButton* btnGenereaza = new QPushButton("&Genereaza aleator");
	QPushButton* btnGoleste = new QPushButton("&Goleste cos");
	QPushButton* btnExport = new QPushButton{ "&Exporta Cos" };
	QPushButton* btnExit = new QPushButton{ "&Exit" };

	void initGUI();
	void connectSignals();
	void reloadCosList();

public:
	CosGUI(Cos& c) : cos{ c } {
		initGUI();
		connectSignals();
		reloadCosList();
	}

};