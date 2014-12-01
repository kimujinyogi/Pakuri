//
//  CountDownLayer.cpp
//  hockey
//
//  Created by yongwoon on 11/26/14.
//
//

#include "CountDownLayer.h"
#include "defines.h"

USING_NS_CC;

CountDownLayer* CountDownLayer::createLayer()
{
    auto layer = CountDownLayer::create();
    
    return layer;
}

// on "init" you need to initialize your instance
bool CountDownLayer::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    return true;
}


bool CountDownLayer::standByCountDownLabelInit(float timeLimit, ccStandByCallback callback)
{
    m_callback = callback;
    
    // Time Limit
    //m_fRunningStandByTime = 3.0f;
    m_fRunningStandByTime = timeLimit;
    
    // get the device size
    Size viewVisibleSize = Director::getInstance()->getVisibleSize();
    
    // integer to string
    auto m_sTimeString = CCString::createWithFormat("%d", (int)m_fRunningStandByTime);
    
    // timer label
    m_lableStandByTimer = Label::createWithTTF(m_sTimeString->getCString(), kFONT_NORMAL, 90.0);
    m_lableStandByTimer->setPosition(Point(viewVisibleSize.width/2, viewVisibleSize.height/2));
    m_lableStandByTimer->setColor(Color3B::RED);
    
    this->addChild(m_lableStandByTimer);
    
    // Create Scheduler
    this->schedule(schedule_selector(CountDownLayer::standBycountDownTimer), 1.0f);
    return true;
}

bool CountDownLayer::gamePlayCountDownLabelInit(float timeLimit, ccStandByCallback callback)
{
    m_callback = callback;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // Game Play Timer
    m_vGamePlayTimeLimit = timeLimit;
    //Value m_vGamePlayTimeLimit(timeLimit);
    
    m_vTimeFormat = this->timeTransformToDigitalClock(m_vGamePlayTimeLimit);
    
    // create Layer for timer
    auto timerLayer = LayerColor::create(Color4B::WHITE, 250, 80);
    timerLayer->setPosition(visibleSize.width/2, visibleSize.height/2 + 200);
    
    // timer label
    // REF>> layer->getPosition(), layer->getContentSize()
    Size timerLayerVisibleSize = timerLayer->getContentSize();
    m_labelGameTimer = Label::createWithTTF(m_vTimeFormat.asString(), kFONT_NORMAL, 60.0);
    m_labelGameTimer->setPosition(Point(timerLayerVisibleSize.width/2, timerLayerVisibleSize.height/2));
    m_labelGameTimer->setColor(Color3B::RED);
    timerLayer->addChild(m_labelGameTimer);
    
    addChild(timerLayer);
    
    
    
    // Game Timer
    this->schedule(schedule_selector(CountDownLayer::gamePlayTimeCountDown), gamePlayTimeCountUnit);
    this->scheduleUpdate();
    
    // Pause button
    auto m_pauseButton = MenuItemImage::create("gamePauseBtn.png", "gamePauseBtn.png", CC_CALLBACK_1(CountDownLayer::menuPauseCallback, this));
    m_pauseButton->setPosition(Point(visibleSize.width/4 - 200, visibleSize.height/2 + 250));
    
    auto menu = Menu::create(m_pauseButton, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    // Pause Layer
    layerPause = LayerColor::create(Color4B::WHITE, visibleSize.width/2, visibleSize.height/2);
    layerPause->ignoreAnchorPointForPosition(false);
    layerPause->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    layerPause->setVisible(false);
    this->addChild(layerPause);
    
    Size layerPauseSizeView = layerPause->getContentSize();
    Point LayerPausePoint = layerPause->getPosition();
    
    
    // Resume button
    auto m_resumeButton = MenuItemImage::create("gameResumeBtn.png", "gameResumeBtn.png", CC_CALLBACK_1(CountDownLayer::menuResumeCallback, this));
    // Quit button
    auto m_quiteButton = MenuItemImage::create("gameStopBtn.png", "gameStopBtn.png", CC_CALLBACK_1(CountDownLayer::menuQuitCallback, this));
    
    
    auto pauseLayerMenu = Menu::create(m_resumeButton, m_quiteButton, NULL);
    pauseLayerMenu->alignItemsHorizontallyWithPadding(layerPauseSizeView.width/8);
    
    // Pause Layer를 기준으로한 상대좌표로 교환
    auto layerPauseRelativePos = layerPause->convertToNodeSpace(LayerPausePoint);
    pauseLayerMenu->setPosition(layerPauseRelativePos);
    
    layerPause->addChild(pauseLayerMenu);
    
    
    return true;
}

 // don't use this function
 void CountDownLayer::update(float delta)
 {
     log("Timeless: %f", delta);
 }
 
 void CountDownLayer::standBycountDownTimer(float delta)
 {
     m_fRunningStandByTime--;
     
     // integer to string
     auto m_sTimeString2 = CCString::createWithFormat("%d", (int)m_fRunningStandByTime);
     //log("Time: %f", m_fRunningTime);
     m_lableStandByTimer->setString(m_sTimeString2->getCString());
     
     if (m_fRunningStandByTime <= 0) {
         this->unschedule(schedule_selector(CountDownLayer::standBycountDownTimer));
         m_callback ();
     }
 
 }

void CountDownLayer::standBycountDownTimeExtenstion(float extensionTime)
{
    m_fRunningStandByTime = m_fRunningStandByTime + extensionTime;
}


Value CountDownLayer::timeTransformToDigitalClock(cocos2d::Value remainTime){
    
    m_vGamePlayMinute = 0.0f;
    m_vGamePlaySecond = 0.0f;
    
    //m_vHour.asFloat() = remainTime.asFloat() / 3600;
    m_vGamePlayMinute = remainTime.asFloat()/60.0f;
    m_vGamePlaySecond = fmodf(remainTime.asFloat(), 60.0f);
    
    Value ml_iMinute(m_vGamePlayMinute.asInt());
    Value ml_iSecond(m_vGamePlaySecond.asInt());
    
    m_iMinuteDigit = this->calculateTimeDigit(ml_iMinute);
    m_iSecondDigit = this->calculateTimeDigit(ml_iSecond);
    
    // If each minute, second digit is zero, add one more digit number
    if(m_iMinuteDigit == 1){ml_iMinute = "0" + ml_iMinute.asString();}
    if(m_iSecondDigit == 1){ml_iSecond = "0" + ml_iSecond.asString();}
    
    Value m_vTimeTrans(ml_iMinute.asString() + " : " + ml_iSecond.asString());
    
    return m_vTimeTrans;
}

int CountDownLayer::calculateTimeDigit(cocos2d::Value ml_time)
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


void CountDownLayer::gamePlayTimeCountDown(float time)
{
//log("m_vGamePlayTimeLimit:AA: %s", m_vGamePlayTimeLimit.getDescription().c_str());
//log("m_vGamePlayTimeLimit:BB: %s", m_vGamePlayTimeLimit.getDescription().c_str());
//log("ml_vTimeFormat: %s", ml_vTimeFormat.getDescription().c_str());
    
    m_vGamePlayTimeLimit = m_vGamePlayTimeLimit.asFloat() - gamePlayTimeCountUnit;
    
    ml_vTimeFormat = this->timeTransformToDigitalClock(m_vGamePlayTimeLimit);
    
    m_labelGameTimer->setString(ml_vTimeFormat.asString());
    
    if(m_vGamePlayTimeLimit.asFloat() <= 0){
        this->unschedule(schedule_selector(CountDownLayer::gamePlayTimeCountDown));
        m_callback ();
    }
}

void CountDownLayer::menuPauseCallback(Ref* pSender)
{
    layerPause->setVisible(true);
    // schedule Pause
    Director::getInstance()->getScheduler()->pauseTarget(this);
    
}

void CountDownLayer::menuResumeCallback(Ref* pSender)
{
    layerPause->setVisible(false);
    // schedule Resume
    Director::getInstance()->getScheduler()->resumeTarget(this);
}

void CountDownLayer::menuQuitCallback(Ref* pSender)
{
    this->unschedule(schedule_selector(CountDownLayer::gamePlayTimeCountDown));
    m_callback ();
}

 

 


 