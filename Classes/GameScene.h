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

class GamePlayLayer;
class GameScene : public cocos2d::Scene
{
private:
    GamePlayLayer* m_layerGamePlay;
protected:
    
public:
    static GameScene* createScene();
    virtual bool initWithPhysics();
    void initLayers();
//    CREATE_FUNC(GameScene);
    void actionResume (Ref* pSender);
};

#endif /* defined(__Puzzle2__GameScene__) */
