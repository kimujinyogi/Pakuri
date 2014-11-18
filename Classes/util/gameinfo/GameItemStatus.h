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
#include "GameInfoDefine.h"

namespace GameInfo {
    class GameItemStatus : public cocos2d::Ref
    {
    public:
        static GameItemStatus* create();
        GameItemStatus ();
        ~GameItemStatus ();

        bool checkItemFlag (enum ItemFlag flag);
        void changeFlag (enum ItemFlag flag);
    private:
        // アイテムを使った状態であるか
        std::bitset <ItemFlag::MAX> m_bsFlag;
    };
}

#endif /* defined(__TestProject__GameItemStatus__) */
