#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include "Stock.h"
#include "Skill.h"
using namespace std;

 // forward declaration
struct Stage;
struct Round;

struct Asset {
    int number;
    int roundCnt; // 持有回合數
    Stock* stock;
    Asset() {}
    Asset(int n, Stock* s) : number(n), stock(s), roundCnt(0) {}
    int getValue() const { return number * stock->getCurrentPrice(); }
};

// class ControlType;

class Character {
protected:
    static int currentId; // 模仿SQL的AUTO_INCREMENT

    // 身分相關
    short id; // served as key in Stage's characters array
    // ControlType* controlType;
    string name;
    string description;

    // 功能相關
    int currentMoney;
    int actionCnt;
    unordered_map<string, Asset> assets;
    vector<string> actionLog; // 本回合操作紀錄
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
    virtual void takeAction(const Stage&, const Round&) = 0; // 實現各自的操作策略

    // 遊戲操作相關(玩家有對應操作)
    void tradeStocks(const Stage&, const string& ticker, int number, bool isbuy); // number大於0表示買入，小於0表示賣出
    void useSkill(int skillId);
    string showSkills() const;
    string showIntroduction() const; // 展示身分、名字、介紹
    string showFinancialStatus() const; // 展示currentMoney、stocks
    const string& showTradeLog() const;
};

class Player : public Character {
protected:
public:
    Player(const string& n, const string& des) : Character(n, des) {}
    void takeAction(const Stage&, const Round&) override;
    int getActionCnt() { return this->actionCnt; }
};

class Retail : public Player {
private:
    static const int maxActionCnt;
    static const array<int, 2> initMoneyRange;
public:
    Retail(const string& n, const string& des);
    void resetActionCnt() override { this->actionCnt = Retail::maxActionCnt; }
};

class Rich : public Player {
private:
    static const int maxActionCnt;
    static const array<int, 2> initMoneyRange;
public:
    Rich(const string& n, const string& des);
    void resetActionCnt() override { this->actionCnt = Rich::maxActionCnt; }
};


#endif
