#include "debugger.h"

Debugger::Debugger() {
	//constructor
}

Debugger::~Debugger() {
	//destructor
}

void Debugger::handleException(const char errorMessage[], const bool toExit) {
	if (toExit)
		rlutil::cls();
	std::cerr << "Unexpected Error Occured : " << errorMessage;
	if (toExit) {
		Utilities::print("Terminating Program ...");
		exit(EXIT_FAILURE);
	}
}
