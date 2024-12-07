#ifndef STAGE_H
#define STAGE_H

#include "Character.h"
#include "../Event.h"
#include "../Stock.h"
#include <unordered_map>
#include <vector>
using namespace std;
/*
    section1: show some events (not always true)
    section2: players trade (and finance, release news)
    section3: show results after the operaions
*/

class Character;
struct Stage;

struct Round {
    vector<Event*> events;

    Round(vector<Event*>& e) : events(e) {}
    void startRound(Stage& stage);
};

struct Stage {
    vector<Character*> characters;
    unordered_map<string, Stock*> stocks;
    vector<Round> rounds;
    int currentRound;

    Stage(unordered_map<string, Stock*>& s, vector<Round>& r) : stocks(s), rounds(r), currentRound(1) {}
    void startStage();
    int getCurRound() const { return currentRound; }
};

#endif