//
//  GamePauseMenuLayer.h
//  TestProject
//
//  Created by KimJinHyuck on 2014/11/28.
//
//

#ifndef __TestProject__GamePauseMenuLayer__
#define __TestProject__GamePauseMenuLayer__

#include "cocos2d.h"

// ゲーム中にスキルを使用する為のボタンや、一時停止のボタンがある
// 一時停止のメニューも管理する

typedef std::function<void(cocos2d::Ref*)> callbackGamemenu;

class GamePauseMenuLayer : public cocos2d::Layer
{
private:
    cocos2d::EventListenerTouchOneByOne* m_eventListener;
    cocos2d::Layer* m_layerMenu;
    callbackGamemenu m_cbResume;
    callbackGamemenu m_cbPause;
    callbackGamemenu m_cbRotate;
    
    bool m_isPause;
public:
    static GamePauseMenuLayer* createLayer();
    virtual bool init();
    CREATE_FUNC(GamePauseMenuLayer);
    
    // 再開、一時停止のイベントセット
    void setMenuEvent (const callbackGamemenu& callbackResume,
                       const callbackGamemenu& callbackPause,
                       const callbackGamemenu& callbackRotate);

    // メニュー操作
    void pauseGame ();
    void doResumeGame (Ref* pSender);
    void doPauseGame (Ref* pSender);
    void doEndGame (Ref* pSender);
    
    // スキル
    void doSkill (Ref* pSender);
    void doShake (Ref* pSender);
};


#endif /* defined(__TestProject__GamePauseMenuLayer__) */
