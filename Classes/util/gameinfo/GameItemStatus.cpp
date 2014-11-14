//
//  GameItemStatus.cpp
//  TestProject
//
//  Created by KimJinHyuck on 2014/11/14.
//
//

#include "GameItemStatus.h"


namespace GameInfo {

    // --------------------------------
    // public
    // --------------------------------

    GameItemStatus* GameItemStatus::create()
    {
        GameItemStatus *ret = new (std::nothrow) GameItemStatus();
//        if (ret && ret->initWithAction(action, speed))
        if (ret)
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    GameItemStatus::GameItemStatus ()
    {
        
    }

    GameItemStatus::~GameItemStatus ()
    {
        
    }
    
    
    // --------------------------------
    // private
    // --------------------------------
}