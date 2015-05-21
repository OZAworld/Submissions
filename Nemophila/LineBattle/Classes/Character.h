//
//  Character.h
//  LineBattle
//
//  Created by 小澤勇太 on 2014/12/18.
//
//

#ifndef __LineBattle__Character__
#define __LineBattle__Character__

#include "cocos2d.h"

class Character : public cocos2d::Ref
{
public:
    //キャラクターの属性
    enum class Element
    {
        Blue,       //  青
        Red,        //  赤
        Green,      //  緑
        Yellow,       //  黄色
        Purple,      //  紫
        Heal,       //  回復用
        Boss,       //  ボス
        Player,     //  プレイヤー
        None,
    };
    
protected:
    int _remainingTurn;                         //  攻撃するまでのターン
    CC_SYNTHESIZE(int, _hp, Hp);                //  ヒットポイント
    CC_SYNTHESIZE(int, _maxHp, MaxHp);          //  最大ヒットポイント
    CC_SYNTHESIZE(int, _attack, Attack);        //  攻撃力
    CC_SYNTHESIZE(Element, _element, Element);  //  属性
    CC_PROPERTY(int, _turnCount, TurnCount);    //  攻撃ターン（敵側）
    
public:
    Character();        //  コンストラクタ
    static Character* create();     //  インスタンス生成
    
    float getHpPercentage();        //  ヒットポイント（％値）取得
    bool isAttackTurn();            //  攻撃ターン（敵）チェック
    static int getDamage(int EnemyCount, int EnemyChain, Character* attacker, Character* defender); //  ダメージ値取得
    
protected:
    static float getElementBounus(Element attackElement, Element defenseElement);   //  属性によるダメージの補正
};



#endif /* defined(__LineBattle__Character__) */
