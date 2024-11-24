#include "Game.h"
#include "UI.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // 創建 SFML 視窗
    sf::RenderWindow window(sf::VideoMode(800, 600), "Trader or Trailor??");

    // 創建遊戲和 UI 物件
    Game game;
    UI ui;

    // 主遊戲循環
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 遊戲的流程控制（每回合）
        game.runLevelStep(); // 運行遊戲流程中的一個步驟

        // 更新 UI
        ui.update(game.getPlayer(), game.getMarket(), game.getCurrentRound(), game.getTotalRounds(), game.getCurrentLevel());

        // 渲染
        window.clear();
        ui.render(window);
        window.display();

        // 檢查是否完成所有關卡
        if (game.isGameOver())
        {
            std::cout << "\n遊戲結束，恭喜你成功通過所有關卡或達成破產條件！" << std::endl;
            window.close();
        }
    }

    return 0;
}
