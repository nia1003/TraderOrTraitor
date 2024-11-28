#ifndef ROUND_H
#define ROUND_H

#include "Character.h"
#include <unordered_map>
using namespace std;
/*
    section1: show events
    section2: players trade (and finance, release news)
    section3: show results after the operaions
*/

class Round {
private: // for testing
public:

};

class Stage {
private:
    unordered_map<int, Character*> characters;
};

#endif