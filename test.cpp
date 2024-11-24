#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

//this is a temporary test for user interface
// this can be removed once main.cpp is finished

namespace fs = std::filesystem;

fs::path currentPath = fs::current_path();

int main()
{
    std::cout << "開始創建遊戲..." << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::RectangleShape startButton(sf::Vector2f(200.f, 100.f));
    startButton.setFillColor(sf::Color::Green);
    startButton.setPosition(300.f, 250.f); // 將矩形框放在窗口中央


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

    // 創建文字
    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("Game Start");
    buttonText.setCharacterSize(24); // 設置字體大小
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setStyle(sf::Text::Bold);

    // 設置文字的位置在按鈕的中心
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setPosition(
        startButton.getPosition().x + (startButton.getSize().x - textBounds.width) / 2 - textBounds.left,
        startButton.getPosition().y + (startButton.getSize().y - textBounds.height) / 2 - textBounds.top
    );

    std::cout << "遊戲創建成功，正在進入遊戲..." << std::endl;
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                std::cout << "正在停止遊戲..." << std::endl;
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        std::cout << "已點擊開始按鈕，遊戲開始" << std::endl;
                        std::cout << "ctrl + c 以退出遊戲" <<std::endl;
                    }
                }
            }
        }

        window.clear();
        window.draw(startButton);    // 繪製按鈕
        window.draw(buttonText);     // 繪製按鈕上的文字
        window.display();
    }

    std::cout << "遊戲程序結束" << std::endl;

    return 0;
}
