//
//  GamePauseMenuLayer.cpp
//  TestProject
//
//  Created by KimJinHyuck on 2014/11/28.
//
//

#include "GamePauseMenuLayer.h"

#include "defines.h"

#include "GameReadyMenuScene.h"

GamePauseMenuLayer* GamePauseMenuLayer::createLayer()
{
    auto layer = GamePauseMenuLayer::create();
    
    return layer;
}

// on "init" you need to initialize your instance
bool GamePauseMenuLayer::init()
{
    if (!Layer::init())
        return false;
    
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    
    // スキル使用ボタン
    auto label = cocos2d::Label::createWithTTF("Skill", kFONT_NORMAL, 30);
    auto itemLabel1 = cocos2d::MenuItemLabel::create(label, CC_CALLBACK_1(GamePauseMenuLayer::doSkill, this));
    itemLabel1->setPositionX(-200);
    label = cocos2d::Label::createWithTTF("Shake", kFONT_NORMAL, 30);
    auto itemLabel2 = cocos2d::MenuItemLabel::create(label, CC_CALLBACK_1(GamePauseMenuLayer::doShake, this));
    itemLabel2->setPositionX(200);
    
    cocos2d::Menu* pMenuSkill = cocos2d::Menu::create(itemLabel1, itemLabel2, NULL);
    pMenuSkill->setPositionY(30);
    this->addChild(pMenuSkill);
    
    
    // 一時停止ボタン
    label = cocos2d::Label::createWithTTF("Pause", kFONT_NORMAL, 30);
    auto itemLabel3 = cocos2d::MenuItemLabel::create(label, CC_CALLBACK_1(GamePauseMenuLayer::doPauseGame, this));
    itemLabel3->setPositionX(200);
    
    cocos2d::Menu* pMenuMenu = cocos2d::Menu::create(itemLabel3, NULL);
    pMenuMenu->setPositionY(visibleSize.height - 30);
    this->addChild(pMenuMenu);
   
    
    
    // ~ 一時停止のレイヤーを作成 ~
    m_layerMenu = cocos2d::Layer::create();
    this->addChild(m_layerMenu, 10);
    // 色設定
    auto foreground = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 128));
    m_layerMenu->addChild(foreground, 10);
    m_layerMenu->setVisible(false);
    
    // 一時停止ボタン
    label = cocos2d::Label::createWithTTF("Resume", kFONT_NORMAL, 45);
    auto menuItemResume = cocos2d::MenuItemLabel::create(label, CC_CALLBACK_1(GamePauseMenuLayer::doResumeGame, this));
    menuItemResume->setPositionY(150);
    label = cocos2d::Label::createWithTTF("Exit", kFONT_NORMAL, 45);
    auto menuItemEnd = cocos2d::MenuItemLabel::create(label, CC_CALLBACK_1(GamePauseMenuLayer::doEndGame, this));
    menuItemEnd->setPositionY(-150);
    
    cocos2d::Menu* pMenuPause = cocos2d::Menu::create(menuItemResume, menuItemEnd, NULL);
    m_layerMenu->addChild(pMenuPause, 11);
    
    
    //TouchOneByOneの他にTouchAllAtOne(複数タッチ)もあるお！
    //    m_eventListener = cocos2d::EventListenerTouchOneByOne::create();
    //    //でもAllAtOnceならonTouch"es"Beganになる。
    //    m_eventListener->onTouchBegan = CC_CALLBACK_2(GamePauseMenuLayer::onTouchBegan, this);
    //    m_eventListener->onTouchMoved = CC_CALLBACK_2(GamePauseMenuLayer::onTouchMoved, this);
    //    m_eventListener->onTouchEnded = CC_CALLBACK_2(GamePauseMenuLayer::onTouchEnded, this);
    this->m_isPause = false;
    return true;
}

void GamePauseMenuLayer::setMenuEvent (const callbackGamemenu& callbackResume,
                                       const callbackGamemenu& callbackPause,
                                       const callbackGamemenu& callbackRotate)
{
    this->m_cbResume = callbackResume;
    this->m_cbPause = callbackPause;
    this->m_cbRotate = callbackRotate;
}

void GamePauseMenuLayer::pauseGame ()
{
    m_layerMenu->setVisible(true);
    // タッチリスナー登録
    //    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_eventListener, this);
}

void GamePauseMenuLayer::doResumeGame (Ref* pSender)
{
    if (this->m_isPause) {
        m_layerMenu->setVisible(false);
        // タッチリスナーの削除
        //    this->getEventDispatcher()->removeEventListener(m_eventListener);
        if (this->m_cbResume)
            this->m_cbResume (this);
        this->m_isPause = !this->m_isPause;
    }
}

void GamePauseMenuLayer::doPauseGame (Ref* pSender)
{
    if (!this->m_isPause) {
        // 一時停止メニューを開く
        this->pauseGame ();
        // ゲームシーンにpause状態だと知らせる
        if (this->m_cbPause)
            this->m_cbPause (this);
    }
    this->m_isPause = !this->m_isPause;
}

void GamePauseMenuLayer::doEndGame (Ref* pSender)
{
    // ゲームを終了していいかポップアップを出して、
    auto scene = GameReadyMenuScene::createScene();
    cocos2d::Director::getInstance()->replaceScene(scene);
}



void GamePauseMenuLayer::doSkill (Ref* pSender)
{
    if (this->m_isPause)
        return;
}

void GamePauseMenuLayer::doShake (Ref* pSender)
{
    if (this->m_isPause)
        return;
    if (this->m_cbRotate)
        this->m_cbRotate (this);
}







