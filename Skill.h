#ifndef SKILL_H
#define SKILL_H

#include "Character.h"
#include "Stage.h"

class Character;
struct Stage;
struct Round;

class Skill{
public:
    virtual string getName() const = 0;
    virtual string showInfo() const = 0;
    virtual string activate(Stage& stage, const Round& round, Character& cha) const = 0;
};

class Foresight : public Skill {
    string getName() const override { return "洞燭先機"; }
};

class StableGrowth : public Skill {
    string getName() const override { return "穩定增值"; }
};

class Hedge : public Skill {
    string getName() const override { return "風險對沖"; }
};

class InsideScoop : public Skill {
    string getName() const override { return "內線消息"; }
};

class Gamble : public Skill {
    string getName() const override { return "槓桿操作"; }
};

#endif