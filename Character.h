#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
// #include <Stock.h>
class Stock{};
using namespace std;

class Character {
protected:
    static const int INIT_MONEY; // 基礎值
    static int currentId; // 模仿SQL的AUTO_INCREMENT
    // 身分相關
    short id; // served as key
    string name;
    string description;
    string info; // 展示currentMoney、stocks等資訊

    // 功能相關
    int initBonus; // 設計成高基礎值多少
    int currentMoney;
    int tradeCntInRound; // 一回合最多可做幾次交易
    vector<Stock*> stocks;
    vector<string> tradeLog; // 交易紀錄：f"{stockName} X {tradeNumber}"

public:
    // 角色創建相關
    Character() {}
    static void resetCurrentId() { Character::currentId = 0; }
    
    // getters
    int getCurrentMoney() const;
    const string& getName() const;
    const string& getDesciption() const;

    // 遊戲背後邏輯相關(輔助遊戲進行)
    void setTradeCntId(int cnt) {  }

    // 遊戲操作相關(玩家有對應操作)
    int getTotalAsset() const; // currentMoney + Σ(s.num * s.price) for s in stocks
    void tradeStocks(int stockId, int number); // number大於0表示買入，小於0表示賣出
    const string& seeOthersInfo(int characterId); // 展示角色資訊
};

const int Character::INIT_MONEY = 10000; // 暫定，全角色共享同樣的值
int Character::currentId = 0;

// 散戶(玩家主要操作角色)
class Retail : public Character {
private:
    
public:
    static const string IDENTITY;
};

const string Retail::IDENTITY = "散戶";

#endif // CHARACTER_H
