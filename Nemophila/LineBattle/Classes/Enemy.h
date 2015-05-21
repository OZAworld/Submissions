//
//  Enemy.h
//  LineBattle
//
//  Created by 小澤勇太 on 2014/12/10.
//
//

#ifndef __LineBattle__Enemy__
#define __LineBattle__Enemy__

#include "cocos2d.h"
#include <random>
#include "Character.h"

class Enemy : public cocos2d::Sprite
{
public:
    //  敵の状態
    enum class State
    {
        Moving,
        Death,
    };
    
    enum class EnemyType
    {
        Blue,
        Red,
        Green,
        Yellow,
        Purple,
        Heal,
    };
    
    Enemy();
    //static Enemy* create();
    //virtual bool init();
    
    State enemyState;
    
    static Enemy* create(EnemyType type, bool visible);
    virtual bool init(EnemyType type, bool visible);
    
    CC_SYNTHESIZE_READONLY(State, _state, State);   //状態
    CC_SYNTHESIZE_READONLY(EnemyType, _enemyType, EnemyType);
    //CREATE_FUNC(Enemy);
    
    
    void deathEnemy();
    float const EnemySize = 100.0f;
    
    static std::string getEnemyImageFilePath(EnemyType type);
    
    
};

#endif /* defined(__LineBattle__Enemy__) */
