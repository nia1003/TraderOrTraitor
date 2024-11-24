#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Market.h"

class UI {
public:
    UI();
    void update(const Player& player, const Market& market, int currentRound, int totalRounds, int currentLevel);
    void render(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text title;
    sf::Text playerInfo;
    sf::Text marketInfo;
    sf::Text roundInfo;
    sf::Text levelInfo;
};

#endif
