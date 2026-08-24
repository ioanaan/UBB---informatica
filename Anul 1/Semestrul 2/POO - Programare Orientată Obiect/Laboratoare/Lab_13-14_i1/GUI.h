#pragma once
#include <map>
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QGroupBox>
#include "service.h"
#include "cos.h"

class GUI : public QWidget {
private:

	Service& serv;
	Cos& cos;

	QListWidget* listaCarti = new QListWidget;
	QTableWidget* tabelCarti = new QTableWidget;

	QLineEdit* editTitlu = new QLineEdit;
	QLineEdit* editAutor = new QLineEdit;
	QLineEdit* editGen = new QLineEdit;
	QLineEdit* editAn = new QLineEdit;

	QPushButton* btnAdauga = new QPushButton{ "&Adauga" };
	QPushButton* btnSterge = new QPushButton{ "&Sterge" };
	QPushButton* btnModifica = new QPushButton{ "&Modifica" };
	QPushButton* btnCauta = new QPushButton{ "Ca&uta" };
	QPushButton* btnPopuleaza = new QPushButton{ "&Populeaza" };
	QPushButton* btnUndo = new QPushButton{ "&Undo" };
	
	//pt cos
	QPushButton* btnCosCRUD = new QPushButton{ "Cos &CRUD" };
	QPushButton* btnCosReadOnly = new QPushButton{ "Cos &ReadOnly" };
	QPushButton* btnCosAdauga = new QPushButton{ "Cos: &Adauga" };
	QPushButton* btnCosGenereaza = new QPushButton{ "Cos: &Genereaza" };
	QPushButton* btnCosGoleste = new QPushButton{ "Cos: &Goleste" };
	QPushButton* btnCosModelView = new QPushButton{ "Cos &ModelView" };

	QLineEdit* editCosTitlu = new QLineEdit;
	QLineEdit* editCosNumar = new QLineEdit;

	QPushButton* btnExit = new QPushButton{ "&Exit" };

	QComboBox* comboSortare = new QComboBox;
	QPushButton* btnSortare = new QPushButton{ "&Sorteaza" };

	QComboBox* comboFiltru = new QComboBox;
	QLineEdit* editFiltru = new QLineEdit;
	QPushButton* btnFiltru = new QPushButton{ "&Filtreaza" };
	QPushButton* btnReload = new QPushButton{ "Arata &Toate" };

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