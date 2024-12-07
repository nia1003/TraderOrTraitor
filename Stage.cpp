#include "Stage.h"

const unordered_map<string, array<int, 11>> Stage::price_per_round = 
{
    {"AAPL", {150, 159, 114, 127, 133, 184, 174, 177, 177, 206, 206}},
    {"MSFT", {280, 290, 209, 233, 241, 308, 286, 280, 269, 314, 314}},
    {"UBER", {55, 55, 26, 29, 32, 48, 46, 50, 43, 49, 54}},
    {"MRNA", {150, 150, 47, 66, 81, 136, 163, 163, 118, 93, 74}},
    {"COST", {520, 551, 434, 434, 450, 558, 568, 559, 579, 634, 634}},
    {"KO", {60, 63, 47, 47, 49, 62, 64, 62, 64, 71, 71}},
    {"TSM", {120, 134, 80, 74, 74, 93, 91, 116, 93, 90, 64}},
    {"INTC", {55, 61, 36, 33, 33, 43, 43, 36, 49, 58, 78}},
    {"UAL", {40, 44, 22, 22, 24, 35, 38, 38, 33, 30, 35}}, // 3
    {"DAL", {45, 50, 26, 26, 28, 41, 43, 43, 37, 34, 40}} // 3
};

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