#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Task.h"

using namespace std;

class Repository {
private:
	std::vector<Task> tasks;
	std::string filename;

	/* inarcare din fisier */
	void loadFromFile();

	/* salvare in fisier */
	void saveToFile();

public:
	Repository(const std::string& filename);

	/* ret toate task */
	const std::vector<Task>& getAll() const;

	/* adaugare task  */
	void add(const Task& t);
	size_t size() const;

	/* schimbare stare */
	void schimbaStare(int id, const std::string& stareNoua);

};