#include "GameReadyMenuScene.h"
#include "defines.h"

#include "GameScene.h"

//#include "cocostudio/CocoStudio.h"

// I'm comming
USING_NS_CC;

#define kINTRO_COUNTTIME 5

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
    this->pLabelLevel = Label::createWithTTF("1", kFONT_NORMAL, 30);
    this->pLabelLevel->setAlignment(cocos2d::TextHAlignment::CENTER);
    this->pLabelLevel->setClipMarginEnabled (true);
    this->pLabelLevel->setDimensions(60, 30);
    this->pLabelLevel->setPosition(40, visibleSize.height - 50);
    this->addChild(this->pLabelLevel, 1);
    // 経験値ラベル
    this->pLabelExp = Label::createWithTTF("10000", kFONT_NORMAL, 30);
    this->pLabelExp->setAlignment(cocos2d::TextHAlignment::LEFT);
    this->pLabelExp->setClipMarginEnabled (true);
    this->pLabelExp->setDimensions(210, 30);
    this->pLabelExp->setPosition(170, visibleSize.height - 50);
    this->addChild(this->pLabelExp, 1);

    // 戻るボタン (今は意味がない)
    label = Label::createWithTTF("Modoru", kFONT_NORMAL, 30);
    auto itemLabel0 = MenuItemLabel::create(label, CC_CALLBACK_1(GameReadyMenuScene::movePrevScene, this));
    itemLabel0->setPositionX(-200.0f);
    // スタートボタン
    label = Label::createWithTTF("Start", kFONT_NORMAL, 30);
    auto itemLabel1 = MenuItemLabel::create(label, CC_CALLBACK_1(GameReadyMenuScene::moveNextScene, this));
    // ツム管理画面へ移動するボタン (今は意味がない)
    label = Label::createWithTTF("Manage", kFONT_NORMAL, 30);
    auto itemLabel2 = MenuItemLabel::create(label, CC_CALLBACK_1(GameReadyMenuScene::moveManageScene, this));
    itemLabel2->setPositionX(200.0f);
    //メニューの作成　pMenuの中にpBtnItemを入れる
    Menu* pMenu = Menu::create(itemLabel0, itemLabel1, itemLabel2, NULL);
    
    //pMenuを画面中央に配置
    pMenu->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.1f));
    this->addChild(pMenu);
    
    
    // スコア＋＋切り替えボタン
    // コイン＋＋切り替えボタン
    // 経験値＋＋切り替えボタン
    // 時間＋＋切り替えボタン
    // 爆弾＋＋切り替えボタン
    // 種類＋＋切り替えボタン
    
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

