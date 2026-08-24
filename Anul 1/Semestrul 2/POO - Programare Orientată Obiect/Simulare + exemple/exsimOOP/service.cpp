#include "service.h"
#include <algorithm>

Service::Service(FisierRepo& repo) : repo{ repo } {
}

const vector<Rochie> &Service::getAll() const noexcept {
	return repo.getAll();
}

vector<Rochie> Service::sorteazaDupaMarime() const {

	vector<Rochie> copie = repo.getAll();
	sort(copie.begin(), copie.end(), [](const Rochie& a, const Rochie& b) {
		return a.getMarime() < b.getMarime();
	});

	return copie;
}

vector <Rochie> Service::sorteazaDupaPret() const {

	vector<Rochie> copie = repo.getAll();
	sort(copie.begin(), copie.end(), [](const Rochie& a, const Rochie& b) {

		return a.getPret() < b.getPret();
	});

	return copie;
}

void Service::inchiriaza(int cod) {
	repo.modifica(cod);
}