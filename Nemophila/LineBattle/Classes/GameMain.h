//
//  GameMain.h
//  LineBattle
//
//  Created by 小澤勇太 on 2014/12/10.
//
//

#ifndef __LineBattle__GameMain__
#define __LineBattle__GameMain__

#include "cocos2d.h"

#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "UIDialog.h"
#include "DrawLine.h"
#include "Enemy.h"
#include "Character.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;

class GameMain : public cocos2d::Layer
{
protected:
    enum ZOrder
    {
        Z_Bg = 0,
        Z_Enemy,
        Z_Line,
        Z_Dialog,
        Z_CharHp,
        Z_BOSS,
        Z_HpBar,
        Z_damage,
        Z_level,
        Z_Result,
    }; 
    
    enum Tag
    {
        T_Enemy = 1,
        T_Dialog,
        T_Line,
    };
    
    
    float _time;
    int _enemy;
    int _tag;
    UIDialog* _dialog;
    
    void initTouchEvent();
    void showEnemy();
    
    cocos2d::Color3B _tagColor[5]
    {
        cocos2d::Color3B(0, 255,255),
        cocos2d::Color3B(0, 0, 255),
        cocos2d::Color3B(0, 0, 0),
        cocos2d::Color3B(255, 80, 120),
        cocos2d::Color3B(255, 255, 255)
    };
    
    
    std::default_random_engine _engine;                     //  乱数生成エンジン
    std::discrete_distribution<int> _distForEnemy;          //  乱数の分布
    std::uniform_int_distribution<int> _distForMenber;      //  乱数の範囲
    
    
    
    cocos2d::Vector<Enemy*> _enemys;
    std::vector<Vec2*> * _enemyVicts;
    Vec2* _fingerPosition;
    
    int _level;             //  現在のレベル
    int _nextLevel;         //  次のレベル
    
    void initBoss();                                            //  敵の表示
    void initMember();                                          //  メンバーの初期情報
    
    void initLevelLayer();                  //  レベル表示レイヤーの表示
    void removeLevelLayer(float dt);        //  レベル表示レイヤーの削除
    void winAnimation();                    //  Winアニメーション
    void loseAnimation();                   //  Loseアニメーション
    void clearAnimation();                  //  Clearアニメーション
    void nextScene(float dt);               //  次のシーンへ
    void changeScene(float dt);             //  タイトル画面へ移動
    
    void DrawLineRemove();                  //  描いた線を消去
    
private:
    void makeItem();
    void makeStreak();
    bool deleteFlag;
    
    void initBackground();
    
    
    cocos2d::Point m_Pos;
    
    void collisionDetection();
    
    
    int m_iCount;
    
    
public:
    
    
    //  初期化のメソッド
    GameMain();                                             //  コンストラクタ
    virtual bool init(int level);
    static GameMain* create(int level);
    static cocos2d::Scene *createScene(int level = 1);
    
    void setDeleteFlag(bool flag);
    bool getDeleteFlag();
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void update(float dt);
    
    void touchEvent(Ref* pSender, Widget::TouchEventType type);
    void dialogClose();
    
    
protected:
    
    
    bool isAttacker(Enemy::EnemyType type, Character::Element element);
    void attackToBoss(int damage, std::set<int> attackers);
    void Healing(int Heal);
    void attackFromEnemy();
    void endAnimation();
    
    cocos2d::Map<int, Enemy*> getAllEnemys();   //　全てのエネミータイプを取得
    
    void calculateDamage(int &chainNum, int &damage, std::set<int> &attackers);       //  ダメージの計算
    
    Enemy* state;
    int _chainNumber;                                               //  連鎖数のカウント
    std::vector<std::map<Enemy::EnemyType, int>> _removedNumbers;    //  エネミーのカウント
    
    
    Character* _bossData;                                           //  敵の情報
    Character* _memberData;
    cocos2d::Sprite* _boss;                                         //  敵の画像
    cocos2d::ProgressTimer* _hpBarForEnemy;                         //  敵のヒットポイントバー
    cocos2d::ProgressTimer* _hpBarForMember;
    
    cocos2d::Vector<Character*> _memberDatum;                       //  メンバーの情報
    cocos2d::Vector<cocos2d::Sprite*> _members;                     //  メンバー画像
    cocos2d::Spawn* vibratingAnimation(int afterHp);                //  振動アニメーション

};

#endif /* defined(__LineBattle__GameMain__) */
