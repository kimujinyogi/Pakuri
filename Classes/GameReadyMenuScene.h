#ifndef __GAMEREADYMENU_SCENE_H__
#define __GAMEREADYMENU_SCENE_H__

#include "cocos2d.h"

namespace GameReadyMenu {
    class UseMenuItemLabel;
}
class GameReadyMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameReadyMenuScene);
private:
    // レベルと経験値
    cocos2d::Label* pLabelLevel;
    cocos2d::Label* pLabelExp;
    // アイテムメニュー
    GameReadyMenu::UseMenuItemLabel* pMILUseScore;
    GameReadyMenu::UseMenuItemLabel* pMILUseCoin;
    GameReadyMenu::UseMenuItemLabel* pMILUseExp;
    GameReadyMenu::UseMenuItemLabel* pMILUseTime;
    GameReadyMenu::UseMenuItemLabel* pMILUseBomb;
    GameReadyMenu::UseMenuItemLabel* pMILUseType;
    
    void moveNextScene (Ref* pSender);
    void movePrevScene (Ref* pSender);
    void moveManageScene (Ref* pSender);
    
    void flipUseItem (Ref* pSender);
};

#endif // __GAMEREADYMENU_SCENE_H__
