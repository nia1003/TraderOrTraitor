#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <filesystem>


namespace fs = std::filesystem;
fs::path currentPath = fs::current_path();



class Button {
public:
    Button(float x, float y, std::string button_text, float size = 1) {
        // Create a rectangle shape for the button
        sf::RectangleShape button(sf::Vector2f(size * 200.f, size * 150.f));
        
        // Set the button color to black with 40 alpha (transparent black)
        button.setFillColor(sf::Color(0, 0, 0, 40)); // Black color with alpha = 40 (transparent)

        // Set the button position
        button.setPosition(x, y);

        // Load the font for the text
        sf::Font buttonFont;
        if (!buttonFont.loadFromFile("assets/fonts/en_Dhurjati-Regular.ttf")) {
            // Handle error if the font loading fails
            std::cerr << "Error loading font!" << std::endl;
        }

        // Create a text object with the provided button text
        sf::Text text(button_text, font);
        text.setCharacterSize(30);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::Red);

        // Set the text position to be centered within the button
        // Calculate the position based on button size and text size
        float textWidth = text.getLocalBounds().width;
        float textHeight = text.getLocalBounds().height;
        text.setPosition(x + (200.f * size - textWidth) / 2, y + (150.f * size - textHeight) / 2);

        // Assuming you have a window to draw the button
        window.draw(button);
        window.draw(text);
    }

private:
    // Assuming window is declared elsewhere, such as in the main function
    sf::RenderWindow& window;
};

int main()
{
    std::cout << "開始創建遊戲..." << std::endl;
    // 創建 SFML 視窗
    sf::RenderWindow window(sf::VideoMode(1200, 900), "SFML works!");
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
        std::cout << "字體加載成功" << std::endl;
    }

    // 創建文字
    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("Game Start");
    buttonText.setCharacterSize(24); // 設置字體大小
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setStyle(sf::Text::Bold);

    // 創建遊戲和 UI 物件
  
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
