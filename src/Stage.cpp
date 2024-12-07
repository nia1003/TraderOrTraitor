#include "Stage.h"
#include "Character.h"

void Stage::startStage() {
    for(Round r: rounds) {
        r.startRound(*this);
        ++currentRound;
    }
}

void Round::startRound(Stage& stage) {
    for(auto c = stage.characters.rbegin(); c != stage.characters.rend(); ++c) {
        (*c)->takeAction(stage, *this);
    }
}