#ifndef DEBUGGER_H
#define DEBUGGER_H
#include <iostream>
#include <string>

#include "util.h"

class Debugger {
  public:
	Debugger();
	virtual ~Debugger();

	static void handleException(const char message[], const bool toExit = false);
};

#endif
