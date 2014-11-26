//
//  GameScene.h
//  hockey
//
//  Created by yongwoon on 11/14/14.
//
//

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "string"


class Game : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Game);
    // Layer
        cocos2d::LayerColor* layerPause;
    
    // Scene transition
        //void goToPauseScene(Ref *pSender);
        void GoToOverScene();
    
    //Timer
        private: cocos2d::Value m_vTimeLimit;
        //private: cocos2d::Value m_vHour;
        private: cocos2d::Value m_vMinute;
        private: cocos2d::Value m_vSecond;
        private: int m_iMinuteDigit;
        private: int m_iSecondDigit;
        private: cocos2d::Label* gameTimer;


        void getGamePlayedTime(Ref *pSender);
        void gamePlayTimeCountDown(float delta);
    
        int calculateTimeDigit(cocos2d::Value ml_time);
        cocos2d::Value timeTransform(cocos2d::Value remainTime);
    
    // Scheduler
        virtual void update(float delta);
    
    // callbacks(Puase, Resume, Quit)
        void menuPauseCallback(Ref *pSender);
        void menuResumeCallback(Ref *pSender);
        void menuQuitCallback(Ref *pSender);
    
    
};

#endif // __PAUSE_SCENE_H__
