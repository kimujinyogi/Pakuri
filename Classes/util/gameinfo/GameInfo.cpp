//
//  GameInfo.cpp
//  TestProject
//
//  Created by KimJinHyuck on 2014/11/14.
//
//

#include "GameInfo.h"

#include "defines.h"

#include "GameItemStatus.h"


namespace GameInfo {
    GameInfo* GameInfo::m_instance = NULL;

    // --------------------------------
    // private
    // --------------------------------

    GameInfo::GameInfo ()
    {
        m_pItemStatus = GameItemStatus::create();
        m_pItemStatus->retain();
    }
    
    GameInfo::~GameInfo ()
    {
        m_pItemStatus->release();
        m_pItemStatus = nullptr;
    }

    // --------------------------------
    // public
    // --------------------------------

    GameInfo* GameInfo::getInstance()
    {
        if (NULL == m_instance)
        {
            m_instance = new GameInfo ();
        }
        
        return m_instance;
    }
    
    GameItemStatus* GameInfo::getItemStatus ()
    {
        return m_pItemStatus;
    }
}
