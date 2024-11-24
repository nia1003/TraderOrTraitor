#ifndef GAME_H
#define GAME_H

#include "Market.h"
#include "Player.h"
#include "Event.h"

class Game {
public:
    Game();
    void runLevelStep();
    Player& getPlayer();
    Market& getMarket();
    int getCurrentRound() const;
    int getTotalRounds() const;
    int getCurrentLevel() const;
    bool isGameOver() const;

private:
    Market market;
    Player player;
    EventManager eventManager;
    int totalRounds;
    int currentRound;
    int currentLevel;
    bool gameOver;
};

#endif
