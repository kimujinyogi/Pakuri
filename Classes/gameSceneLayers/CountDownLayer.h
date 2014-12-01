//
//  CountDownLayer.h
//  hockey
//
//  Created by yongwoon on 11/26/14.
//
//

#ifndef __hockey__CountDownLayer__
#define __hockey__CountDownLayer__

#include "cocos2d.h"

// Declare Callback
typedef std::function<void()> ccStandByCallback;

class CountDownLayer : public cocos2d::Layer
{
private:
    ccStandByCallback m_callback;
    
public:
    static CountDownLayer* createLayer();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual bool standByCountDownLabelInit(float timeLimit, ccStandByCallback callback);
    virtual bool gamePlayCountDownLabelInit(float timeLimit, ccStandByCallback callback);
    
    // Declare Variable
    public: cocos2d::Label* m_lableStandByTimer;
    private: float m_fRunningStandByTime;

    // Declare Functions
    void standBycountDownTimer(float delta);
    void standBycountDownTimeExtenstion(float extensionTime);
    
    // For schedule update
    virtual void update(float delta);
    
    
    
    // Game Play Count Down
    // Layer
    cocos2d::LayerColor* layerPause;
    
    
    //Timer
    public: cocos2d::Value m_vGamePlayTimeLimit;
    public: cocos2d::Value m_vTimeFormat;
    //private: cocos2d::Value m_vHour;
    private: cocos2d::Value m_vGamePlayMinute;
    private: cocos2d::Value m_vGamePlaySecond;
    private: cocos2d::Value ml_vTimeFormat;
    private: int m_iMinuteDigit;
    private: int m_iSecondDigit;
    private: cocos2d::Label* m_labelGameTimer;
    
    
    void getGamePlayedTime(Ref *pSender);
    void gamePlayTimeCountDown(float delta);
    
    int calculateTimeDigit(cocos2d::Value ml_time);
    cocos2d::Value timeTransformToDigitalClock(cocos2d::Value remainTime);
    
    
    // callbacks(Puase, Resume, Quit)
    void menuPauseCallback(Ref *pSender);
    void menuResumeCallback(Ref *pSender);
    void menuQuitCallback(Ref *pSender);
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(CountDownLayer);
    
};

#endif /* defined(__hockey__CountDownLayer__) */
