//
//  GameStandByScene.cpp
//  hockey
//
//  Created by yongwoon on 11/14/14.
//
//

#include "GameStandByScene.h"
#include "TeamOrganizeScene.h"

#include "defines.h"

USING_NS_CC;

Scene* GameStandBy::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameStandBy::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameStandBy::init()
{
    
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    // Show the Text using Label
        auto gameCountDownText = Label::createWithSystemFont("Game stand by scene", "HirakakuProN-W6", 48);
        gameCountDownText->setPosition(Point(300,200));
        this->addChild(gameCountDownText);
    
    
    // Timer
        m_fRunningTime = 3.0f;
        this->schedule(schedule_selector(GameStandBy::countDownTimer), 1.0f);
    
    
    // Show the time with label TTF
        //this->showCountDownLabel(m_fRunningTime);

        log("m_fTime %f" ,  m_fRunningTime);

        // get the device size
        Size viewVisibleSize = Director::getInstance()->getVisibleSize();

        // integer to string
        auto m_sTimeString = CCString::createWithFormat("%d", (int)m_fRunningTime);

        // timer label
        iTimer = Label::createWithTTF(m_sTimeString->getCString(), kFONT_NORMAL, 60.0);
        iTimer->setPosition(Point(viewVisibleSize.width/2, viewVisibleSize.height/2));
        iTimer->setColor(Color3B::RED);

        this->addChild(iTimer);

    return true;
}


// don't use this function
void GameStandBy::update(float delta)
{
    log("Timeless: %f", delta);
}



void GameStandBy::countDownTimer(float delta)
{    
    m_fRunningTime--;
    
    // integer to string
    auto m_sTimeString2 = CCString::createWithFormat("%d", (int)m_fRunningTime);
    //log("Time: %f", m_fRunningTime);
     iTimer->setString(m_sTimeString2->getCString());
    
    if (m_fRunningTime < 0) {
        this->unschedule(schedule_selector(GameStandBy::countDownTimer));
        //log("Timer is over");
        this->goToTeamOrganizeScene();
    }
    
}



void GameStandBy::goToTeamOrganizeScene()
{
    auto scene = TeamOrganize::createScene();
    Director::getInstance()->replaceScene(scene);
}


/*
// Show the time with label TTF
void GameStandBy::showCountDownLabel(float m_fTime)
{
    CCLog("m_fTime %f" ,  m_fTime);
    
    Size viewVisibleSize = Director::getInstance()->getVisibleSize();
    
    // integer to string
    CCString* m_sTimeString = CCString::createWithFormat("%d", (int)m_fTime);
    
    // timer label
    auto iTimer = Label::createWithTTF(m_sTimeString->getCString(), kFONT_NORMAL, 60.0);
    iTimer->setPosition(Point(viewVisibleSize.width/2, viewVisibleSize.height/2));
    iTimer->setColor(Color3B::RED);
    
    this->addChild(iTimer);
    //this->removeChild(iTimer);
}
*/
