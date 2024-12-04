// 編譯命令：g++ test_round.cpp Character.cpp Stage.cpp Stock.cpp Event.cpp -o test_round

#include <iostream>
#include <windows.h>
#include "Character.h"
#include "Stock.h"
#include "Event.h"
#include "Stage.h"

using namespace std;

// 初始化股票列表
vector<Stock> stockVector = {
    // 科技股
    Stock("AAPL", "Apple Inc.", "Technology", 150, "疫情期間持續推出創新產品，並加速研發自家晶片，硬體需求保持強勁。然而，疫情後需關注一般消費者的購買力是否能夠支撐其營收增長。", 0.8),
    Stock("MSFT", "Microsoft", "Technology", 280, "受益於遠端辦公需求以及 Azure 雲端業務的增長，近期業績表現穩定，未來發展值得關注。", 1.1),
    Stock("UBER", "Uber", "Technology", 45, "疫情期間載客需求顯著減少，業務面臨挑戰，但未來需求回升的可能性仍需觀察。", 1.2),

    // 生技醫療股
    Stock("MRNA", "Moderna", "Biotech", 150, "疫苗研發取得成功，疫情後期業務增長顯著，但長期表現仍存在不確定性，須注意疫苗是否能被各國認可。", 1.5),

    // 消費必需品股
    Stock("COST", "Costco", "Consumer Staples", 520, "疫情期間囤貨需求激增，但未來趨勢仍需觀察", 0.8),
    Stock("KO", "Coca-Cola", "Consumer Staples", 60, "飲料需求保持穩定，但長期增長可能取決於消費者習慣的變化", 0.7),

    // 半導體類股
    Stock("TSM", "Taiwan Semiconductor Manufacturing", "Semiconductor", 120, "作為晶圓代工龍頭，持續受益於先進晶片需求，但面臨英特爾新競爭壓力", 1.2),
    Stock("INTC", "Intel", "Semiconductor", 55, "老牌半導體公司，近期擴張晶圓代工業務，與台積電處於劇烈競爭的狀態", 1.0),

    // 航空類股
    Stock("UAL", "United Airlines", "Airlines", 40, "旅遊需求驟降，業績遭受重創，但疫苗問世可能帶來復甦希望", 1.0),
    Stock("DAL", "Delta Air Lines", "Airlines", 45, "作為航空業龍頭之一，疫苗普及推動旅遊需求回升，但挑戰依然存在", 1.0)
};

int main() {
    SetConsoleOutputCP(CP_UTF8); // 設定主控台為 UTF-8
    SetConsoleCP(CP_UTF8);       // 設定輸入為 UTF-8

    vector<Event> events;

    // 回合一 事件1：新產品發布
    events.emplace_back(
        unordered_map<string, double>{{"AAPL", 1.8}, {"MSFT", 0.8}, {"INTC", 1.2}},
        "Apple 發布新一代 MacBook Pro 和 AirPods Pro，引發市場對其創新能力的信心",
        8,
        "Tech News"
    );

    // 回合一 事件2：貿易協議進展
    events.emplace_back(
        unordered_map<string, double>{{"TSM", 2.0}, {"INTC", 1.5}, {"COST", 1.0}},
        "中美貿易談判取得進展，市場對半導體和消費必需品的需求提升",
        5,
        "Global News"
    );

    // 回合一 事件3：旅遊業旺季來臨
    events.emplace_back(
        unordered_map<string, double>{{"UAL", 1.7}, {"DAL", 1.5}, {"KO", 0.9}},
        "感恩節即將到來，航空業迎來旺季，旅遊需求上升",
        6,
        "Holiday Trends"
    );

    unordered_map<string, Stock*> testStocks;
    for(int i = 0; i < stockVector.size(); ++i)
        testStocks[stockVector[i].getTicker()] = &stockVector[i];

    vector<Event*> eventPtrs;
    for(Event& e: events)
        eventPtrs.push_back(&e);
    Round r(eventPtrs);
    vector<Round> testRound = {r};

    Character* testCha = new Retail("測試用玩家", "我是散戶");
    Stage testStage(testStocks, testRound);
    testStage.characters.push_back(testCha);

    testStage.startStage();
    
    return 0;
}
