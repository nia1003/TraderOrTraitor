#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include "../Stock.h"
// #include "Skill.h"
using namespace std;

 // forward declaration
struct Stage;
struct Round;
struct Result;
class Skill;
class Stock;

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
    // 各角色的基本資訊
    static const unordered_map<string, int> maxActionCntMap;
    static const unordered_map<string, array<int, 2>> initMoneyRangeMap;
    static const array<short, 2> tradeLimits; // 買入限制，賣出為一半。0為玩家，1為電腦
    static vector<Skill> skillList;

    // static int currentId; // 模仿SQL的AUTO_INCREMENT

    // 可能用到的
    int initMoney; // 隨機後的結果
    int tradeLimit;
    string type;

    // 身分相關
    // short id; // served as key in Stage's characters array
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
    Character(const string& t, const string& n, const string& des);
    virtual ~Character() = default;
    // static void resetCurrentId() { Character::currentId = 0; }
    
    // getters
    const string& getName() const { return this->name; };
    int getActionCnt() { return this->actionCnt; }

    // 遊戲背後邏輯相關(輔助遊戲進行)
    virtual bool isPlayer() const = 0 ;
    void obtainSkill(Skill* s) { skills.push_back(s); }
    int getTotalAsset() const; // currentMoney + Σ(s.num * s.price) for s in stocks
    void resetActionCnt() { this->actionCnt = Character::maxActionCntMap.at(this->type); }
    virtual void takeAction(Stage&, const Round&) = 0; // 實現各自的操作策略

    // 遊戲操作相關(玩家有對應操作)
    int tradeStocks(const Stage&, const string& ticker, int number, bool isbuy); // 回傳交易額度
    Result useSkill(Stage&, int skillId);
    string showSkills() const;
    string showIntroduction() const; // 展示身分、名字、介紹
    string showFinancialStatus() const; // 展示currentMoney、stocks
    string showActionLog() const;

friend class AssetGrowth;
friend class InsideScoop;
};


// 玩家部分
class Player : public Character {
protected:
public:
    Player(const string& t, const string& n, const string& des);
    virtual ~Player() = default;
    bool isPlayer() const { return true; }
    void takeAction(Stage&, const Round&) override;
};

class Retail : public Player {
private:
public:
    Retail(const string& n, const string& des);
};

class Rich : public Player {
private:
public:
    Rich(const string& n, const string& des);
};

// 機器人部分
class Robot : public Character {
protected:
    template <typename T>
    string randomStock(const unordered_map<string, T>&);
public:
    Robot(const string& t, const string& n, const string& des);
    bool isPlayer() const { return false; }
    // 機器人根據身分有不同的takeAction
};

class ShortTerm : public Robot {
private:
public:
    ShortTerm(const string& n, const string& des);
};

class LongTerm : public Robot {
private:
    static vector<string> preferredStocks;
public:
    LongTerm(const string& n, const string& des);
    void takeAction(Stage&, const Round&) override;
};

class Defensive : public Robot {
private:
public:
    Defensive(const string& n, const string& des);
};

class Insider : public Robot {
private:
    static const unordered_map<string, vector<string>> industryToTickers;
    string industry;
    vector<string> industryStock;
public:
    Insider(const string& ind, const string& n, const string& des);
    void takeAction(Stage&, const Round&) override;
    string getIndustry() { return this->industry; }
};

#endif