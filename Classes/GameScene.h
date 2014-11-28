//
//  GameScene.h
//  Puzzle2
//
//  Created by otmb on 2014/09/05.
//
//

#ifndef __Puzzle2__GameScene__
#define __Puzzle2__GameScene__

#include "cocos2d.h"

USING_NS_CC;

using namespace ui;

class GamePlayLayer; // ゲームプレイ画面を管理
class GamePauseMenuLayer;   // ゲーム進行中の一時画面の管理
class GameScene : public cocos2d::Scene
{
    enum LayerType {
        Game = 0,
        Timer,
        Pause
    };
    
private:
    GamePlayLayer* m_layerGamePlay;
    GamePauseMenuLayer* m_layerPauseMenu;
protected:
    
public:
    static GameScene* createScene();
    virtual bool initWithPhysics();
    void initLayers();
//    CREATE_FUNC(GameScene);
//    void actionResume (Ref* pSender);
    void evResume (Ref* pSender);
    void evPause (Ref* pSender);
};

#endif /* defined(__Puzzle2__GameScene__) */
