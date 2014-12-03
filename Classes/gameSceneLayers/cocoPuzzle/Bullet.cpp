//
//  Bullet.cpp
//  Puzzle2
//
//  Created by otmb on 2014/09/05.
//
//

#include "Bullet.h"

USING_NS_CC;

//コンストラクタ
Bullet::Bullet()
: _state(State::Moving)
{
}

Bullet* Bullet::create()
{
    
    auto node = new Bullet();
    node->init();
    node->autorelease();
    
    return node;
}

bool Bullet::init()
{
//    if (!Sprite::initWithFile("faceball.png")){
    if (!Sprite::initWithFile("ball.png")){
        return false;
    }
    
    // 大きさをランダムにとりあえず
    bulletSize = arc4random() % 20 + 45;
//    this->setContentSize(cocos2d::Size (bulletSize * 20, bulletSize * 20));
    // もともと設定されてたもの
    // なんか、物理エンジンがおかしくなるような気がする
    // これを消すと落ち着く
    this->setScale(0.13f * bulletSize);
    
    //this->setScale(0.043f * bulletSize);
    // 密度、反発、摩擦
    // まるいやつ。回転がわかりズラい
//    auto pBall = PhysicsBody::createCircle(bulletSize,
//                                           PhysicsMaterial(10.0f, 0.6f, 0.3f));
    
    // しかくいやつ。これは四角すぎる
//    auto pBall = PhysicsBody::createBox(cocos2d::Size(bulletSize, bulletSize), PhysicsMaterial(1.0f, 0.6f, 0.3f));

    Point spritePoints[12] =
    {
        Point(-1, 0.333) *= bulletSize, Point(-0.666, 0.5) *= bulletSize, Point(-0.333, 0.666) *= bulletSize,
        Point(0.333, 0.666) *= bulletSize, Point(0.666, 0.5) *= bulletSize, Point(1, 0.333) *= bulletSize,
        Point(1, -0.333) *= bulletSize, Point(0.666, -0.5) *= bulletSize, Point(0.333, -0.666) *= bulletSize,
        Point(-0.333, -0.666) *= bulletSize, Point(-0.666, -0.5) *= bulletSize, Point(-1, -0.333) *= bulletSize
    };

//    for (Point target : spritePoints) {
//        target *= bulletSize;
//    }
    // 密度、反発、摩擦
    auto pBall = PhysicsBody::createPolygon(spritePoints, 12, PhysicsMaterial(1.0f, 0.0f, 1.0f));
//    auto pBall = PhysicsBody::createPolygon(spritePoints, 12, PhysicsMaterial(1.0f, 0.6f, 0.3f));
    
    pBall->setDynamic(true);
    pBall->setRotationEnable(true);
    // 回転率？なのか？これを無限にすると回転しない
//    pBall->setMoment(PHYSICS_INFINITY);
//    pBall->setMoment(bulletSize);
    pBall->setGravityEnable(true);
    //log("%f",pBall->getMass());
//    pBall->setMass(1.0);
    
    pBall->setVelocityLimit(800);
    
    this->setPhysicsBody(pBall);
    
    return true;
    
}

void Bullet::brokenBullet()
{
    stopAllActions();
    // 弾を消すアクションを起こす
    Action* action = RemoveSelf::create();
    runAction(action);
    
    _state = State::Broken;
}

