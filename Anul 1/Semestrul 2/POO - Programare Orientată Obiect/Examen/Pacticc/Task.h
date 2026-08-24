#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Task {
private:
	int id;
	std::string descriere;
	std::vector<std::string> programatori;
	std::string stare;

public:
	Task(const int id, const std::string& descriere, const std::vector<std::string>& programatori, const std::string& stare);

	int getId() const;
	const std::string& getDescriere() const;
	const std::vector<std::string>& getProgramatori() const;
	const std::string& getStare() const;
	void setStare(const std::string& stareNoua);

	std::string getProgramatoriStr() const;

};