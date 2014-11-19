//
//  GameInfoDefine.h
//  TestProject
//
//  Created by KimJinHyuck on 2014/11/18.
//
//

#ifndef TestProject_GameInfoDefine_h
#define TestProject_GameInfoDefine_h

namespace GameInfo {
    
    // http://ppp-lab.sakura.ne.jp/cpp/library/008.html
    enum ItemFlag {
        // スコア＋＋
        Score,
        // コイン＋＋
        Coin,
        // 経験値＋＋
        Exp,
        // 時間＋＋
        Time,
        // 爆弾＋＋
        Bomb,
        // 種類＋＋
        Type,
        MAX,
    };
}

#endif
