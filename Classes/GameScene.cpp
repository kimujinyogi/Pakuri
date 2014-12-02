//
//  GameScene.cpp
//  Puzzle2
//
//  Created by otmb on 2014/09/05.
//
//

#include "GameScene.h"

#include "defines.h"

#include "GamePlayLayer.h"
#include "GamePauseMenuLayer.h"

USING_NS_CC;

#define kGAMESCENE_PHYSICS_GRAVITY 1594.0f
#define kGAMESCENE_PHYSICS_SPEED 1.0f
//#define kGAMESCENE_PHYSICS_GRAVITY 94.0f
//#define kGAMESCENE_PHYSICS_SPEED 4.0f

GameScene* GameScene::createScene()
{
    GameScene *ret = new (std::nothrow) GameScene();
    
    //物理演算を使う為にcreateWithPhysicsを使用
    if (ret && ret->initWithPhysics())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

// on "init" you need to initialize your instance
bool GameScene::initWithPhysics()
{
    if (!Scene::initWithPhysics())
        return false;
    
    //Worldに対して重力をセット
    //Vect gravity;
    //gravity.setPoint(0, -50);
//    this->getPhysicsWorld()->setGravity(Vec2(0, -98.0));
    this->getPhysicsWorld()->setGravity(Vec2(0, -kGAMESCENE_PHYSICS_GRAVITY));
    this->getPhysicsWorld()->setSpeed(kGAMESCENE_PHYSICS_SPEED);
//    this->getPhysicsWorld()->setcon
    
    //物理オブジェクトにを可視的にしてくれるデバックモード
//    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // レイヤーを設定する ...
    this->initLayers ();
    
    return true;
}

void GameScene::initLayers ()
{
    // ゲームレイヤーを追加
    m_layerGamePlay = GamePlayLayer::createLayer();
    this->addChild(m_layerGamePlay, LayerType::Game);
    
    m_layerPauseMenu = GamePauseMenuLayer::createLayer();
    this->addChild(m_layerPauseMenu, LayerType::Pause);

    m_layerPauseMenu->setMenuEvent(CC_CALLBACK_1(GameScene::evResume, this),
                                   CC_CALLBACK_1(GameScene::evPause, this),
                                   CC_CALLBACK_1(GameScene::evRotate, this));
    
    // 一時停止のテスト機能
    
    // 1秒後にラムダ式を実行
//    this->runAction(Sequence::create(DelayTime::create(0.3),CallFunc::create([this](){
//        m_layerGamePlay->pause();
//    }), NULL));
    
    //    this->runAction(Sequence::create(DelayTime::create(1.3),CallFunc::create([this](){
    //        //        this->getScene ()->getPhysicsWorld()->set
    //        //        cocos2d::Director::getInstance()->pause();
    //        this->getScene()->getPhysicsWorld()->setSpeed(4);
    //    }), NULL));
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    auto label = Label::createWithTTF("SAIKAI!", kFONT_NORMAL, 30);
//    auto itemLabel0 = MenuItemLabel::create(label, CC_CALLBACK_1(GameScene::actionResume, this));
//    Menu* pMenu = Menu::create(itemLabel0, NULL);
//    pMenu->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.1f));
//    this->addChild(pMenu, 100);
}

//void GameScene::actionResume (Ref* pSender)
//{
//    m_layerGamePlay->resume();
//}

void GameScene::evResume (Ref* pSender)
{
    m_layerGamePlay->resume();
    this->getPhysicsWorld()->setSpeed(kGAMESCENE_PHYSICS_SPEED);
}

void GameScene::evPause (Ref* pSender)
{
    m_layerGamePlay->pause();
    this->getPhysicsWorld()->setSpeed(0.0f);
}

void GameScene::evRotate (Ref* pSender)
{
    m_layerGamePlay->actionRotate();
}








