#define UI_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Market.h"
#include "UI.h"
#include <iostream>

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



UI::UI() {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "無法加載字體文件" << std::endl;
    }

    title.setFont(font);
    title.setString("股票交易遊戲");
    title.setCharacterSize(30);
    title.setPosition(200, 10);
    title.setFillColor(sf::Color::White);

    playerInfo.setFont(font);
    playerInfo.setCharacterSize(20);
    playerInfo.setPosition(20, 60);
    playerInfo.setFillColor(sf::Color::White);

    marketInfo.setFont(font);
    marketInfo.setCharacterSize(20);
    marketInfo.setPosition(20, 150);
    marketInfo.setFillColor(sf::Color::White);

    roundInfo.setFont(font);
    roundInfo.setCharacterSize(20);
    roundInfo.setPosition(20, 500);
    roundInfo.setFillColor(sf::Color::Cyan);

    levelInfo.setFont(font);
    levelInfo.setCharacterSize(20);
    levelInfo.setPosition(20, 530);
    levelInfo.setFillColor(sf::Color::Green);
}

void UI::update(const Player& player, const Market& market, int currentRound, int totalRounds, int currentLevel) {
    std::string playerText = "玩家: " + player.name + "\n現金: $" + std::to_string(player.cash) + "\n持有股票：\n";
    for (const auto& pair : player.stocks) {
        playerText += " - " + pair.first + ": " + std::to_string(pair.second) + " 股\n";
    }
    playerInfo.setString(playerText);

    std::string marketText = "當前市場行情：\n";
    for (const auto& stock : market.stocks) {
        marketText += " - " + stock.name + ": $" + std::to_string(stock.price) + "\n";
    }
    marketInfo.setString(marketText);

    roundInfo.setString("當前回合: " + std::to_string(currentRound) + " / " + std::to_string(totalRounds));
    levelInfo.setString("當前關卡: " + std::to_string(currentLevel));
}

void UI::render(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(playerInfo);
    window.draw(marketInfo);
    window.draw(roundInfo);
    window.draw(levelInfo);
}

