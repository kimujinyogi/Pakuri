//
//  Bullet.h
//  Puzzle2
//
//  Created by otmb on 2014/09/05.
//
//

#ifndef __Puzzle2__Bullet__
#define __Puzzle2__Bullet__

#include "cocos2d.h"

class Bullet : public cocos2d::Sprite
{
public:
    
    // 弾の状態
    enum class State
    {
        Moving, // 移動中
        Broken, // 壊れる
    };
    
    Bullet();
    static Bullet* create(int tag);
    bool init (int tag);
    //CREATE_FUNC(Bullet);
    
    void setSelectableColor (bool flag);    // 色を変更させる（選択可能と知らせる）
    void brokenBullet(); // 弾が壊れる
    float bulletSize = 45.0f;
    
    
    CC_SYNTHESIZE_READONLY(State, _state, State); // 弾の状態
    CC_SYNTHESIZE_READONLY(int, m_tag, Tag); // 弾の状態
};

#endif /* defined(__Puzzle2__Bullet__) */
