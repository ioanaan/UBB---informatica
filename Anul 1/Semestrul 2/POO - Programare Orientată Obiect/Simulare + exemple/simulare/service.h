#pragma once
#include "fisierRepo.h"
#include "echipament.h"

class Service {
private:
	FisierRepo& repo;

public:
	Service(FisierRepo& repo);

	const vector<Echipament>& getAll() const noexcept;
	vector<Echipament> filtrareDupaBrand(string brd);
	vector<Echipament> sortareDupaMarime();
};