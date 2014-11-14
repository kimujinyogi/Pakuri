//
//  GameInfo.h
//  TestProject
//
//  Created by KimJinHyuck on 2014/11/14.
//
//

#ifndef __TestProject__GameInfo__
#define __TestProject__GameInfo__


#include "cocos2d.h"

namespace GameInfo {
    class GameItemStatus;
    class GameInfo
    {
    private:
        static GameInfo* m_instance;
        GameInfo ();
        ~GameInfo ();
        GameItemStatus* m_pItemStatus;
    public:
        static GameInfo* getInstance ();
        GameItemStatus* getItemStatus ();
    };
}

#endif /* defined(__TestProject__GameInfo__) */
