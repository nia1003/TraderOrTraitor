#include <iostream>
#include <vector>
#include <unordered_map>
#include <windows.h>
#include "../src/Event.h"
#include "../src/Stock.h"


using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8); // 設定主控台為 UTF-8
    SetConsoleCP(CP_UTF8);       // 設定輸入為 UTF-8
    
    vector<Event> events;

    // 回合一 事件1：新產品發布
    events.emplace_back(
        unordered_map<string, double>{{"AAPL", 0.5}, {"MSFT", 0.3}, {"INTC", 0.2}},
        "Apple 發布新一代 MacBook Pro 和 AirPods Pro，引發市場對其創新能力的信心",
        0.08,
        "Tech News"
    );

    // 回合一 事件2：貿易協議進展
    events.emplace_back(
        unordered_map<string, double>{{"TSM", 0.6}, {"INTC", 0.5}, {"COST", 0.5}},
        "中美貿易談判取得進展，市場對半導體和消費必需品的需求提升",
        0.1,
        "Global News"
    );

    // 回合一 事件3：旅遊業旺季來臨
    events.emplace_back(
        unordered_map<string, double>{{"UAL", 0.6}, {"DAL", 0.6}, {"KO", 0.5}},
        "感恩節即將到來，航空業迎來旺季，旅遊需求上升",
        0.08,
        "Holiday Trends"
    );

    // 回合二 事件1：COVID-19 疫情爆發
    events.emplace_back(
        unordered_map<string, double>{{"AAPL", -1.0}, {"MSFT", -1.0}, {"UBER", -1.0}, {"MRNA", -1.0}, {"COST", -1.0}, {"KO", -1.0}, {"TSM", -1.0}, {"INTC", -1.0}, {"UAL", -1.0}, {"DAL", -1.0}}, // 使用 "ALL" 表示全體股票
        "COVID-19 疫情在全球範圍內迅速蔓延，各國實施封鎖措施，對經濟活動造成重大影響，導致市場普遍恐慌，全體股價出現劇烈下跌",
        0.2,  // 強烈負面影響
        "World Health Organization"
    );

    // 回合二 事件2：遠端工作需求激增
    events.emplace_back(
        unordered_map<string, double>{{"MSFT", 0.5}, {"AAPL", 0.5}},
        "隨著疫情蔓延，企業轉向遠端工作模式，對線上協作工具的需求激增",
        0.08,  // 穩定正面影響
        "Tech Industry Reports"
    );

    // 回合二 事件3：消費者囤積必需品
    events.emplace_back(
        unordered_map<string, double>{{"COST", 0.4}, {"KO", 0.4}},
        "疫情期間，消費者大量購買生活必需品，導致相關產品需求激增",
        0.05,  // 穩定正面影響
        "Market Analysis"
    );

    // 回合三 事件1: 科技公司財報超預期
    events.emplace_back(
        unordered_map<string, double>{{"AAPL", 0.6}, {"MSFT", 0.6}},
        "主要科技公司公佈的第一季度財報超出市場預期，顯示出強勁的業績表現",
        0.1,  // 正面影響
        "Tech News"
    );

    // 回合三 事件2: 疫苗研發取得進展
    events.emplace_back(
        unordered_map<string, double>{{"MRNA", 1.0}, {"UBER", 0.4}},
        "生技公司在 COVID-19 疫苗研發上取得重要進展，進入臨床試驗階段",
        0.12,  // 強烈正面影響
        "Health Reports"
    );

    // 回合三 事件3: 供應鏈中斷影響半導體行業
    events.emplace_back(
        unordered_map<string, double>{{"TSM", -0.7}, {"INTC", -0.7}},
        "疫情導致的供應鏈中斷影響半導體行業的生產和交付",
        0.05,  // 負面影響
        "Industry Reports"
    );

    // 回合四 事件1: 科技公司推出新產品線
    events.emplace_back(
        unordered_map<string, double>{{"AAPL", 0.4}, {"MSFT", 0.3}},
        "主要科技公司在 8 月推出新產品線，滿足居家工作和學習的需求，市場反應熱烈",
        0.08,  // 正面影響
        "Tech Industry Reports"
    );

    // 回合四 事件2: 疫苗研發進入最後階段
    events.emplace_back(
        unordered_map<string, double>{{"MRNA", 0.7}, {"UBER", 0.4}, {"UAL", 0.4}, {"DAL", 0.4}},
        "生技公司宣佈 COVID-19 疫苗研發進入最後階段，市場對疫情結束的預期增強",
        0.1,  // 強烈正面影響
        "Health and Market News"
    );

    // 回合四 事件3: 消費必需品需求增長
    events.emplace_back(
        unordered_map<string, double>{{"COST", 0.4}, {"KO", 0.4}},
        "疫情期間，消費者對必需品的需求持續增長，相關企業業績提升",
        0.07,  // 穩定正面影響
        "Consumer Trends"
    );

    // 回合五 事件1: 蘋果推出自研 M1 晶片
    events.emplace_back(
        unordered_map<string, double>{{"AAPL", 0.6}, {"INTC", -0.3}},
        "蘋果公司（Apple Inc.）在 11 月發佈首款搭載自研 M1 晶片的 Mac 電腦，標誌著從英特爾（Intel）處理器過渡的開始，提升產品性能和能效",
        0.1,  // AAPL 積極影響；INTC 負面影響
        "Tech Industry Reports"
    );

    // 回合五 事件2: 半導體產業供應鏈緊張
    events.emplace_back(
        unordered_map<string, double>{{"TSM", -0.5}, {"MSFT", -0.2}, {"AAPL", -0.2}},
        "全球半導體需求激增，導致供應鏈緊張，晶圓代工產能供不應求，影響相關企業的生產計劃",
        0.09,  // 供應鏈緊張對大部分企業是負面影響
        "Industry Reports"
    );

    // 回合五 事件3: 全球股市強勁反彈
    events.emplace_back(
        unordered_map<string, double>{{"AAPL", 0.6}, {"MSFT", 0.6}, {"UBER", 0.6}, {"MRNA", 0.6}, {"COST", 0.6}, {"KO", 0.6}, {"TSM", 0.6}, {"INTC", 0.6}, {"UAL", 0.6}, {"DAL", 0.6}}, // "ALL" 代表全體股票
        "受疫苗研發進展和經濟刺激政策影響，全球股市在 11 月出現強勁反彈，投資者信心回升",
        0.08,  // 正面影響
        "Global Market News"
    );

    // 回合六 事件1: AI 智能交易系統引發股市波動
    events.emplace_back(
        unordered_map<string, double>{{"MSFT", -0.3}, {"AAPL", -0.3}, {"DAL", -0.2}, {"UBER", -0.2}},
        "一家大型投資機構的人工智慧交易系統發生異常，短時間內觸發大量拋售指令，導致市場短暫性暴跌。事件後市場迅速恢復，但部分個股受影響較大",
        0.05,  // 負面影響
        "Market Watch Reports"
    );

    // 回合六 事件2: 疫苗接種計劃進展迅速
    events.emplace_back(
        unordered_map<string, double>{{"MRNA", 0.6}, {"UAL", 0.4}, {"DAL", 0.4}, {"COST", 0.3}, {"KO", 0.3}},
        "全球多國加速疫苗接種，經濟重啟進程加快，市場對經濟復甦的信心增強，帶動整體市場反彈",
        0.1,  // 正面影響
        "Global Health Reports"
    );

    // 回合六 事件3: 虛擬貨幣市場崩盤
    events.emplace_back(
        unordered_map<string, double>{{"MSFT", -0.4}, {"TSM", -0.1}, {"AAPL", -0.2}, {"COST", -0.2}},
        "一家主要的虛擬貨幣交易所遭受大規模駭客攻擊，引發市場對數字資產的恐慌性拋售，部分科技公司股價受到拖累",
        0.07,  // 負面影響
        "Crypto Market News"
    );

    // 回合七 事件1: 台積電宣布全球擴張計劃
    events.emplace_back(
        unordered_map<string, double>{{"TSM", 0.5}, {"INTC", -0.5}},
        "台積電（TSMC）宣布未來三年內在全球建造六座新廠，擴大產能以應對晶片短缺問題",
        0.1,  // 正面影響
        "Tech Industry Reports"
    );

    // 回合七 事件2: 全球網絡攻擊導致供應鏈中斷
    events.emplace_back(
        unordered_map<string, double>{{"AAPL", -0.2}, {"MSFT", -0.2}, {"COST", -0.2}},
        "一場大規模的網絡攻擊癱瘓了多家主要供應鏈公司的系統，導致產品交付延遲，影響多個行業",
        0.06,  // 負面影響
        "Global Security News"
    );

    // 回合七 事件3: 新型可穿戴設備引發健康熱潮
    events.emplace_back(
        unordered_map<string, double>{{"AAPL", 0.4}, {"KO", -0.2}},
        "一款革命性的新型可穿戴健康設備在市場上引發熱潮，消費者爭相購買，帶動相關公司的銷售增長",
        0.07,  // 正面影響
        "Consumer Market Reports"
    );

    // 回合八 事件1: 英特爾宣布新建晶圓代工廠
    events.emplace_back(
        unordered_map<string, double>{{"INTC", 0.7}, {"TSM", -0.4}, {"MSFT", -0.2}},
        "英特爾（Intel）宣布在美國亞利桑那州新建兩座先進晶圓代工廠，投資 200 億美元，旨在挑戰台積電（TSMC）和三星在晶圓代工市場的領導地位",
        0.1,  // 正面影響
        "Tech Industry Reports"
    );

    // 回合八 事件2: 英特爾製程技術突破
    events.emplace_back(
        unordered_map<string, double>{{"INTC", 0.8}, {"TSM", -0.5}},
        "英特爾宣布其新一代製程技術成功達到 3nm 水平，對其晶圓代工業務具有里程碑意義，但量產仍需時間",
        0.08,  // 穩定正面影響
        "Industry News"
    );

    // 回合八 事件3: 疫苗接種率下降，經濟復甦受阻
    events.emplace_back(
        unordered_map<string, double>{{"MRNA", -0.8}, {"UAL", -0.5}, {"DAL", -0.5}, {"COST", 0.3}, {"KO", 0.3}},
        "多起疫苗接種引發的死亡案例，使得全球出現對疫苗安全性質疑的聲音，疫苗接種率下降，導致疫情反彈，經濟復甦放緩",
        0.1,  // 負面影響
        "Global Health Watch"
    );

    // 回合九 事件1: 英特爾完成對格羅方德的收購
    events.emplace_back(
        unordered_map<string, double>{{"INTC", 0.8}, {"TSM", -0.5}},
        "英特爾（Intel）成功以 300 億美元收購格羅方德（GlobalFoundries），大幅提升其晶圓代工產能及良率，進一步挑戰台積電（TSMC）的市場地位",
        0.1,  // 正面影響
        "Tech Industry Reports"
    );

    // 回合九 事件2: 疫苗接種率下降導致疫情反彈
    events.emplace_back(
        unordered_map<string, double>{{"MRNA", 0.6}, {"UAL", 0.5}, {"DAL", 0.5}, {"COST", -1.4}, {"KO", -1.2}},
        "由於對疫苗安全性的質疑，全球疫苗接種率下降，導致 COVID-19 疫情反彈，各國重新實施封鎖措施，經濟復甦受阻，資金流入表現較穩定的股票避險",
        0.1,  // 負面影響
        "Global Health Watch"
    );

    // 回合九 事件3: 科技行業持續領跑經濟
    events.emplace_back(
        unordered_map<string, double>{{"AAPL", 0.7}, {"MSFT", 0.7}, {"TSM", 0.4}},
        "受遠端工作模式的延續和數位轉型加速影響，科技公司在多個領域的業務保持高速增長，市場看好未來發展",
        0.08,  // 穩定正面影響
        "Tech Market Analysis"
    );

    // 最後一回合 事件1: 英特爾超越台積電，成為全球最大晶圓代工廠
    events.emplace_back(
        unordered_map<string, double>{{"INTC", 1.0}, {"TSM", -1.0}},
        "收購格羅方德後，3奈米製程良率持續成長，英特爾（Intel）成功搶到大筆客戶訂單，超越台積電（TSMC），成為全球最大的晶圓代工廠，吸引大量客戶轉單",
        0.14,  // 強烈正面影響
        "Tech Market Reports"
    );

    // 最後一回合 事件2: Uber 公布財報，業績不佳
    events.emplace_back(
        unordered_map<string, double>{{"UBER", -0.6}},
        "Uber 公布最新財報，顯示出行需求未如預期恢復，導致收入低於市場預期，股價下跌",
        0.05,  // 輕微負面影響
        "Financial News"
    );

    // 最後一回合 事件3: 新疫苗問世，航空業回暖
    events.emplace_back(
        unordered_map<string, double>{{"UAL", 0.8}, {"DAL", 0.8}, {"MRNA", -0.6}},
        "台灣開發的新型 COVID-19 疫苗橫空出世，對變種病毒高度有效，通過各國監管機關認證，施打狀況良好，使得各國放寬旅遊限制，航空業需求回升",
        0.1,  // 穩定正面影響
        "Global Health Reports"
    );

    unordered_map<string, Stock> stockMap = 
    {
        {"AAPL", Stock("AAPL", "Apple Inc.", "Technology", 150, "疫情期間持續推出創新產品，並加速研發自家晶片，硬體需求保持強勁。然而，疫情後需關注一般消費者的購買力是否能夠支撐其營收增長。", 0.8)},
        {"MSFT", Stock("MSFT", "Microsoft", "Technology", 280, "受益於遠端辦公需求以及 Azure 雲端業務的增長，近期業績表現穩定，未來發展值得關注。", 0.8)},
        {"UBER", Stock("UBER", "Uber", "Technology", 55, "疫情期間載客需求顯著減少，業務面臨挑戰，但未來需求回升的可能性仍需觀察。", 1.3)},
        {"MRNA", Stock("MRNA", "Moderna", "Biotech", 150, "疫苗研發取得成功，疫情後期業務增長顯著，但長期表現仍存在不確定性，須注意疫苗是否能被各國認可。", 1.7)},
        {"COST", Stock("COST", "Costco", "Consumer Staples", 520, "疫情期間囤貨需求激增，但未來趨勢仍需觀察", 0.6)},
        {"KO", Stock("KO", "Coca-Cola", "Consumer Staples", 60, "飲料需求保持穩定，但長期增長可能取決於消費者習慣的變化", 0.7)},
        {"TSM", Stock("TSM", "Taiwan Semiconductor Manufacturing", "Semiconductor", 120, "作為晶圓代工龍頭，持續受益於先進晶片需求，但面臨英特爾新競爭壓力", 1.0)},
        {"INTC", Stock("INTC", "Intel", "Semiconductor", 55, "老牌半導體公司，近期擴張晶圓代工業務，與台積電處於劇烈競爭的狀態", 1.0)},
        {"UAL", Stock("UAL", "United Airlines", "Airlines", 40, "旅遊需求驟降，業績遭受重創，但疫苗問世可能帶來復甦希望", 1.2)},
        {"DAL", Stock("DAL", "Delta Air Lines", "Airlines", 45, "作為航空業龍頭之一，疫苗普及推動旅遊需求回升，但挑戰依然存在", 1.2)}
    };

    // // 打印所有事件的詳情
    // for (const auto& event : events) {
    //     event.printEventDetails();
    //     cout << "------------------" << endl;
    // }

    events[3].affectStockPrice(stockMap);

    return 0;
}