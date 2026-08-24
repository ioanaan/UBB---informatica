#pragma once
#include "fisierRepo.h"

class Service {
private: 
	FisierRepo& repo;

public:
	Service(FisierRepo& repo);

	const vector<Rochie>& getAll() const noexcept;
	void inchiriaza(int cod);
	vector<Rochie> sorteazaDupaMarime() const;
	vector<Rochie> sorteazaDupaPret() const;
};