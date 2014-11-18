//
//  UseMenuItemLabel.cpp
//  TestProject
//
//  Created by KimJinHyuck on 2014/11/18.
//
//

#include "UseMenuItemLabel.h"

namespace GameReadyMenu {
    UseMenuItemLabel::UseMenuItemLabel()
    {
        
    }

    UseMenuItemLabel::~UseMenuItemLabel()
    {
        
    }

    UseMenuItemLabel* UseMenuItemLabel::create(cocos2d::Node*label, const cocos2d::ccMenuCallback& callback, GameInfo::ItemFlag flag)
    {
        UseMenuItemLabel *ret = new (std::nothrow) UseMenuItemLabel();
        ret->initWithLabel(label, callback, flag);
        ret->autorelease();
        return ret;
    }
    
    enum GameInfo::ItemFlag UseMenuItemLabel::getFlag ()
    {
        return this->eFlag;
    }

    bool UseMenuItemLabel::initWithLabel(Node* label, const cocos2d::ccMenuCallback& callback, GameInfo::ItemFlag flag)
    {
        if (this->cocos2d::MenuItemLabel::initWithLabel(label, callback)) {
            this->eFlag = flag;
            return true;
        }
        return false;
    }
}





