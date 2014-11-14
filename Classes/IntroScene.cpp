#include "IntroScene.h"
#include "defines.h"

#include "GameReadyMenuScene.h"

//#include "cocostudio/CocoStudio.h"

// I'm comming
USING_NS_CC;

#define kINTRO_COUNTTIME 0

Scene* IntroScene::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = IntroScene::create();

    // add layer as a child to scene
    
    
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IntroScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // ３秒をカウントしてみる
    // これを使ってゲーム開始時のスタートを実装しよう
    this->iCount = kINTRO_COUNTTIME;
    
    this->labelCount = Label::createWithTTF("", kFONT_NORMAL, 30);
    this->labelCount->setAlignment(cocos2d::TextHAlignment::CENTER);
    this->labelCount->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
    this->addChild(this->labelCount, 1);
    
    this->startCount();
    
    return true;
}

// 現在のカウントをラベルに表示
void IntroScene::setCountLabel ()
{
    std::string str = this->labelCount->getString();
    switch (this->iCount) {
        case kINTRO_COUNTTIME:
            str = str.append("Project");
            break;
        case (kINTRO_COUNTTIME - 1):
            str = str.append("\nby");
            break;
        case (kINTRO_COUNTTIME - 2):
            str = str.append("\nU & 2KIM");
            break;
        case (kINTRO_COUNTTIME - 3):
            str = str.append("\nsince 2014");
        default:
            break;
    }
    this->labelCount->setString(str.c_str());

}

// １秒後に更新する
void IntroScene::startCount ()
{
    this->setCountLabel();
    this->iCount--;
    // 1秒後にラムダ式を実行
    this->runAction(Sequence::create(DelayTime::create(1),CallFunc::create([this](){
        // カウントが０になったら、次のシーンに移動するように
        if (this->iCount <= 0) {
            this->moveNextScene();
        } else {
            // 数字をもう一度表示させる
            this->startCount();
        }
    }), NULL));
}

void IntroScene::moveNextScene ()
{
    auto scene = GameReadyMenuScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
