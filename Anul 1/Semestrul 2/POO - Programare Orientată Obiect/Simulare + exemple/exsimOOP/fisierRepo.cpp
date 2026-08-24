#include "fisierRepo.h"
#include "rochie.h"
#include <fstream>
#include <sstream>

FisierRepo::FisierRepo(const string& filename)
	: filename{ filename } {
	incarcaDinFisier();
}

void FisierRepo::incarcaDinFisier() {

	ifstream f(filename);

	string linie;
	while (getline(f, linie)) {

		stringstream ss(linie);
		string tokenCod, denumire, marime, tokenPret, tokenDisp;

		getline(ss, tokenCod, ',');
		getline(ss, denumire, ',');
		getline(ss, marime, ',');
		getline(ss, tokenPret, ',');
		getline(ss, tokenDisp, ',');

		int cod = stoi(tokenCod);
		double pret = stod(tokenPret);
		bool disp = (tokenDisp == "True");

		rochii.push_back(Rochie{ cod, denumire, marime, pret, disp });
	}
}

void FisierRepo::salveazaInFisier() const {

	ofstream f(filename);

	for (const auto& r : rochii) {

		f << r.getCod() << "," << r.getDenumire() << "," << r.getMarime() << "," <<
			r.getPret() << "," << (r.getDisponibila() ? "True" : "False") << "\n";
	}
}

void FisierRepo::modifica(int cod) {

	for (auto& r : rochii) {
		if (r.getCod() == cod) {
			if (r.getDisponibila()) {
				r.setDisponibila(false);
				salveazaInFisier();
				return ;
			}
			else throw runtime_error("Rochia nu este disponibila!");
		}
	}
	throw runtime_error("Rochia nu exista!");
}


const vector<Rochie>& FisierRepo::getAll() const noexcept { return rochii; }