#ifndef GAME_H
#define GAME_H

#include "Market.h"
#include "Player.h"
#include "Event.h"
#include <iostream>
#include <vector>
#include <string>


struct Stock {
    std::string stockName;
    int stockPrice;
    int stockQuantity;
};

class Game {
private:

    const int START_CURRENCY;
    const int START_INTEREST_RATE;
    const Stock START_STOCKHOLDINGS;
    const int TOTAL_ROUNDS = 10;

public:
    // costructor & destructor
    Game();
    virtual ~Game();

    void runGame();
    void runLevelStep();
    Player& getPlayer();
    Market& getMarket();
    int getCurrentRound() const;
    int getTotalRounds() const;
    int getCurrentLevel() const;
    bool isGameOver() const;
};

class Level1::Game {
private:
   
public:
    
};



#endif
