//
//  GamePlayLayer.h
//  TestProject
//
//  Created by KimJinHyuck on 2014/11/26.
//
//

#ifndef __TestProject__GamePlayLayer__
#define __TestProject__GamePlayLayer__

#include "cocos2d.h"

#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "UIDialog.h"
#include "Bullet.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;

class GamePlayLayer : public cocos2d::Layer
{
protected:
    enum ZOrder
    {
        Z_Bg = 0,
        Z_Bullet,
        Z_Line,
        Z_Dialog,
    };
    
    enum Tag
    {
        T_Bullet = 1,
        T_Bullet1,
        T_Bullet2,
        T_Bullet3,
        T_Bullet4,
        T_Bullet5,
        T_Dialog,
        T_Line,
    };
    
    float _time;
    int _bullet;
    int _tag;
    UIDialog* _dialog;
    
    void initTouchEvent();
    void showBullet();
    
    //void addLayer();
    
    //cocos2d::Action* dialogClose();
    
    cocos2d::Color3B _tagColor[5]{
        cocos2d::Color3B(0,255,255),
        cocos2d::Color3B(0,0,255),
        cocos2d::Color3B(128,128,128),
        cocos2d::Color3B(255,0,0),
        cocos2d::Color3B(255,255,255)
    };
    //void dialogClose();
    void DrawLineRemove();
    
    //SpriteBatchNode* _spriteNode;
    Vector<Bullet*> _bullets;
    std::vector<Vec2*> * _bulletVicts;
    Vec2* _fingerPosition;
    // 生成するポジションをずらす為のもの
    float _createPosY;
    
    cocos2d::Layer* m_layerBullet;
    
public:
    static GamePlayLayer* createLayer();
    virtual bool init();
    CREATE_FUNC(GamePlayLayer);
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* evnet);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* evnet);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* evnet);
    virtual void update(float dt);
    void touchEvent(Ref *pSender, Widget::TouchEventType type);
    //void dialogClose(Ref *pSender, Widget::TouchEventType type);
    void dialogClose();
    
    void actionRotate ();
    
    //Vector<Vec2*> _bulletVicts; // これは出来ない
};


#endif /* defined(__TestProject__GamePlayLayer__) */
