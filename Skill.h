#ifndef SKILL_H
#define SKILL_H

class Skill{
public:
    virtual string getName() const = 0;
    virtual string showInfo() const = 0;
    virtual void activate() const = 0;
};

#endif