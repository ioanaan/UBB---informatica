#pragma once
#include <map>
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "service.h"
#include "cos.h"

class GUI : public QWidget {
private:

	Service& serv;
	Cos& cos;

	QListWidget* listaCarti = new QListWidget;
	QLineEdit* editTitlu = new QLineEdit;
	QLineEdit* editAutor = new QLineEdit;
	QLineEdit* editGen = new QLineEdit;
	QLineEdit* editAn = new QLineEdit;

	QPushButton* btnAdauga = new QPushButton{ "&Adauga" };
	QPushButton* btnSterge = new QPushButton{ "&Sterge" };
	QPushButton* btnModifica = new QPushButton{ "&Modifica" };
	QPushButton* btnUndo = new QPushButton{ "&Undo" };
	QPushButton* btnSortTitlu = new QPushButton{ "Sortare &Titlu" };
	QPushButton* btnSortAutor = new QPushButton{ "Sortare &Autor" };
	
	QPushButton* btnCos = new QPushButton{ "Deschide &Cos" };
	QPushButton* btnExit = new QPushButton{ "&Exit" };

	void initGUI();
	void connectSignals();
	void reloadList(const std::vector<Carte>& carti);



	QWidget* widgetDinamic = new QWidget;
	QVBoxLayout* layoutDinamic = new QVBoxLayout;

	void incarcaButoaneDinamic();

public:
	GUI(Service& s, Cos& c) : serv{ s }, cos{ c } {
		initGUI();
		connectSignals();
		reloadList(serv.getCarti());

		incarcaButoaneDinamic();
	}

};