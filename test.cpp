#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
class Scene
{
public:
    virtual ~Scene() = default;
    virtual void handleInput(sf::RenderWindow &window) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};

// 場景管理器
class SceneManager
{
public:
    void setScene(std::unique_ptr<Scene> scene)
    {
        currentScene = std::move(scene);
    }

    void handleInput(sf::RenderWindow &window)
    {
        if (currentScene)
        {
            currentScene->handleInput(window);
        }
    }

    void draw(sf::RenderWindow &window)
    {
        if (currentScene)
        {
            currentScene->draw(window);
        }
    }

    std::unique_ptr<Scene> &getCurrentScene()
    {
        return currentScene;
    }

private:
    std::unique_ptr<Scene> currentScene;
};

// 自訂的事件類型
enum class ButtonEventType
{
    ButtonPressed
};

struct ButtonPressedEvent
{
    ButtonEventType type;
    std::string buttonName; // 按鈕的名稱或ID
};

class Button {
private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    sf::Font buttonFont;
public:
    Button(float x, float y, const std::string &button_text, float size = 1)
    {
        buttonShape.setSize(sf::Vector2f(size * 200.f, size * 90.f));
        buttonShape.setFillColor(sf::Color(0, 0, 0, 100));
        buttonShape.setPosition(x, y);

        if (!buttonFont.loadFromFile("assets/fonts/en_Dhurjati-Regular.ttf"))
        {
            std::cerr << "Error loading font!" << std::endl;
        }

        buttonText.setFont(buttonFont);
        buttonText.setString(button_text);
        buttonText.setFillColor(sf::Color::White);
        setTextProperties(size);
    }

    void setTextProperties(float size)
    {
        buttonText.setCharacterSize(35 * size);
        float textWidth = buttonText.getLocalBounds().width;
        float textHeight = buttonText.getLocalBounds().height;
        buttonText.setPosition(
            buttonShape.getPosition().x + (buttonShape.getSize().x - textWidth) / 2,
            buttonShape.getPosition().y + (buttonShape.getSize().y - textHeight) / 2);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(buttonShape);
        window.draw(buttonText);
    }

    bool isClicked(sf::RenderWindow &window)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (buttonShape.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                return true;
            }
        }
        return false;
    }


};

// 遊戲畫面場景
class GameScene : public Scene
{

private:
    sf::Font font;
    sf::Text text;
    Button button;
    //有關文字的設定
    void textDependencies(){
        // 載入字型
        if (!font.loadFromFile("assets/fonts/en_Dhurjati-Regular.ttf")){
            std::cerr << "Error loading font!" << std::endl;
        }  
        // 設定文字基本屬性
        text.setFont(font);
        text.setFillColor(sf::Color::White);  // 設置主文字顏色為白色
    }
    
public:
    struct Position{
        float x;
        float y;
    };
    GameScene(){
        
    }

    GameScene(std::string& sceneName){
        // 初始化遊戲畫面 (可以顯示一些遊戲內容)
        // 這裡簡單畫一個顯示 "遊戲中" 的文本
        font.loadFromFile("assets/fonts/en_Dhurjati-Regular.ttf");
        text.setFont(font);
        text.setString("Game is running...");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::White);
        text.setPosition(400, 300);
    }
    void handleInput(sf::RenderWindow &window) override{
        // 這裡處理遊戲畫面的輸入 (如有需要)
    }



    void draw(sf::RenderWindow &window) override{
        window.clear();
        window.draw(text);
        window.display();
    }
    //建立標題敘述（遊戲說明或事件名稱）
    void createTitleText(std::string& titleText, int size = 50, Position& p){
        void textDependencies();
        text.setString(titleText);
        text.setCharacterSize(size);
        text.setPosition(p.x, p.y);
    }
    //建立詳細文字說明（例如事件細節）
    void createDescriptionText(std::string& dsrpText, int size = 30, Position& p)
    {
        void textDependencies();
        text.setString(dsrpText);
        text.setCharacterSize(size);
        text.setPosition(p.x,p.y);
    }

};

class RoleScene : public Scene
{
private:
    sf::Text description;
    sf::Font font;

public:
    RoleScene()
    {
        // 初始化遊戲畫面 (可以顯示一些遊戲內容)
        // 這裡簡單畫一個顯示 "遊戲中" 的文本
        font.loadFromFile("assets/fonts/en_Dhurjati-Regular.ttf");
        description.setFont(font);
        description.setString("請選擇你的身分！"); 
        description.setCharacterSize(50);
        description.setFillColor(sf::Color::White);
        description.setPosition(400, 300);
    }

    void handleInput(sf::RenderWindow &window) override
    {
        // 這裡處理遊戲畫面的輸入 (如有需要)
    }


    void draw(sf::RenderWindow &window) override
    {
        window.clear();
        window.draw(gameText);
        window.display();
    }


};

//class EventScene : public Scene

// 主菜單場景
class MainMenuScene : public Scene
{
private:
    Button startButton, exitButton;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text title;
public:
    MainMenuScene(sf::RenderWindow &window)
        : startButton(window.getSize().x * 0.2f, window.getSize().y * 0.6f, "Start Game"),
          exitButton(window.getSize().x * 0.65f, window.getSize().y * 0.6f, "Exit Game")
    {

        // 加載背景圖像 (只加載一次)
        if (!backgroundTexture.loadFromFile("assets/images/fu.jpg"))
        {
            std::cerr << "無法加載背景圖像" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);

        if (!font.loadFromFile("assets/fonts/en_Dhurjati-Regular.ttf"))
        {
            std::cerr << "無法加載字體" << std::endl;
        }
        title.setFont(font);
        title.setString("TRADER OR TRAITOR");
        title.setCharacterSize(90);           // 設置標題字體大小
        title.setFillColor(sf::Color::White); // 設置標題顏色
        title.setPosition(window.getSize().x * 0.5f - title.getLocalBounds().width * 0.5f, window.getSize().y * 0.1f);
    };

    void handleInput(sf::RenderWindow &window) override
    {
        if (startButton.isClicked(window))
        {
            std::cout << "Start Game clicked!" << std::endl;
            nextScene = std::make_unique<RoleScene>(); // 轉到遊戲畫面
        }

        if (exitButton.isClicked(window))
        {
            window.close(); // 點���退出按鈕後關閉遊��
        }
    }

    void draw(sf::RenderWindow &window) override
    {
        window.clear();

        // 畫出背景
        window.draw(backgroundSprite);
        window.draw(title);
        // 畫出按鈕
        startButton.draw(window);
        exitButton.draw(window);

        window.display();
    }

    std::unique_ptr<Scene> nextScene; // 用於切換到其他場景
};
class Round : public Scene {
private:
    int roundNumber;
    int currentEventIndex; // 用來控制當前事件
    bool roundComplete;

public:
    Round(sf::RenderWindow &window, int round)
        : roundNumber(round), currentEventIndex(0), roundComplete(false) {}

    void handleInput(sf::RenderWindow &window) override {
        if (currentEventIndex < 3) {
            // 如果當前是事件階段，處理事件
            // 你可以通過按鈕點擊或其他事件來決定何時完成該事件
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                currentEventIndex++; // 完成事件，進入下一個事件
            }
        } else if (currentEventIndex == 3) {
            // 當前是交易階段
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                roundComplete = true; // 完成交易，回合結束
            }
        }
    }

    bool isRoundComplete() {
        return roundComplete;
    }

    void draw(sf::RenderWindow &window) override {
        if (currentEventIndex < 3) {
            // 顯示當前的事件場景
            // 比如你可以顯示第 currentEventIndex 個事件
        } else if (currentEventIndex == 3) {
            // 顯示交易場景
        }
    }
};


int main() {
    fs::path current_path = fs::current_path();
    //開啟視窗
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Game works!");
    SceneManager sceneManager;

    // 主頁
    sceneManager.setScene(std::make_unique<MainMenuScene>(window));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // 處理不同場景中的事件
            sceneManager.handleInput(window);
        }

        // 渲染當前場景
        sceneManager.draw(window);

        // 檢查是否需要切換場景
        if (sceneManager.getCurrentScene())
        {
            // 檢查主菜單是否切換到角色選擇場景
            auto *mainMenuScene = dynamic_cast<MainMenuScene *>(sceneManager.getCurrentScene().get());
            if (mainMenuScene && mainMenuScene->nextScene)
            {
                sceneManager.setScene(std::move(mainMenuScene->nextScene));
            }

            // 檢查角色選擇後進入回合
            auto *roleScene = dynamic_cast<RoleScene *>(sceneManager.getCurrentScene().get());
            if (roleScene && roleScene->isCharacterSelected())
            {
                sceneManager.setScene(std::make_unique<Round>(window, 1));  // 開始第1回合
            }

            // 檢查回合完成後切換
            auto *round = dynamic_cast<Round *>(sceneManager.getCurrentScene().get());
            if (round && round->isRoundComplete())
            {
                static int roundCount = 1;
                roundCount++;  // 開始下一回合

                if (roundCount <= 10)
                {
                    // 開始新回合
                    sceneManager.setScene(std::make_unique<Round>(window, roundCount));
                }
                else
                {
                    // 10回合結束，進入遊戲結束場景
                    sceneManager.setScene(std::make_unique<GameOverScene>(window));
                }
            }
        }
    }

    return 0;
}











// int main()
// {
//     fs::path current_path = fs::current_path();
//     sf::RenderWindow window(sf::VideoMode(1200, 800), "Game works!");
//     SceneManager sceneManager;
//     // 設置起始場景為主菜單
//     sceneManager.setScene(std::make_unique<MainMenuScene>(window));

//     sf::Clock clock;
    
//     int roundCount = 0;

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//             {
//                 window.close();
//             }
//         }

//         // 處理輸入、更新和繪製
//         sceneManager.handleInput(window);
//         sceneManager.draw(window);

//         // 檢查是否需要切換場景
//         if (sceneManager.getCurrentScene())
//         {
//             auto *mainMenuScene = dynamic_cast<MainMenuScene *>(sceneManager.getCurrentScene().get());
//             if (mainMenuScene && mainMenuScene->nextScene)
//             {
//                 // 從主菜單進入角色選擇場景
//                 sceneManager.setScene(std::move(mainMenuScene->nextScene));
//             }
//         }

//         // 當角色選擇場景結束後開始回合循環
//         if (sceneManager.getCurrentScene())
//         {
//             auto *roleScene = dynamic_cast<RoleScene *>(sceneManager.getCurrentScene().get());
//             if (roleScene && roleScene->isCharacterSelected())
//             {
//                 // 角色選擇完成後，進入回合
//                 roundCount = 1;  // 開始第 1 回合
//                 sceneManager.setScene(std::make_unique<Round>(window, roundCount));
//             }
//         }

//         // 在回合內管理場景切換
//         if (roundCount > 0 && roundCount <= 10)
//         {
//             auto *round = dynamic_cast<Round *>(sceneManager.getCurrentScene().get());
//             if (round)
//             {
//                 if (round->isRoundComplete())
//                 {
//                     roundCount++;  // 回合結束，進入下一回合

//                     if (roundCount <= 10)
//                     {
//                         // 開始新回合
//                         sceneManager.setScene(std::make_unique<Round>(window, roundCount));
//                     }
//                     else
//                     {
//                         // 遊戲結束，進入結束場景
//                         sceneManager.setScene(std::make_unique<GameOverScene>(window));
//                     }
//                 }
//             }
//         }
//     }

//     return 0;
// }







// int main() {
//     // 創建視窗
//     sf::RenderWindow window(sf::VideoMode(1200, 800), "Game works!");

//     // 加載字體
//     sf::Font font;
//     if (!font.loadFromFile("assets/fonts/en_Dhurjati-Regular.ttf")) {
//         std::cerr << "無法加載字體" << std::endl;
//         return -1;
//     }

//     // 加載背景圖像 (只加載一次)
//     sf::Texture backgroundTexture;
//     if (!backgroundTexture.loadFromFile("assets/images/fu.jpg")) { // 確保路徑正確
//         std::cerr << "無法加載背景圖像" << std::endl;
//         return -1;
//     }

//     sf::Sprite backgroundSprite(backgroundTexture);

//     // 創建按鈕 (只創建一次)
//     Button startButton(300.f, 250.f, "Game Start", 1);
//     Button exitButton(500.f, 250.f, "Exit Game", 1);

//     std::cout << "遊戲創建成功，正在進入遊戲..." << std::endl;

//     // 檢查是否點擊了 Start 或 Exit 按鈕
//     if (startButton.isClicked(window)) {
//         std::cout << "Start Game clicked!" << std::endl;
//         // 這裡可以加入開始遊戲的邏輯，例如轉到遊戲主畫面
//     }

//     if (exitButton.isClicked(window)) {
//         std::cout << "Exit clicked!" << std::endl;
//         window.close();  // 點擊退出按鈕後關閉遊戲
//     }
//     // 遊戲主循環
//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }

//             // 視窗大小調整事件
//             if (event.type == sf::Event::Resized) {
//                 sf::Vector2u newSize = window.getSize();
//                 float newWidth = static_cast<float>(newSize.x);
//                 float newHeight = static_cast<float>(newSize.y);

//                 // 根據新的視窗大小調整按鈕位置
//                 startButton = Button(newWidth * 0.3f, newHeight * 0.4f, "Game Start", 1);
//                 exitButton = Button(newWidth * 0.5f, newHeight * 0.4f, "Exit Game", 1);

//                 // 更新按鈕內的文字
//                 startButton.update(1);
//                 exitButton.update(1);
//             }
//         }

//         // 清除畫面
//         window.clear();

//         // 顯示背景圖像
//         window.draw(backgroundSprite);

//         // 顯示按鈕
//         startButton.draw(window);
//         exitButton.draw(window);

//         // 顯示更新
//         window.display();
//     }

//     std::cout << "遊戲程序結束" << std::endl;
//     return 0;
// }
