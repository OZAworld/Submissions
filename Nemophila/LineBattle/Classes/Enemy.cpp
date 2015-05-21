//
//  Enemy.cpp
//  LineBattle
//
//  Created by 小澤勇太 on 2014/12/10.
//
//

#include "Enemy.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;



Enemy::Enemy()
: _state(State::Moving)
{
}

Enemy* Enemy::create(EnemyType type, bool visible)
{
    
    auto node = new Enemy();
    node->init(type, visible);
    node->autorelease();
    
    return node;
     
    
    Enemy* pRet = new Enemy();
    if (pRet && pRet->init(type, visible))
    {
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
    
}


bool Enemy::init(EnemyType type, bool visible)
{
    if (!Sprite::initWithFile(getEnemyImageFilePath(type)))
    {
        return false;
    }
    
    
    auto pEnemy = PhysicsBody::createCircle(EnemySize, PhysicsMaterial(1.0f,0.6f,0.3f));
    pEnemy->setDynamic(true);
    pEnemy->setRotationEnable(true);
    pEnemy->setMoment(PHYSICS_INFINITY);
    pEnemy->setMass(1.0f);
    this->setPhysicsBody(pEnemy);
    
    _enemyType = type;
    
    setVisible(visible);
    
    return true;
}

void Enemy::deathEnemy()
{
    stopAllActions();
    
    
    Action* action = RemoveSelf::create();
    runAction(action);
    
    _state = State::Death;
}

std::string Enemy::getEnemyImageFilePath(EnemyType type)
{
    switch (type)
    {
        case EnemyType::Blue:
            return "mob_blue.png";
            
        case EnemyType::Red:
            return "mob_red.png";

        case EnemyType::Green:
            return "mob_green.png";

        case EnemyType::Yellow:
            return "mob_yellow.png";

        case EnemyType::Purple:
            return "mob_purple.png";

        case EnemyType::Heal:
            return "mob_2.png";
    }
}

