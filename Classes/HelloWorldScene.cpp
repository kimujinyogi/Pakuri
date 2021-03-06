#include "HelloWorldScene.h"
#include "defines.h"
#include "GameScene.h"

//#include "cocostudio/CocoStudio.h"


// I'm comming
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    
    
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    CCLOG("%f, %f", visibleSize.width, visibleSize.height);
    CCLOG("%f, %f", origin.x, origin.y);
    
    auto text = Label::createWithSystemFont("Touch Layer", "HiraKakuProN-W6", 48);
    text->setPosition(Point(300, 200));
    this->addChild(text);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

	// テストボタン、通信開始
	auto networkItem = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuNetworkTest, this));

	networkItem->setPosition(Vec2(origin.x + visibleSize.width - networkItem->getContentSize().width/2 ,
			origin.y + networkItem->getContentSize().height/2));


    // create menu, it's an autorelease object
    auto menu = Menu::create(networkItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // なんか背景を表示
    //CCSpriteクラスを初期化しています。
    auto sprite = Sprite::create("top.jpg");
    SpriteFrame* frame = sprite->getSpriteFrame();
    Size size = frame->getOriginalSize();
    sprite->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    sprite->setScale(visibleSize.width/size.width);

    this->addChild(sprite, 0);

//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

// テストイベント、ここで通信を試してみる
void HelloWorld::menuNetworkTest(Ref* pSender)
{
    // create a scene. it's an autorelease object
    auto scene = GameScene::createScene();

    // run
    Director::getInstance()->replaceScene(scene);
    
    // CocosStudioのLayout読み込み
//    auto layout = cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("studio/Default/MainScene.csb");
//    this->addChild(layout);
    
//	// MessageBox("zzzzzz","HOHOHO");
//    NetManager* netmgr = NetManager::getInstance();
//    netmgr->test();
	return;
}
