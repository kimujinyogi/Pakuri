//
//  GamePlayLayer.cpp
//  TestProject
//
//  Created by KimJinHyuck on 2014/11/26.
//
//

#include "GamePlayLayer.h"

#include "defines.h"

#include "Bullet.h"
#include "UIDialog.h"
#include "DrawLine.h"


USING_NS_CC;

#define MAX_BULLET 45

GamePlayLayer* GamePlayLayer::createLayer()
{
    auto layer = GamePlayLayer::create();
    
    return layer;
}

// on "init" you need to initialize your instance
bool GamePlayLayer::init()
{
    if (!Layer::init())
        return false;
    
    auto winSize = Director::getInstance()->getWinSize();
    
    Vec2 vec[6] =
    {
        Vec2(winSize.width-1, winSize.height -1),
        Vec2(1, winSize.height -1),
        Vec2(1, 100),
        Vec2(winSize.width/2, 0),
        Vec2(winSize.width-1,100),
        Vec2(winSize.width-1,winSize.height -1),
    };
    
    auto wall = Node::create();
    //wall->setPhysicsBody(PhysicsBody::createEdgeChain(vec, 5, PhysicsMaterial(0.1f, 1.0f, 0.0f)));
    // 密度、反発、摩擦
    wall->setPhysicsBody(PhysicsBody::createEdgeChain(vec, 6, PhysicsMaterial(0.0f, 0.0f, 0.5f)));
    wall->setPosition(0, 0);
    addChild(wall);
    
    initTouchEvent();
    scheduleUpdate();
    
    Button* button = Button::create("ball.png");
    button->setPosition(Vec2(winSize.width,winSize.height - 50));
    button->addTouchEventListener(CC_CALLBACK_2(GamePlayLayer::touchEvent, this));
    addChild(button);
    
    _bulletVicts = new std::vector<Vec2*>();
    _fingerPosition = nullptr;
    
    //_spriteNode = SpriteBatchNode::create("ball.png");
    //addChild(_spriteNode);
    
    return true;
}

void GamePlayLayer::actionResume (Ref* pSender)
{
    
}

void GamePlayLayer::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    //std::function<void(Ref*,Widget::TouchEventType)> callback = CC_CALLBACK_0(GamePlayLayer::dialogClose,this);
    Widget::ccWidgetTouchCallback callback = CC_CALLBACK_0(GamePlayLayer::dialogClose,this);
    _dialog = UIDialog::create(callback);
    addChild(_dialog,Z_Dialog,T_Dialog);
}

//void GamePlayLayer::dialogClose(Ref *pSender, Widget::TouchEventType type)
void GamePlayLayer::dialogClose()
{
    auto nodes = getChildren();
    
    for (auto node : nodes)
    {
        switch (node->getTag())
        {
            case T_Dialog:
                UIDialog* dialog = static_cast<UIDialog*>(node);
                dialog->close();
                break;
        }
    }
}

void GamePlayLayer::update(float dt)
{
    _time += dt;
    
    // 弾の発射判定
    if (MAX_BULLET > _bullet) showBullet();
    
    // 弾の座標が物理演算で変わるので対処
    //std::vector<Vec2*> * victs = new std::vector<Vec2*>();
    for(auto* bullet : _bullets){
        _bulletVicts->push_back(new Vec2(bullet->getPosition()));
    }
    if (_fingerPosition != nullptr)
        _bulletVicts->push_back(_fingerPosition);
    
    DrawLineRemove();
    // 線を引く
    DrawLine* node = DrawLine::create(_bulletVicts);
    addChild(node,Z_Line,T_Line);
    _bulletVicts->clear();
}

void GamePlayLayer::showBullet(){
    
    //auto* sp = Sprite::createWithTexture(_spriteNode->getTexture());
    //addChild(sp,Z_Bullet);
    auto bullet = Bullet::create();
    //srand((unsigned int)time(NULL));
    int tagNum = arc4random()%5;
    
    bullet->setColor(_tagColor[tagNum]);
    
    auto winSize = Director::getInstance()->getWinSize();
    bullet->setPosition(winSize.width/2, winSize.height - bullet->bulletSize);
    
    PhysicsBody* pBall = bullet->getPhysicsBody();
    pBall->setTag(T_Bullet);
    
    addChild(bullet,Z_Bullet,tagNum+2);
    _bullet++;
}

void GamePlayLayer::initTouchEvent()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GamePlayLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GamePlayLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GamePlayLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
}

#define mark - タップイベント

bool GamePlayLayer::onTouchBegan(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    auto arr = this->getScene()->getPhysicsWorld()->getShapes(location);
    
    for (auto& obj : arr)
    {
        if ((obj->getBody()->getTag() & T_Bullet) != 0)
        {
            _tag = static_cast<Bullet*>(obj->getBody()->getNode())->getTag();
            break;
        }
    }
    return true;
}

void GamePlayLayer::onTouchMoved(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    auto arr = this->getScene()->getPhysicsWorld()->getShapes(location);
    
    //_bullets = Vector<Bullet*>();
    //std::vector<Vec2*> * _bulletVicts = new std::vector<Vec2*>();
    
    Bullet* bullet = nullptr;
    for (auto& obj : arr)
    {
        if ((obj->getBody()->getTag() & T_Bullet) != 0)
        {
            bullet = static_cast<Bullet*>(obj->getBody()->getNode());
            if (bullet->getTag() == _tag){
                break;
            } else {
                bullet = nullptr;
            }
        }
    }
    if (bullet != nullptr
        && bullet->getState() == Bullet::State::Moving){
        
        if (_bullets.empty()){ // 空
            _bullets.pushBack(bullet);
        } else if (!_bullets.contains(bullet)){ // 配列に入っていない
            // 距離の比較
            float distance = _bullets.back()->getPosition().distance(bullet->getPosition());
            //log("%f",distance);
            if (distance < bullet->bulletSize * 3.0f){
                _bullets.pushBack(bullet);
            }
            //} else if (_bullets.back() == bullet) {
            //    _bullets.erase(_bullets.find(bullet));
        }
    }
    if (_bullets.size() < 2){
        _fingerPosition = new Vec2(location);
    } else {
        _fingerPosition = nullptr;
    }
    
    //DrawLine* node = DrawLine::create();
    //addChild(node);
}

void GamePlayLayer::onTouchEnded(Touch* touch, Event* event)
{
    // 2個以上で削除
    if (!_bullets.empty() && _bullets.size() > 2){
        for (auto* bullet : _bullets){
            if (bullet->getState() == Bullet::State::Moving){
                bullet->brokenBullet();
                _bullet--;
            }
        }
    }
    _bullets.clear();
    //_bulletVicts->clear();
}

void GamePlayLayer::DrawLineRemove()
{
    auto nodes = getChildren();
    
    for (auto node : nodes)
    {
        switch (node->getTag())
        {
            case T_Line:
                DrawLine* line = static_cast<DrawLine*>(node);
                line->remove();
                break;
        }
    }
}
