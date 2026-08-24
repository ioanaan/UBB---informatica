#pragma once
#include "Repo.h"
#include <string>
#include <vector>

class Service {
private:
	Repository& repo;

public:
	Service(Repository& repo);

	const std::vector<Task>& getAll() const;

	/* sorteaza dupa stare */
	std::vector<Task> getSortedByStare() const;

	/* filtreaza dupa programator */
	std::vector<Task> filtreazaDupaProgramator(const std::string& search) const;

	void adaugaTask(int id, const std::string& descriere, const std::vector<std::string>& programatori, const std::string& stare);

	void schimbaStare(int id, const std::string& stareNoua);
};