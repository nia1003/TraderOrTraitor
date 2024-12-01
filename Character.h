#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <array>
#include "Stock.h"
using namespace std;

class Skill{};

struct Asset {
    int number;
    int roundCnt; // 持有回合數
    Stock* stock;
    Asset(int n, Stock* s) : number(n), stock(s) {}
    int getValue() const { return number * stock->getCurrentPrice(); }
};

class ControlType;

class Character {
protected:
    static int currentId; // 模仿SQL的AUTO_INCREMENT

    // 身分相關
    short id; // served as key in Stage's characters array
    string name;
    string description;

    // 功能相關
    ControlType* control;
    int currentMoney;
    int remainingActionCnt;
    vector<Asset> assets;
    vector<string> actionLog; // 操作紀錄
    vector<Skill*> skills;

public:
    // 角色創建相關
    Character(const string& n, const string& des);
    static void resetCurrentId() { Character::currentId = 0; }
    
    // getters
    const string& getName() const { return this->name; };

    // 遊戲背後邏輯相關(輔助遊戲進行)
    void obtainSkills(Skill* s) { skills.push_back(s); }
    int getTotalAsset() const; // currentMoney + Σ(s.num * s.price) for s in stocks
    virtual void resetActionCnt() = 0;
    virtual void takeAction() = 0; // 實現各自的操作策略

    // 遊戲操作相關(玩家有對應操作)
    void useSkill();
    void tradeStocks(const string& ticker, int number); // number大於0表示買入，小於0表示賣出
    string showIntroduction() const; // 展示身分、名字、介紹
    string showFinancialStatus() const; // 展示currentMoney、stocks
    string showTradeLog() const;

    // testing
    void addAsset(const Asset& a) { assets.push_back(a); }
};


class ControlType {
public:
    virtual void makeDesicion(Character& character) = 0;
};

class PlayerControl : public ControlType {
public:
    void makeDesicion(Character& character) override;
};



#endif
