#include "service.h"
#include "fisierRepo.h"
#include <algorithm>

Service::Service(FisierRepo& repo) : repo { repo }{}

const vector<Echipament> &Service::getAll() const noexcept { return repo.getAll(); }

vector<Echipament> Service::filtrareDupaBrand(string brd) {

	vector<Echipament> rezultat;
	for (const auto& e : repo.getAll()) {
		if (e.getBrand() == brd)
			rezultat.push_back(Echipament{ e.getCod(), e.getCategorie(), e.getBrand(), e.getMarime() });
	}
	return rezultat;
}
