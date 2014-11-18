//
//  UseMenuItemLabel.h
//  TestProject
//
//  Created by KimJinHyuck on 2014/11/18.
//
//

#ifndef __TestProject__UseMenuItemLabel__
#define __TestProject__UseMenuItemLabel__

#include "CCRef.h"
#include "cocos2d.h"
#include "GameInfoDefine.h"

namespace GameReadyMenu {
    class UseMenuItemLabel : public cocos2d::MenuItemLabel
    {
    public:
        UseMenuItemLabel();
        ~UseMenuItemLabel();
        static UseMenuItemLabel * create(cocos2d::Node*label, const cocos2d::ccMenuCallback& callback, GameInfo::ItemFlag flag);

        enum GameInfo::ItemFlag getFlag ();
    protected:
        bool initWithLabel(Node* label, const cocos2d::ccMenuCallback& callback, GameInfo::ItemFlag flag);

    private:
        enum GameInfo::ItemFlag eFlag;
    };
}
#endif /* defined(__TestProject__UseMenuItemLabel__) */


