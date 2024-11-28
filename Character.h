#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <array>
#include "Stock.h"
using namespace std;

struct Asset {
    int number;
    Stock* stock;
    Asset(int n, Stock* s) : number(n), stock(s) {}
    int getValue() const { return number * stock->getCurrentPrice(); }
};

class Character {
protected:
    static const int INIT_MONEY; // 基礎值
    static int currentId; // 模仿SQL的AUTO_INCREMENT
    // 身分相關
    short id; // served as key
    string name;
    string description;

    // 功能相關
    // int initBonus; // 設計成高基礎值多少
    int currentMoney;
    int tradeCntInRound; // 一回合最多可做幾次交易
    vector<Asset> assets;
    vector<Asset> tradeLog; // 交易紀錄

public:
    // 角色創建相關
    Character(const string& n, const string& des);
    static void resetCurrentId() { Character::currentId = 0; }
    
    // getters
    // int getCurrentMoney() const { return this->currentMoney; };
    // const string& getName() const { return this->name; };
    // const string& getDesciption() const { return this->description; };

    // 遊戲背後邏輯相關(輔助遊戲進行)
    int getTotalAsset() const; // currentMoney + Σ(s.num * s.price) for s in stocks
    void setTradeCntId(int cnt) { this->tradeCntInRound = cnt; }
    virtual void performOperations() = 0; // 實現各自的操作策略

    // 遊戲操作相關(玩家有對應操作)
    virtual string showIntroduction() const; // 展示身分、名字、介紹
    string showFinancialStatus() const; // 展示currentMoney、stocks
    string seeTradeLog() const;

    // testing
    void addAsset(const Asset& a) { assets.push_back(a); }
};

/*
    散戶：資金加成{0, 500}, 操作次數調整：0
*/
class Player : public Character {
private:
    const array<short, 2> initBonusRange; // 設計成高基礎值多少(隨機值)
    int tradeCntAdjust;
public:
    const string identity;

    Player(const string& iden, const array<short, 2>& range, int cntAdjust,  const string& n, const string& des);
    static const string IDENTITY;
    const string& seeOthersInfo(int characterId); // 查看自己或對手的資訊
    void tradeStocks(int stockId, int number); // number大於0表示買入，小於0表示賣出
    string showIntroduction() const override;

    void performOperations() override {} // temp
};

/*
    直接用Player類別做出散戶、富二代等玩家等類別，
    假設兩者只差在初始資金(富二代多)和操作次數(散戶多)
*/

class Robot : public Character {
protected:
};

#endif // CHARACTER_H
