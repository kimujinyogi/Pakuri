//
//  GameScene.cpp
//  hockey
//
//  Created by yongwoon on 11/14/14.
//
//

#include "GameScene.h"
//#include "PauseScene.h"
#include "GameOverScene.h"

#include "defines.h"
//#include "GameTimer.h"

USING_NS_CC;

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Game::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
 

    //set background
        auto layerBackground = LayerColor::create(Color4B::ORANGE, visibleSize.width, visibleSize.height);
        addChild(layerBackground);
 
    
    
    
    
    // show label
        auto playTitle = Label::createWithSystemFont("Game scene", "HirakakuProN-W6", 48);
        playTitle->setPosition(Point(600,300));
        this->addChild(playTitle);

    
    // Game Play Timer
        m_vTimeLimit = 120.f;
    
        auto m_vTimeFormat = this->timeTransform(m_vTimeLimit);

        // create Layer for timer
        auto timerLayer = LayerColor::create(Color4B::WHITE, 250, 80);
        timerLayer->setPosition(visibleSize.width/2, visibleSize.height/2 + 200);

            // timer label
            // REF>> layer->getPosition(), layer->getContentSize()
            Size timerLayerVisibleSize = timerLayer->getContentSize();
            gameTimer = Label::createWithTTF(m_vTimeFormat.asString(), kFONT_NORMAL, 60.0);
            gameTimer->setPosition(Point(timerLayerVisibleSize.width/2, timerLayerVisibleSize.height/2));
            gameTimer->setColor(Color3B::RED);
            timerLayer->addChild(gameTimer);
        
        addChild(timerLayer);
    
    
    // Game Timer
        this->schedule(schedule_selector(Game::gamePlayTimeCountDown), 1.0f);
        this->scheduleUpdate();
    
    // Pause button
        auto m_pauseButton = MenuItemImage::create("gamePauseBtn.png", "gamePauseBtn.png", CC_CALLBACK_1(Game::menuPauseCallback, this));
        m_pauseButton->setPosition(Point(visibleSize.width/4 - 200, visibleSize.height/2 + 250));
        
        auto menu = Menu::create(m_pauseButton, NULL);
        menu->setPosition(Point::ZERO);
        this->addChild(menu);
    
    // Pause Layer
        layerPause = LayerColor::create(Color4B::BLUE, visibleSize.width/2, visibleSize.height/2);
        layerPause->ignoreAnchorPointForPosition(false);
        layerPause->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
        layerPause->setVisible(false);
        addChild(layerPause);
    
        Size layerPauseSizeView = layerPause->getContentSize();
        Point LayerPausePoint = layerPause->getPosition();
    
    
        // Resume button
        auto m_resumeButton = MenuItemImage::create("gameResumeBtn.png", "gameResumeBtn.png", CC_CALLBACK_1(Game::menuResumeCallback, this));
        // Quit button
        auto m_quiteButton = MenuItemImage::create("gameStopBtn.png", "gameStopBtn.png", CC_CALLBACK_1(Game::menuQuitCallback, this));

    
        auto pauseLayerMenu = Menu::create(m_resumeButton, m_quiteButton, NULL);
        pauseLayerMenu->alignItemsHorizontallyWithPadding(layerPauseSizeView.width/8);

        // Pause Layer를 기준으로한 상대좌표로 교환
        auto layerPauseRelativePos = layerPause->convertToNodeSpace(LayerPausePoint);
        pauseLayerMenu->setPosition(layerPauseRelativePos);
    
        layerPause->addChild(pauseLayerMenu);

    return true;
}

/*
void Game::goToPauseScene(cocos2d::Ref *pSender)
{
    auto scene = Pause::createScene();
    Director::getInstance()->pushScene(scene);
}
*/

void Game::GoToOverScene()
{
    auto scene = GameOver::createScene();
    Director::getInstance()->replaceScene(scene);
}



Value Game::timeTransform(cocos2d::Value remainTime){
    
    m_vMinute = 0.0f;
    m_vSecond = 0.0f;
    
    //m_vHour.asFloat() = remainTime.asFloat() / 3600;
    m_vMinute = remainTime.asFloat()/60.0f;
    m_vSecond = fmodf(remainTime.asFloat(), 60.0f);
    
    Value ml_iMinute(m_vMinute.asInt());
    Value ml_iSecond(m_vSecond.asInt());
    
    m_iMinuteDigit = this->calculateTimeDigit(ml_iMinute);
    m_iSecondDigit = this->calculateTimeDigit(ml_iSecond);
    
    // If each minute, second digit is zero, add one more digit number
    if(m_iMinuteDigit == 1){ml_iMinute = "0" + ml_iMinute.asString();}
    if(m_iSecondDigit == 1){ml_iSecond = "0" + ml_iSecond.asString();}
    

    
    Value m_vTimeTrans(ml_iMinute.asString() + " : " + ml_iSecond.asString());
    
    return m_vTimeTrans;
}

int Game::calculateTimeDigit(cocos2d::Value ml_time)
{
    int ml_iDivision = 0;
    int ml_iDigit = 1;
    
    while (1) {
        ml_iDivision = ml_time.asInt() / 10;
        
        if(ml_iDivision == 0){break;}
        
        ml_iDigit++;
        ml_time = ml_iDivision;
    }
    
    return ml_iDigit;
}

void Game::update(float delta)
{
    
}

void Game::gamePlayTimeCountDown(float time)
{
    m_vTimeLimit = m_vTimeLimit.asFloat() - 1;
    
    //log("m_vTimeLimit: %s", m_vTimeLimit.getDescription().c_str());
    auto ml_vTimeFormat = this->timeTransform(m_vTimeLimit);
    gameTimer->setString(ml_vTimeFormat.asString());
    
    if(m_vTimeLimit.asFloat() < 0){
        this->unschedule(schedule_selector(Game::gamePlayTimeCountDown));
        this->GoToOverScene();
    }
}

void Game::menuPauseCallback(Ref* pSender)
{
    //log("called pause function");
    layerPause->setVisible(true);
    
}

void Game::menuResumeCallback(Ref* pSender)
{
    //log("called resume function");
    layerPause->setVisible(false);
}

void Game::menuQuitCallback(Ref* pSender)
{
    //log("called quit function");
    this->unschedule(schedule_selector(Game::gamePlayTimeCountDown));
    this->GoToOverScene();
}



/* Reference
 
     log("minute digit : %d", m_iMinuteDigit);
     log("second digit : %d", m_iSecondDigit);
     log("minute digit : %s", ml_iMinute.getDescription().c_str());
     log("second digit : %s", ml_iSecond.getDescription().c_str());
 

 */



