#ifndef SKILL_H
#define SKILL_H

class Skill{
public:
    virtual string getName() const = 0;
    void showInfo() const { std::cout << "技能資訊"; };
    void activate() { std::cout << "技能啟動"; };
};

#endif