# include "Skill.h"
using namespace std;


Result AssetGrowth::activate(Stage& stage, Character& cha) const {
    --cha.actionCnt;
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