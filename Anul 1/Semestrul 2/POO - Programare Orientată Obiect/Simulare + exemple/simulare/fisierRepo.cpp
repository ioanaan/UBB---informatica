#include "fisierRepo.h"
#include "echipament.h"
#include <fstream>
#include <sstream>

FisierRepo::FisierRepo(const string& filename) 
	: filename{ filename } {
	incarcaDinFisier();
}

void FisierRepo::incarcaDinFisier() {

	ifstream f("echipamente.txt");
	string linie;
	while (getline(f, linie)) {
		stringstream ss(linie);
		string tokenCod, categorie, brand, marime;

		getline(ss, tokenCod, ',');
		getline(ss, categorie, ',');
		getline(ss, brand, ',');
		getline(ss, marime, ',');

		int cod = stoi(tokenCod);

		echipamente.push_back(Echipament{ cod, categorie, brand, marime });

	}
}

void FisierRepo::salveazaInFisier() const {

	ofstream f("echipamente.txt");
	for (const auto& e : echipamente) {
		f << e.getCod() << "," << e.getCategorie() << "," << e.getBrand() << "," << e.getMarime() << "\n";
	}
}

const vector<Echipament>& FisierRepo::getAll() const noexcept { return echipamente; }