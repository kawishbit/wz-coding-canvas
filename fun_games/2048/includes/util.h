#ifndef UTILITIES_H
#define UTILITIES_H

#include "rlutil.h"
#include "debugger.h"

class Utilities
{
public:
    Utilities();
    virtual ~Utilities();

    static const int defaultDelay = 20;
    static const char *defaultHighscoreFileName;
    static const int defaultTextColor = rlutil::COLORS::BLACK;
    static void print(const std::string &info, const bool lineEnd = true, const int color = Utilities::defaultTextColor, const int delay = Utilities::defaultDelay);
    static int getRandomNumber(const int leftLimit, const int rightLimit);

protected:
private:
};

#endif // UTILITIES_H
