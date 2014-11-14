//
//  GameItemStatus.h
//  TestProject
//
//  Created by KimJinHyuck on 2014/11/14.
//
//

#ifndef __TestProject__GameItemStatus__
#define __TestProject__GameItemStatus__

#include "base/CCRef.h"
#include "cocos2d.h"

namespace GameInfo {
    class GameItemStatus : public cocos2d::Ref
    {
    public:
        static GameItemStatus* create();
        GameItemStatus ();
        ~GameItemStatus ();

    private:
        // アイテムを使った状態であるか
        // スコア＋＋
        bool m_bUsedScore;
        // コイン＋＋
        bool m_bUsedCoin;
        // 経験値＋＋
        bool m_bUsedExp;
        // 時間＋＋
        bool m_bUsedTime;
        // 爆弾＋＋
        bool m_bUsedBomb;
        // 種類＋＋
        bool m_bUsedType;
    };
}

#endif /* defined(__TestProject__GameItemStatus__) */
