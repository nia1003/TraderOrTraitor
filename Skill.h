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

#endif