#include "Skill.h"
#include "RandomInt.h"
#include "../Event.h"
#include <typeinfo> // for std::bad_cast
#include <unordered_set>
using namespace std;


Result AssetGrowth::activate(Stage& stage, Character& cha) const {
    int maxRoundCnt = 0;
    Asset theAsset;

    // 找最久的持股
    for (const auto& a: cha.assets) {
        if(a.second.roundCnt > maxRoundCnt){
            maxRoundCnt = a.second.roundCnt;
            theAsset = a.second;
        }
    }

    if(maxRoundCnt >= 7) {
        int increment = theAsset.getValue() * 0.1;
        cha.currentMoney += increment;
        return Result("最久的持股為" + theAsset.stock->getName() + "，獲得" + to_string(increment) + "的資金");
    } else if(maxRoundCnt >= 4) {
        while(true){
            int num = theAsset.number;
            if(cha.isPlayer()){
                cout << "最久的持股： " << theAsset.stock->getName() << "\n輸入欲購買數量：";
                cin >> num;
            }
            try {
                int reward = cha.tradeStocks(stage, theAsset.stock->getName(), num, true) * 0.08;
                cha.currentMoney += reward;
                break;
            } catch (exception& e) {
                if(cha.isPlayer())
                    cerr << e.what() << "\n";
                else 
                    num /= 2;
            }
        }
    } else {
        return Result("沒有持股超過3回合的股票");
    }
}

Result InsideScoop::activate(Stage& stage, Character& cha) const {
    static unordered_set<string> industrySet = {"Technology", "Biotech", "Consumer Staples", "Semiconductor", "Airlines"};

    int curRound = stage.getCurRound();
    if(curRound == 10){
        int increment = cha.getTotalAsset() * 0.01;
        cha.currentMoney += increment;
        return Result("第十回合使用，轉為獲得" + to_string(increment));
    }

    // 正式找到下回合事件
    bool eventOccur = false;
    vector<Event*>& events = stage.rounds[curRound].events;
    int eventId =  randomInt(0, events.size() - 1);
    return Result(events[eventId]->getDescription(), -100, events[eventId]);
}



Result Peek::activate(Stage& stage, Character& cha) const {
    // 玩家特有技能
    while(true){
        cout << "輸入想查看的角色編號: 1 ~ " << stage.characters.size() << "\n";
        int id;
        cin >> id;
        try{
            Character* she = stage.characters.at(id - 1);
            return Result(she->showIntroduction() + 
                    she->showFinancialStatus() +
                    she->showActionLog());
        } catch (out_of_range& e) {
            cerr << "不存在的角色編號：" + to_string(id) + "\n";
        }
    }
}