#include "util.h"

Utilities::Utilities() {
	//constructor
}

Utilities::~Utilities() {
	//destructor
}

const char *Utilities::defaultHighscoreFileName = "highscore_data.txt";

void Utilities::print(const std::string &info, const bool lineEnd, const int color, const int delay) {
	rlutil::setColor(color);
	for (unsigned int i = 0; i < info.size(); i++) {
		rlutil::msleep(delay);
		std::cout << info[i];
	}

	rlutil::msleep(delay * 5);
	if (lineEnd)
		std::cout << std::endl;

	rlutil::setColor(Utilities::defaultTextColor);
}

int Utilities::getRandomNumber(const int leftLimit, const int rightLimit) {
	return (rand() % (rightLimit - leftLimit + 1) + leftLimit);
}
