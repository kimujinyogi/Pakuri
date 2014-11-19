//
//  UseMenuItemLabel.cpp
//  TestProject
//
//  Created by KimJinHyuck on 2014/11/18.
//
//

// extern "C" int malloc_zone_check(int);
// assert( malloc_zone_check(NULL) );
// http://pebble8888.hatenablog.com/entry/2014/03/24/214851

#include "UseMenuItemLabel.h"

#include "GameInfo.h"
#include "GameItemStatus.h"

namespace GameReadyMenu {

#pragma mark - public
    
    UseMenuItemLabel::UseMenuItemLabel()
    {
        
    }

    UseMenuItemLabel::~UseMenuItemLabel()
    {
        
    }

    UseMenuItemLabel* UseMenuItemLabel::create(cocos2d::Node*label, const cocos2d::ccMenuCallback& callback, GameInfo::ItemFlag flag, const std::string& strOn, const std::string& strOff)
    {
        UseMenuItemLabel *ret = new (std::nothrow) UseMenuItemLabel();
        ret->initWithLabel(label, callback, flag, strOn, strOff);
        ret->autorelease();
        return ret;
    }
    
    enum GameInfo::ItemFlag UseMenuItemLabel::getFlag ()
    {
        return this->m_eFlag;
    }

#pragma mark - protected
    
    bool UseMenuItemLabel::initWithLabel(Node* label, const cocos2d::ccMenuCallback& callback, GameInfo::ItemFlag flag, const std::string& strOn, const std::string& strOff)
    {
        this->m_callback = callback;
        if (this->cocos2d::MenuItemLabel::initWithLabel(label, CC_CALLBACK_1(UseMenuItemLabel::touchedItem, this))) {
            this->m_eFlag = flag;
            this->m_strOn = strOn;
            this->m_strOff = strOff;
            this->setLabelStatus();
            return true;
        }
        return false;
    }
    
    void UseMenuItemLabel::setLabelStatus ()
    {
        cocos2d::Label* label = (cocos2d::Label*)this->getLabel();
        if (GameInfo::GameInfo::getInstance ()->getItemStatus()->checkItemFlag(this->m_eFlag)) {
            label->setString(this->m_strOn.c_str());
        } else {
            label->setString(this->m_strOff.c_str());
        }
        this->setContentSize(label->getContentSize());
    }

#pragma mark - private
    void UseMenuItemLabel::touchedItem (Ref* pSender)
    {
        GameInfo::GameInfo::getInstance ()->getItemStatus()->changeFlag(this->m_eFlag);
        this->setLabelStatus();
        this->m_callback (this);
    }
}





