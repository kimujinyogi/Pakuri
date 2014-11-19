#include "GameReadyMenuScene.h"
#include "defines.h"

#include "UseMenuItemLabel.h"
#include "GameScene.h"

//#include "cocostudio/CocoStudio.h"

// I'm comming
USING_NS_CC;

#define kINTRO_COUNTTIME 5

#define kSTR_MODORU "Modoru"
#define KSTR_START "Start"
#define kSTR_MANAGE "Manage"

#define kSTR_SCORE_ON "SCORE ON"
#define kSTR_SCORE_OFF "SCORE OFF"
#define kSTR_COIN_ON "COIN ON"
#define kSTR_COIN_OFF "COIN OFF"
#define kSTR_EXP_ON "EXP ON"
#define kSTR_EXP_OFF "EXP OFF"
#define kSTR_TIME_ON "TIME ON"
#define kSTR_TIME_OFF "TIME OFF"
#define kSTR_BOMB_ON "BOMB ON"
#define kSTR_BOMB_OFF "BOMB OFF"
#define kSTR_TYPE_ON "TYPE ON"
#define kSTR_TYPE_OFF "TYPE OFF"

Scene* GameReadyMenuScene::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameReadyMenuScene::create();
    
    // add layer as a child to scene
    
    
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameReadyMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto label = Label::createWithTTF("GameReadyMenu", kFONT_NORMAL, 40);
    // position the label on the center of the screen
    label->setPosition(Vec2(visibleSize.width * 0.5f,
                            visibleSize.height - 20));
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // --------------------------------
    // 上に２行ぐらい
    // 真ん中　３行
    // 下に１行
    // --------------------------------
    
    // レベルラベル
    this->m_pLabelLevel = Label::createWithTTF("1", kFONT_NORMAL, 30);
    this->m_pLabelLevel->setAlignment(cocos2d::TextHAlignment::CENTER);
    this->m_pLabelLevel->setClipMarginEnabled (true);
    this->m_pLabelLevel->setDimensions(60, 30);
    this->m_pLabelLevel->setPosition(40, visibleSize.height - 50);
    this->addChild(this->m_pLabelLevel, 1);
    // 経験値ラベル
    this->m_pLabelExp = Label::createWithTTF("10000", kFONT_NORMAL, 30);
    this->m_pLabelExp->setAlignment(cocos2d::TextHAlignment::LEFT);
    this->m_pLabelExp->setClipMarginEnabled (true);
    this->m_pLabelExp->setDimensions(210, 30);
    this->m_pLabelExp->setPosition(170, visibleSize.height - 50);
    this->addChild(this->m_pLabelExp, 1);
    
    // 戻るボタン (今は意味がない)
    label = Label::createWithTTF(kSTR_MODORU, kFONT_NORMAL, 30);
    auto itemLabel0 = MenuItemLabel::create(label, CC_CALLBACK_1(GameReadyMenuScene::movePrevScene, this));
    itemLabel0->setPositionX(-200.0f);
    // スタートボタン
    label = Label::createWithTTF(KSTR_START, kFONT_NORMAL, 30);
    auto itemLabel1 = MenuItemLabel::create(label, CC_CALLBACK_1(GameReadyMenuScene::moveNextScene, this));
    // ツム管理画面へ移動するボタン (今は意味がない)
    label = Label::createWithTTF(kSTR_MANAGE, kFONT_NORMAL, 30);
    auto itemLabel2 = MenuItemLabel::create(label, CC_CALLBACK_1(GameReadyMenuScene::moveManageScene, this));
    itemLabel2->setPositionX(200.0f);
    //メニューの作成　pMenuの中にpBtnItemを入れる
    Menu* pMenu = Menu::create(itemLabel0, itemLabel1, itemLabel2, NULL);
    
    //pMenuを画面中央に配置
    pMenu->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.1f));
    this->addChild(pMenu);
    
    
    // スコア＋＋切り替えボタン
    label = Label::createWithTTF("", kFONT_NORMAL, 30);
    auto useScore = GameReadyMenu::UseMenuItemLabel::create(label, CC_CALLBACK_1(GameReadyMenuScene::flipUseItem, this), GameInfo::Score, kSTR_SCORE_ON, kSTR_SCORE_OFF);
    useScore->setPosition(-200.0f, 100.0f);
    // コイン＋＋切り替えボタン
    label = Label::createWithTTF("", kFONT_NORMAL, 30);
    auto useCoin = GameReadyMenu::UseMenuItemLabel::create(label, CC_CALLBACK_1(GameReadyMenuScene::flipUseItem, this), GameInfo::Coin, kSTR_COIN_ON, kSTR_COIN_OFF);
    useCoin->setPosition(0.0f, 100.0f);
    // 経験値＋＋切り替えボタン
    label = Label::createWithTTF("", kFONT_NORMAL, 30);
    auto useExp = GameReadyMenu::UseMenuItemLabel::create(label, CC_CALLBACK_1(GameReadyMenuScene::flipUseItem, this), GameInfo::Exp, kSTR_EXP_ON, kSTR_EXP_OFF);
    useExp->setPosition(200.0f, 100.0f);
    // 時間＋＋切り替えボタン
    label = Label::createWithTTF("", kFONT_NORMAL, 30);
    auto useTime = GameReadyMenu::UseMenuItemLabel::create(label, CC_CALLBACK_1(GameReadyMenuScene::flipUseItem, this), GameInfo::Time, kSTR_TIME_ON, kSTR_TIME_OFF);
    useTime->setPosition(-200.0f, -100.0f);
    // 爆弾＋＋切り替えボタン
    label = Label::createWithTTF("", kFONT_NORMAL, 30);
    auto useBomb = GameReadyMenu::UseMenuItemLabel::create(label, CC_CALLBACK_1(GameReadyMenuScene::flipUseItem, this), GameInfo::Bomb, kSTR_BOMB_ON, kSTR_BOMB_OFF);
    useBomb->setPosition(0.0f, -100.0f);
    // 種類＋＋切り替えボタン
    label = Label::createWithTTF("", kFONT_NORMAL, 30);
    auto useType = GameReadyMenu::UseMenuItemLabel::create(label, CC_CALLBACK_1(GameReadyMenuScene::flipUseItem, this), GameInfo::Type, kSTR_TYPE_ON, kSTR_TYPE_OFF);
    useType->setPosition(200.0f, -100.0f);
    //メニューの作成　pMenuの中にpBtnItemを入れる
    Menu* pUseMenu = Menu::create(useScore, useCoin, useExp, useTime, useBomb, useType, NULL);
    pUseMenu->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
    this->addChild(pUseMenu);
    
    return true;
}

void GameReadyMenuScene::moveNextScene (Ref* pSender)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void GameReadyMenuScene::movePrevScene (Ref* pSender)
{
    
}

void GameReadyMenuScene::moveManageScene (Ref* pSender)
{
    
}

void GameReadyMenuScene::flipUseItem (Ref* pSender)
{
    GameReadyMenu::UseMenuItemLabel* lab = (GameReadyMenu::UseMenuItemLabel*)pSender;
    switch (lab->getFlag ()) {
        case GameInfo::Score:
            CCLOG ("%s", "SCORE");
            break;
        case GameInfo::Coin:
            break;
        case GameInfo::Exp:
            break;
        case GameInfo::Time:
            break;
        case GameInfo::Bomb:
            CCLOG ("%s", "BOMB");
            break;
        case GameInfo::Type:
            break;
        default:
            break;
    }
}







