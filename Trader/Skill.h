#ifndef SKILL_H
#define SKILL_H

#include "Character.h"
#include "Stage.h"

class Character;
class Event;
class Stock;
struct Stage;
struct Round;

// 可能回傳的結果類型
struct Result {
    string strVal; // 給玩家看的
    int intVal;
    Event* eventPtr;
    string stockTicker;

    Result() {}
    Result(const string& str, int d=-100 , Event* e=nullptr, string s="") : 
        strVal(str), intVal(d), eventPtr(e), stockTicker(s) {}
};

class Skill{
public:
    virtual string getName() const = 0;
    virtual string showInfo() const = 0;
    virtual Result activate(Stage& stage, Character& cha) const = 0;
    // 需要時回傳目標股票與其漲幅，或事件內容，否則為空
};

class Foresight : public Skill {
public:
    static int getId() { return 0; }
    string getName() const override { return "洞燭先機"; }
    string showInfo() const override { return "持股達到3回合，下次買入獲得8%回饋；達到7回合，獲得持股額度的10%獎勵。\n只會對持股最久的股票發動，且只會發動最高回合數的效果。"; }
    Result activate(Stage& stage, Character& cha) const override;
};

class AssetGrowth : public Skill {
public:
    static int getId() { return 1; }
    string getName() const override { return "資產增值"; }
    string showInfo() const override { return "持股達到4回合，下次買入獲得8%回饋；達到7回合，獲得持股額度的10%獎勵。\n只會對持股最久的股票發動，且只會發動最高回合數的效果。"; }
    Result activate(Stage& stage, Character& cha) const override;
};

class Hedge : public Skill {
public:
    static int getId() { return 2; }
    string getName() const override { return "風險對沖"; }
    string showInfo() const override { return "持股達到4回合，下次買入獲得8%回饋；達到7回合，獲得持股額度的10%獎勵。\n只會對持股最久的股票發動，且只會發動最高回合數的效果。"; }
    Result activate(Stage& stage, Character& cha) const override;
};

class InsideScoop : public Skill {
public:
    static int getId() { return 3; }
    string getName() const override { return "內線消息"; }
    string showInfo() const override { return "得到一個下回合將發生的事件內容。第十回合使用轉為增加總資產1%"; }
    Result activate(Stage& stage, Character& cha) const override;
};

class Gamble : public Skill {
public:
    static int getId() { return 4; }
    string getName() const override { return "豪賭"; }
    string showInfo() const override { return "持股達到4回合，下次買入獲得8%回饋；達到7回合，獲得持股額度的10%獎勵。\n只會對持股最久的股票發動，且只會發動最高回合數的效果。"; }
    Result activate(Stage& stage, Character& cha) const override;
};

class Peek : public Skill {
public:
    static int getId() { return 5; }
    string getName() const override { return "窺視"; }
    string showInfo() const override { return "查看某角色本回合的操作紀錄&財務狀況。"; }
    Result activate(Stage& stage, Character& cha) const override;
};

#endif