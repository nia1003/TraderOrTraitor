#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <filesystem>
#include "Game.h"
#include "UI.h"

namespace fs = std::filesystem;
fs::path currentPath = fs::current_path();

int main()
{
    std::cout << "開始創建遊戲..." << std::endl;
    // 創建 SFML 視窗
    sf::RenderWindow window(sf::VideoMode(1200, 900), "SFML works! Game: Trader or Trailor");
    sf::RectangleShape startButton(sf::Vector2f(200.f, 100.f));
    startButton.setFillColor(sf::Color::Green);
    startButton.setPosition(300.f, 100.f); // 將矩形框放在窗口中央


    // 取得當前執行檔案所在的目錄
    fs::path currentPath = fs::current_path();
    fs::path fontPath = currentPath / "assets/fonts/en_Dhurjati-Regular.ttf"; // 將當前路徑與資源相對路徑結合


    // 加載字體
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/en_Dhurjati-Regular.ttf")) // 使用你本地的字體文件
    {
        std::cerr << "無法加載字體" << std::endl;
        return -1;
    }
    else{
        cout << "字體加載成功" << endl;
    }

    // 創建文字
    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("Game Start");
    buttonText.setCharacterSize(24); // 設置字體大小
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setStyle(sf::Text::Bold);

    // 創建遊戲和 UI 物件
    //創建三個關卡
    gameLevel Level1;
    gameLevel Level2;
    gameLevel Level3;
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
