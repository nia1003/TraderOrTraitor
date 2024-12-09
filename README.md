# TraderOrTraitor

**黃子寰 筆記**
- 串接流程
    - 建立rounds vector，包含十個round，每個round包3個事件(可以參考我在test_event最下面的程式碼)，讓stage能夠運作十個round。
    - 回合結束更新價格+affectStock函數邏輯更新
    - 建立遊戲結束條件
    - 輸出玩家排行
        - 如果前三名->恭喜過關!
        - 沒有前三名->再試一次吧!