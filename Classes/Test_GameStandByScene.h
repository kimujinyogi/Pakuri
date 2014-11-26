//
//  GameStandByScene.h
//  hockey
//
//  Created by yongwoon on 11/14/14.
//
//

#ifndef __GAMESTANDBY_SCENE_H__
#define __GAMESTANDBY_SCENE_H__

#include "cocos2d.h"

class GameStandBy : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    
    // implement GameStandBy "static create()" method manually
    CREATE_FUNC(GameStandBy);
    
    // Timer
    virtual void update(float delta);
    void countDownTimer(float delta);
    
    float m_fRunningTime;
    cocos2d::Label* iTimer;
    
    // Show timer
    void showCountDownLabel(float m_fTime);
    
    // Go to TeamOragnizeScene
    void goToTeamOrganizeScene();
    

};

#endif // __GAMESTANDBY_SCENE_H__
