//
//  Character.cpp
//  LineBattle
//
//  Created by 小澤勇太 on 2014/12/18.
//
//

#include "Character.h"


USING_NS_CC;


//  コンストラクタ
Character::Character()
: _hp(0)
, _maxHp(0)
, _attack(0)
, _element(Element::None)
, _turnCount(0)
, _remainingTurn(0)
{
}


//  インスタンス生成
Character* Character::create()
{
    Character* pRet = new Character();
    pRet->autorelease();
    
    return pRet;
}

//  攻撃ターン数取得
int Character::getTurnCount()
{
    return _turnCount;
}

//  攻撃ターン数設定
void Character::setTurnCount(int turnCount)
{
    _turnCount = turnCount;
    _remainingTurn = _turnCount;
}

//  ヒットポイント取得
float Character::getHpPercentage()
{
    return _hp * 100.f / _maxHp;
}

//  攻撃ターン（敵）取得
bool Character::isAttackTurn()
{
    //  残りターンの計算
    _remainingTurn--;
    
    if (_remainingTurn <= 0)
    {
        _remainingTurn = _turnCount;
        return true;
    }
    
    return false;
}



#define mark - 

//  ダメージ数取得
int Character::getDamage(int EnemyCount, int chainCount, Character* attacker, Character* defender)
{
    //  消した敵の数によるダメージ
    float baseDamage = chainCount / 3.0 * 100;
    
    //  属性ボーナス
    float elementBonus = getElementBounus(attacker->getElement(), defender->getElement());
    
    //  ダメージにボーナスを乗算したものを返す
    return baseDamage * elementBonus;
}

//  属性による攻撃ボーナス
float Character::getElementBounus(Element attackElement, Element defenseElement)
{
    //  攻撃属性
    switch (attackElement)
    {
        case Element::Blue:
        {
            //  防御属性
            switch (defenseElement)
            {
                case Element::Boss: return 0.3;
                default: return 1;
            }
            break;
        }
        case Element::Red:
        {
            //  防御属性
            switch (defenseElement)
            {
                case Element::Boss: return 0.5;
                default: return 1;
            }
            break;
        }
        case Element::Green:
        {
            //  防御属性
            switch (defenseElement)
            {
                case Element::Boss: return 1;
                default: return 1;
            }
            break;
        }
        case Element::Yellow:
        {
            //  防御属性
            switch (defenseElement)
            {
                case Element::Boss: return 1.2;
                default: return 1;
            }
            break;
        }
        case Element::Purple:
        {
            //  防御属性
            switch (defenseElement)
            {
                case Element::Boss: return 1.5;
                default: return 1;
            }
            break;
        }
        case Element::Boss:
        {
            //  防御属性
            switch (defenseElement)
            {
                default: return 1;
            }
            break;
        }
            default:
        {
            return  1;
        }
    }
}