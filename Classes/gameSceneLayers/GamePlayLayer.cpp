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
    
    _createPosY = winSize.height - 50;
    _mixForce = 150;
    
    float thickWallSize = winSize.height * winSize.width;
    float thickWallSizeHalf = thickWallSize * 0.5f;
    float offsetSize = 50;
    
    // 壁をポリゴンで作って、外に出ないようにする
/*
     [       1       ]
     [ 2  ]       [ 4  ]
     [  3     ][    5  ]
        [   6   ]
*/
    PhysicsMaterial wallMat = PhysicsMaterial(1.0f, 0.0f, 1.0f);
    cocos2d::Size wallSize = cocos2d::Size (thickWallSize, thickWallSize);
//    auto pWall01 = PhysicsBody::createPolygon(spritePoints, 12, PhysicsMaterial(1.0f, 0.0f, 1.0f));
    auto pWall01 = Node::create();
    pWall01->setPhysicsBody(PhysicsBody::createBox(wallSize, wallMat));
    pWall01->getPhysicsBody()->setDynamic(false);
    pWall01->getPhysicsBody()->setGravityEnable(false);
    pWall01->setPosition(cocos2d::Vec2 (VisibleRect::center().x, VisibleRect::top().y + thickWallSizeHalf + 800));
    
    auto pWall02 = Node::create();
    pWall02->setPhysicsBody(PhysicsBody::createBox(wallSize, wallMat));
    pWall02->getPhysicsBody()->setDynamic(false);
    pWall02->getPhysicsBody()->setGravityEnable(false);
    pWall02->setPosition(cocos2d::Vec2 (VisibleRect::left().x - thickWallSizeHalf + offsetSize, VisibleRect::center().y));

    auto pWall03 = Node::create();
    pWall03->setPhysicsBody(PhysicsBody::createBox(wallSize, wallMat));
    pWall03->getPhysicsBody()->setDynamic(false);
    pWall03->getPhysicsBody()->setGravityEnable(false);
    pWall03->setPosition(cocos2d::Vec2 (VisibleRect::right().x + thickWallSizeHalf - offsetSize, VisibleRect::center().y));
    
    auto pWall04 = Node::create();
    pWall04->setPhysicsBody(PhysicsBody::createBox(wallSize, wallMat));
    pWall04->getPhysicsBody()->setDynamic(false);
    pWall04->getPhysicsBody()->setGravityEnable(false);
    pWall04->getPhysicsBody()->setRotationEnable(true);
    pWall04->getPhysicsBody()->setRotationOffset(30);
    pWall04->setPosition(cocos2d::Vec2 (VisibleRect::center().x - thickWallSizeHalf * 0.7, VisibleRect::bottom().y - thickWallSizeHalf + thickWallSizeHalf * 0.2496));
    
    auto pWall05 = Node::create();
    pWall05->setPhysicsBody(PhysicsBody::createBox(wallSize, wallMat));
    pWall05->getPhysicsBody()->setDynamic(false);
    pWall05->getPhysicsBody()->setGravityEnable(false);
    pWall05->getPhysicsBody()->setRotationEnable(true);
    pWall05->getPhysicsBody()->setRotationOffset(-30);
    pWall05->setPosition(cocos2d::Vec2 (VisibleRect::center().x + thickWallSizeHalf * 0.7, VisibleRect::bottom().y - thickWallSizeHalf + thickWallSizeHalf * 0.2496));
    
    auto pWall06 = Node::create();
    pWall06->setPhysicsBody(PhysicsBody::createBox(wallSize, wallMat));
    pWall06->getPhysicsBody()->setDynamic(false);
    pWall06->getPhysicsBody()->setGravityEnable(false);
    pWall06->setPosition(cocos2d::Vec2 (VisibleRect::center().x, VisibleRect::bottom().y - thickWallSizeHalf + offsetSize * 2));
    
    addChild(pWall01);
    addChild(pWall02);
    addChild(pWall03);
    addChild(pWall04);
    addChild(pWall05);
    addChild(pWall06);
    
//    this->setScale(0.01f);
    
//    // これが、壁。
//    Vec2 vec[7] =
//    {
//        Vec2(winSize.width - 30, winSize.height + 300),
//        Vec2(30, winSize.height + 300),
//        Vec2(30, 200),
//        Vec2(winSize.width * 0.33f, 100),
//        Vec2(winSize.width * 0.66f, 100),
//        Vec2(winSize.width - 30, 200),
//        Vec2(winSize.width - 30, winSize.height + 300),
//    };
//    
//    auto wall = Node::create();
//    //wall->setPhysicsBody(PhysicsBody::createEdgeChain(vec, 5, PhysicsMaterial(0.1f, 1.0f, 0.0f)));
//    // 密度、反発、摩擦
//    wall->setPhysicsBody(PhysicsBody::createEdgeChain(vec, 7, PhysicsMaterial(1.0f, 0.0f, 1.0f)));
//    wall->setPosition(0, 0);
//    addChild(wall);
    
    initTouchEvent();
    scheduleUpdate();
    
//    Button* button = Button::create("ball.png");
//    button->setPosition(Vec2(winSize.width, winSize.height - 50));
//    button->addTouchEventListener(CC_CALLBACK_2(GamePlayLayer::touchEvent, this));
//    addChild(button);
    
    _bulletVicts = new std::vector<Vec2*>();
    _fingerPosition = nullptr;
    
    //_spriteNode = SpriteBatchNode::create("ball.png");
    //addChild(_spriteNode);
    
    m_layerBullet = cocos2d::Layer::create();
    addChild(m_layerBullet);
    
    return true;
}

// つむの位置を変更させる
void GamePlayLayer::actionRotate ()
{
    Bullet* bullet;
    auto enemies = m_layerBullet->getChildren();    // Vector
//    CCLOG ("%s", "ACTION");
//    enemies.reverse();
    for (auto target : enemies) {
        bullet = (Bullet*)target;
        PhysicsBody* pBall = bullet->getPhysicsBody();
        int x = arc4random() % 10000000 - 5000000;
        int y = arc4random() % 16000000 - 5000000;
        int side = (arc4random() % 2) == 0 ? bullet->bulletSize * 0.5f : bullet->bulletSize * -0.5f;
        pBall->applyImpulse(Vect(x, y), Vect(side, 0));
//        pBall->applyImpulse(Vect(0, 99999999), Vect(side, 0));
//        pBall->applyTorque(1500);
    }
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

// 更新処理
// 一定のつむを生成し続ける
void GamePlayLayer::update(float dt)
{
    _time += dt;
    
    // 弾の発射判定
    if (MAX_BULLET > _bullet) {
         showBullet();
    }
    
    // 弾の座標が物理演算で変わるので対処
    // _bulletsに選択されたつむが入っているので、毎回位置を設定して線を描画
    // さらに、指を動かしているのであれば、指の線の描画
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

// つむを生成する処理
// 画面の外にランダムで発生させる
void GamePlayLayer::showBullet(){
    
    //auto* sp = Sprite::createWithTexture(_spriteNode->getTexture());
    //addChild(sp,Z_Bullet);
    auto bullet = Bullet::create();
    //srand((unsigned int)time(NULL));
    int tagNum = arc4random()%5;
    
    bullet->setColor(_tagColor[tagNum]);
    
    auto winSize = Director::getInstance()->getWinSize();
    
    // 生成される位置をランダムにしてみよう
    // そして画面の外から
    float randomX = arc4random() % ((int)(winSize.width - bullet->bulletSize * 2)) + bullet->bulletSize;
    bullet->setPosition(randomX, _createPosY);
//    bullet->setPosition(winSize.width/2, winSize.height - bullet->bulletSize);

    PhysicsBody* pBall = bullet->getPhysicsBody();
    pBall->setTag(T_Bullet);
    m_layerBullet->addChild(bullet,Z_Bullet,tagNum+2);
//    addChild(bullet,Z_Bullet,tagNum+2);
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
            // ここでタッチしたものと繋げる事が出来る物を光らせる必要がある
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
        } else {
            // 配列にすでに入っていた
            // 最後の物のみキャンセル出来る
            if (_bullets.size() > 1) {
                Bullet* lastBullet = (_bullets.at(_bullets.size() - 2));
                if (lastBullet == bullet) {
                    _bullets.erase(_bullets.find(_bullets.back()));
                }
            }
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
