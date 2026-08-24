#include "Task.h"

Task::Task(int id, const std::string& descriere, const std::vector<std::string>& programatori, const std::string& stare)
	: id(id), descriere(descriere), programatori(programatori), stare(stare) { }

/* getter id */
int Task::getId() const {
	return id;
}

/* getter descriere */
const std::string& Task::getDescriere() const {
	return descriere;
}

/* getter programatori */
const std::vector<std::string>& Task::getProgramatori() const {
	return programatori;
}

/* getter stare */
const std::string& Task::getStare() const {
	return stare;
}
/* setter stare */
void Task::setStare(const std::string& stareNoua) { stare = stareNoua; }

std::string Task::getProgramatoriStr() const {
    std::string result;
    for (int i = 0; i < (int)programatori.size(); i++) {
        result += programatori[i];
        if (i < (int)programatori.size() - 1)
            result += ", ";
    }
    return result;
}