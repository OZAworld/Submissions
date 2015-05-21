//
//  GameMain.cpp
//  LineBattle
//
//  Created by 小澤勇太 on 2014/12/10.
//
//

#include "GameMain.h"
#include "GameSceneTitle.h"
#include "SimpleAudioEngine.h"
#include "DrawLine.h"
#include "Enemy.h"
#include "UIDialog.h"
#include <random>


using namespace cocos2d;
using namespace std;

USING_NS_CC;
#define WINSIZE Director::getInstance()->getWinSize()
#define TAG_LEVEL_LAYER 100
#define MAX_ENEMY 30

//  メイン部分

//  コンストラクタ
GameMain::GameMain()
: state(nullptr)
, _chainNumber(0)
, _level(0)
, _nextLevel(0)
{
    //  乱数の重みを設定する
    std::random_device device;
    _engine = std::default_random_engine(device());
    _distForEnemy = std::discrete_distribution<int>{40, 20, 18, 14, 10, 10};
    _distForMenber = std::uniform_int_distribution<int>{0,5};
}

//  ゲームのシーンを作成
Scene *GameMain::createScene(int level)
{
    auto *scene = Scene::createWithPhysics();
    
    scene->getPhysicsWorld()->setGravity(Vec2(0,-98.0));
    scene->getPhysicsWorld()->setSpeed(4.0f);
    
    GameMain *layer = GameMain::create(level);
    scene -> addChild(layer);
    
    
    return scene;
}

GameMain* GameMain::create(int level)
{
    GameMain* pRet = new GameMain();
    pRet->init(level);
    pRet->autorelease();
    
    return pRet;
}

//  初期化
bool GameMain::init(int level)
{
    if (! CCLayer::init())
    {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic("incandescence.caf");
    audio->playBackgroundMusic("incandescence.caf", true);
    audio->setBackgroundMusicVolume(0.3f);
    
    
    //  壁のポイントを画面に設置　右上、左上、左下、真ん中下、右下、右上
    Vec2 vec[6] =
    {
        Vec2(winSize.width - 1, winSize.height - 100),
        Vec2(1, winSize.height - 100),
        Vec2(1, 100),
        Vec2(winSize.width / 2, 0),
        Vec2(winSize.width - 1, 100),
        Vec2(winSize.width - 1, winSize.height - 100),
    };
    
    auto wall = Node::create();
    
    //  密度、反発、摩擦
    wall->setPhysicsBody(PhysicsBody::createEdgeChain(vec, 6, PhysicsMaterial(0.1f, 0.0f, 0.5f)));
    
    wall->setPosition(0,0);
    addChild(wall);
    
    _level = level;             //  レベルの保持
    
    initBackground();           //  背景の表示
    initTouchEvent();           //  タッチイベントの初期化
    initBoss();                 //  ボスの表示とステータスの初期化
    initMember();               //  プレイヤーのHpバーの表示とステータスの初期化
    initLevelLayer();           //  レベル表示レイヤーの表示
    
    scheduleUpdate();
    
    Button* button = Button::create("mob_1.png");
    button->setPosition(Vec2(winSize.width, winSize.height - 50));
    button->addTouchEventListener(CC_CALLBACK_2(GameMain::touchEvent, this));
    addChild(button);
    
    _enemyVicts = new std::vector<Vec2*>();
    _fingerPosition = nullptr;
    
    return true;
}

//  背景を設定
void GameMain::initBackground()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    //  背景を設置
    Sprite *spBG = Sprite::create(StringUtils::format("back%d.png",_level));
    spBG->setPosition(Point(origin.x + winSize.width/2,origin.y + winSize.height/2));
    this->addChild(spBG,0);
}

//  タッチイベントの処理
void GameMain::touchEvent(Ref* pSender, Widget::TouchEventType type)
{
    Widget::ccWidgetTouchCallback callback = CC_CALLBACK_0(GameMain::dialogClose, this);
    _dialog = UIDialog::create(callback);
    addChild(_dialog,Z_Dialog,T_Dialog);
}

void GameMain::dialogClose()
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

void GameMain::showEnemy()
{
    auto winSize = Director::getInstance()->getWinSize();
    //  ランダムで敵のカラーを取得。
    int enemyType = _distForEnemy(_engine);
    auto enemy = Enemy::create((Enemy::EnemyType)enemyType, true);
    
    //  デフォルトカラーの敵を出す。
    enemy->setPosition(winSize.width / 2, winSize.height - enemy->EnemySize - 60);
    enemy->setScale(0.5f);
    
    
    PhysicsBody* pBall = enemy->getPhysicsBody();
    pBall->setTag(T_Enemy);
    
    addChild(enemy, Z_Enemy, enemyType + 4);        //  +4の意味は特になし。ただし+値をつけておかないと特定の色が出ないことがある。
    _enemy++;
}

void GameMain::initTouchEvent()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameMain::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameMain::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameMain::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
}

//  エネミーの全状態を取得
Map<int, Enemy*> GameMain::getAllEnemys()
{
    auto enemys = Map<int, Enemy*>();
    
    for (auto object : getChildren())
    {
        auto enemy = dynamic_cast<Enemy*>(object);
        if (enemy)
        {
            enemys.insert(enemy->getTag(), enemy);
        }
    }
    
    return enemys;
}




void GameMain::update(float dt)
{
    _time += dt;
    
    //  エネミーを表示
    if (MAX_ENEMY > _enemy)
    {
        showEnemy();
    }
    
    if (_enemy > MAX_ENEMY || _enemy <= -1)
    {
        //  多すぎたら一度０にする。
        _enemy = 0;
    }
    
    for (auto* enemy : _enemys)
    {
        _enemyVicts->push_back(new Vec2(enemy->getPosition()));
    }
    if (_fingerPosition != nullptr)
    {
        _enemyVicts->push_back(_fingerPosition);
    }
    
    DrawLineRemove();
    
    
    DrawLine* node = DrawLine::create(_enemyVicts);
    addChild(node, Z_Line, T_Line);
    _enemyVicts->clear();
}

#define Amark - タップイベント
bool GameMain::onTouchBegan(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    auto arr = this->getScene()->getPhysicsWorld()->getShapes(location);
    
    for (auto& obj : arr)
    {
        if((obj->getBody()->getTag() & T_Enemy) != 0)
        {
            _tag = static_cast<Enemy*>(obj->getBody()->getNode())->getTag();
            break;
        }
    }
    return true;
}


void GameMain::onTouchMoved(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    auto arr = this->getScene()->getPhysicsWorld()->getShapes(location);
    
    
    
    Enemy* enemy = nullptr;
    for (auto& obj : arr)
    {
        if((obj->getBody()->getTag() & T_Enemy) != 0)
        {
            enemy = static_cast<Enemy*>(obj->getBody()->getNode());
            if(enemy->getTag() == _tag)
            {
                break;
            }   else{
                enemy = nullptr;
            }
            
        }
    }
    
    if (enemy != nullptr && enemy->getState() == Enemy::State::Moving)
    {
        if (_enemys.empty())
        {
            _enemys.pushBack(enemy);
        }   else if (!_enemys.contains(enemy))
        {
            float distance = _enemys.back()->getPosition().distance(enemy->getPosition());
            
            if (distance < enemy->EnemySize * 2.0f)
            {
                _enemys.pushBack(enemy);
            }
        }
    }
    
    if (_enemys.size() < 1)
    {
        _fingerPosition = new Vec2(location);
    }   else{
        _fingerPosition = nullptr;
    }
    
}

void GameMain::onTouchEnded(Touch* touch, Event* event)
{
    auto allEnemys = getAllEnemys();
    double element_b = 0;          //  消した敵のボーナスダメージ
    double number_b = 0;           //  消した数のボーナスダメージ
    
    //  敵を２体以上つないだときの処理
    if(!_enemys.empty() && _enemys.size() > 1)
    {
        int damage = 0;
        int Heal = 0;
        std::set<int> attackers;
        switch (_tag)
        {
            case 4:
            {
                //  青色の敵を消すと
                element_b = 0.5;
                if (_enemys.size() >= 14) number_b = 400;
                break;
            }
            case 5:
            {
                //  赤色の敵を消すと
                element_b = 0.8;
                if (_enemys.size() >= 12) number_b = 200;
                break;
            }
            case 6:
            {
                //  緑色の敵を倒すと
                element_b = 1;
                if (_enemys.size() >= 10) number_b = 200;
                break;
            }
            case 7:
            {
                //  黄色の敵を倒すと
                element_b = 2;
                if (_enemys.size() >= 8) number_b = 300;
                break;
            }
            case 8:
            {
                //  紫色の敵を倒すと
                element_b = 4;
                if (_enemys.size() >= 8) number_b = 500;
                break;
            }
            case 9:
            {
                //  回復敵を消すと
                element_b = 3;
                break;
            }
        }
        
        //  ダメージ計算
        if (_tag == 9)  //  回復処理
        {
            Heal = _enemys.size() * element_b * 50;
        }
        else   damage = _enemys.size() / 5.0 * element_b * _enemys.size() * 10 + number_b;     //  攻撃処理
        
        
        //  ボスの残りHp
        int afterHp = _bossData->getHp() - damage;
        
        if (damage > 0)
        {
            attackToBoss(damage, attackers);
        }
        
        if (Heal > 0)
        {
            Healing(Heal);
        }
        
        if (afterHp > 0)
        {
            CallFunc* func = CallFunc::create(CC_CALLBACK_0(GameMain::attackFromEnemy, this));
            runAction(Sequence::create(DelayTime::create(0.5), func, nullptr));
        }
        
        CallFunc* func;
        if (afterHp <= 0)
        {
            if (_level >= 7)
            {
                //CallFunc* func;
                func = CallFunc::create(CC_CALLBACK_0(GameMain::clearAnimation, this));
                runAction(Sequence::create(DelayTime::create(0.5), func, nullptr));
            }else
            {
                func = CallFunc::create(CC_CALLBACK_0(GameMain::winAnimation, this));
                runAction(Sequence::create(DelayTime::create(0.5), func, nullptr));
            }
        }
        
        for (auto* enemy : _enemys)
        {
            if (enemy->getState() == Enemy::State::Moving)
            {
                if (_tag == 9)
                {
                    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
                    audio->playEffect("playerHealSE.caf");
                    audio->setEffectsVolume(0.1f);
                }else
                {
                    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
                    audio->playEffect("playerAttackSE.caf");
                    audio->setEffectsVolume(0.1f);
                }
                            
                enemy->deathEnemy();
                
                _enemy--;
            }
        }
        
        
    }
    _enemys.clear();
}



#define Bmark -ここからはタッチイベント以外の処理

void GameMain::DrawLineRemove()
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



void GameMain::initBoss()
{
    int turnCount;
    
    switch (_level)
    {
        case 1:
        {
            turnCount = 5;
            break;
        }
            
        case 2:
        {
            turnCount = 4;
            break;
        }
            
        case 3:
        {
            turnCount = 5;
            break;
        }
            
        case 4:
        {
            turnCount = 5;
            break;
        }
            
        case 5:
        {
            turnCount = 3;
            break;
        }
            
        case 6:
        {
            turnCount = 4;
            break;
        }
            
        case 7:
        {
            turnCount = 3;
            break;
        }
    }
    
    //  敵の情報
    _bossData = Character::create();
    _bossData->retain();
    _bossData->setMaxHp(1000 * _level * 0.3 + 300);
    _bossData->setHp(1000 * _level * 0.3 + 300);
    _bossData->setElement(Character::Element::Boss);
    _bossData->setTurnCount(turnCount);
    
    //  敵の表示
    _boss = Sprite::create(StringUtils::format("boss_%d.png",_level));
    _boss->setScale(1.3f);
    _boss->setPosition(Point(WINSIZE.width / 2, 500));
    addChild(_boss, Z_BOSS);
    
    //  敵のヒットポイントバー
    auto hpBg = Sprite::create("HpEnemyBackground.png");
    hpBg->setPosition(Point(WINSIZE.width / 2, 360));
    addChild(hpBg, Z_HpBar);
    
    //  敵のヒットポイントの表示
    _hpBarForEnemy = ProgressTimer::create(Sprite::create("HpEnemyRed.png"));
    _hpBarForEnemy->setPosition(Point(hpBg->getContentSize().width / 2, hpBg->getContentSize().height / 2));
    _hpBarForEnemy->setType(ProgressTimer::Type::BAR);
    _hpBarForEnemy->setMidpoint(Point::ZERO);
    _hpBarForEnemy->setBarChangeRate(Point(1, 0));
    _hpBarForEnemy->setPercentage(_bossData->getHpPercentage());
    hpBg->addChild(_hpBarForEnemy);
}

void GameMain::initMember()
{
    _memberData = Character::create();
    _memberData->retain();
    _memberData->setMaxHp(1000);
    _memberData->setHp(1000);
    _memberData->setElement(Character::Element::Player);
    
    //  メンバーのHpバーの枠を表示
    auto hpBg = Sprite::create("HpCardBackground.png");
    hpBg->setPosition(Point(WINSIZE.width / 1.13, WINSIZE.height / 1.1));
    addChild(hpBg, Z_CharHp);
    
    //  メンバーのHpバーを表示
    _hpBarForMember = ProgressTimer::create(Sprite::create("HpCardGreen.png"));
    _hpBarForMember->setPosition(Point(hpBg->getContentSize().width / 2, hpBg->getContentSize().height / 2));
    _hpBarForMember->setType(ProgressTimer::Type::BAR);
    _hpBarForMember->setMidpoint(Point::ZERO);
    _hpBarForMember->setBarChangeRate(Point(1, 0));
    _hpBarForMember->setPercentage(_memberData->getHpPercentage());
    hpBg->addChild(_hpBarForMember);
}

void GameMain::calculateDamage(int &chainNum, int &damage, std::set<int> &attackers)
{
    /*
     auto removeIt = _removedNumbers.begin();
     while (removeIt != _removedNumbers.end())
     {
     auto enemyIt = (*removeIt).begin();
     while (enemyIt != (*removeIt).end())
     {
     CCLOG("開始");
     for (int i = 0; i < _memberDatum.size(); i++)
     {
     auto memberData = _memberDatum.at(i);
     
     if (memberData->getHp() <= 0)
     {
     continue;
     }
     
     if(isAttacker((*enemyIt).first,memberData->getElement()))
     {
     //  アタッカー情報の保持
     attackers.insert(i);
     
     //  ダメージ
     damage += Character::getDamage((*enemyIt).second, chainNum, memberData, _bossData);
     }
     }
     
     chainNum++;
     enemyIt++;
     }
     removeIt++;
     }
     */
}

bool GameMain::isAttacker(Enemy::EnemyType type, Character::Element element)
{
    switch (type)
    {
        case Enemy::EnemyType::Red:
            //  赤の敵：赤
            if (element == Character::Element::Red)
            {
                return true;
            }
            break;
            
        case Enemy::EnemyType::Blue:
            //  赤の敵：青
            if (element == Character::Element::Blue)
            {
                return true;
            }
            break;
            
        case Enemy::EnemyType::Green:
            //  赤の敵：緑
            if (element == Character::Element::Green)
            {
                return true;
            }
            break;
            
        case Enemy::EnemyType::Yellow:
            //  赤の敵：黄
            if (element == Character::Element::Yellow)
            {
                return true;
            }
            break;
            
        case Enemy::EnemyType::Purple:
            //  赤の敵：紫
            if (element == Character::Element::Purple)
            {
                return true;
            }
            break;
            
        default:
            break;
    }
    return false;
}

void GameMain::attackToBoss(int damage, std::set<int> attackers)
{
    //  敵のHPを取得する
    float preHpPercentage = _bossData->getHpPercentage();
    
    //  ダメージをセットする
    int afterHp = _bossData->getHp() - damage;
    if (afterHp < 0) afterHp = 0;
    _bossData->setHp(afterHp);
    
    //  敵ヒットポイントバーのアニメーション
    auto act = ProgressFromTo::create(0.5, preHpPercentage, _bossData->getHpPercentage());
    _hpBarForEnemy->runAction(act);
    
    //  敵の被ダメージアニメーション
    _boss->runAction(vibratingAnimation(afterHp));
    
}

void GameMain::Healing(int Heal)
{
    //  プレイヤーのHPを取得する
    float preHpPercentage = _memberData->getHpPercentage();
    
    //  ダメージをセットする
    int afterHp = _memberData->getHp() + Heal;
    if (afterHp > _memberData->getMaxHp()) afterHp = _memberData->getMaxHp();
    _memberData->setHp(afterHp);
    auto whiteLayer = LayerColor::create(Color4B(255,255,255,50),WINSIZE.width, WINSIZE.height);
    whiteLayer->setPosition(Point::ZERO);
    addChild(whiteLayer, Z_damage);
    auto firstAction = FadeIn::create(0.1f);        //  フェードインのアクション
    auto secoundAction = FadeOut::create(0.1f);     //  フェードアウトのアクション
    Sequence* sequence = Sequence::create(firstAction, secoundAction, NULL);
    
    whiteLayer->runAction(sequence);
    
    //  プレイヤーのヒットポイントバーのアニメーション
    auto act = ProgressFromTo::create(0.5, preHpPercentage, _memberData->getHpPercentage());
    _hpBarForMember->runAction(act);

}

void GameMain::attackFromEnemy()
{
    if(!_bossData->isAttackTurn())
    {
        return;
    }
    
    int e_damage = 50 * _level;
    
    
    //  メンバーにダメージを与える
    float preHpPercentage = _memberData->getHpPercentage();
    int afterHp = _memberData->getHp() - e_damage;
    if (afterHp < 0) afterHp = 0;
    _memberData->setHp(afterHp);
    
    //  敵の攻撃アニメーション
    auto seq = Sequence::create(MoveBy::create(0.1, Point(0, -20)),
                                MoveBy::create(0.1, Point(0, 20)),
                                nullptr);
    _boss->runAction(seq);

    auto redLayer = LayerColor::create(Color4B(255,10,30,127),WINSIZE.width, WINSIZE.height);
    redLayer->setPosition(Point::ZERO);
    addChild(redLayer, Z_damage);
    
    auto sePlay = CocosDenshion::SimpleAudioEngine::getInstance();
    sePlay->playEffect("enemyAttackSE.caf");
    sePlay->setEffectsVolume(20.0f);
    
    auto firstAction = FadeIn::create(0.2f);        //  フェードインのアクション
    auto secoundAction = FadeOut::create(0.2f);     //  フェードアウトのアクション
    Sequence* sequence = Sequence::create(firstAction, secoundAction, NULL);

    redLayer->runAction(sequence);
    
    //  メンバーのHpバーのアニメーション
    auto act = ProgressFromTo::create(0.5, preHpPercentage, _memberData->getHpPercentage());
    _hpBarForMember->runAction(act);
    
    
    CallFunc* func;
    if (afterHp <= 0)
    {
        func = CallFunc::create(CC_CALLBACK_0(GameMain::loseAnimation, this));
        runAction(Sequence::create(DelayTime::create(0.5), func, nullptr));
    }
}

Spawn* GameMain::vibratingAnimation(int afterHp)
{
    auto move = Sequence::create(MoveBy::create(0.05, Point(10, 10)),
                                 MoveBy::create(0.05, Point(-10, -10)),
                                 MoveBy::create(0.05, Point(-10, -10)),
                                 MoveBy::create(0.05, Point(10, 10)),
                                 MoveBy::create(0.05, Point(10, -10)),
                                 MoveBy::create(0.05, Point(-10, 10)),
                                 MoveBy::create(0.05, Point(-10, 10)),
                                 MoveBy::create(0.05, Point(10, -10)),
                                 nullptr);
    
    Action* tint;
    if(afterHp > 0)
    {
        tint = Sequence::create(TintTo::create(0, 255, 0, 0),
                                DelayTime::create(0.2),
                                TintTo::create(0, 255, 255, 255),
                                nullptr);
    }else
    {
        tint = TintTo::create(0, 255, 0, 0);
    }
    
    return Spawn::create(move, tint, nullptr);
}

void GameMain::initLevelLayer()
{
    auto levelLayer = LayerColor::create(Color4B(0,0,0,191),WINSIZE.width, WINSIZE.height);
    levelLayer->setPosition(Point::ZERO);
    levelLayer->setTag(TAG_LEVEL_LAYER);
    addChild(levelLayer, Z_level);
    
    //  レベルの表示
    auto levelSprite = Sprite::create("LEVEL.png");
    levelSprite->setPosition(Point(WINSIZE.width * 0.45, WINSIZE.height * 0.5));
    levelLayer->addChild(levelSprite);
    
    //  レベル数の表示
    auto levelNumPath = StringUtils::format("%d.png", _level);
    auto levelNumSprite = Sprite::create(levelNumPath.c_str());
    levelNumSprite->setPosition(Point(WINSIZE.width * 0.75, WINSIZE.height * 0.5));
    levelLayer->addChild(levelNumSprite);
    
    //  1.5秒後に消えるようにする
    scheduleOnce(schedule_selector(GameMain::removeLevelLayer), 1);
}

void GameMain::removeLevelLayer(float dt)
{
    
    //0.5秒で消えるようにする
    auto levelLayer = getChildByTag(TAG_LEVEL_LAYER);
    levelLayer->runAction(Sequence::create(FadeTo::create(0.5, 0),
                                           RemoveSelf::create(),
                                           nullptr));
}

void GameMain::winAnimation()
{
    auto whiteLayer = LayerColor::create(Color4B(255,255,255,127),WINSIZE.width, WINSIZE.height);
    whiteLayer->setPosition(Point::ZERO);
    addChild(whiteLayer, Z_Result);
    
    //  Win画像を表示する
    auto win = Sprite::create("Win.png");
    win->setPosition(Point(WINSIZE.width / 2, WINSIZE.height / 2));
    win->setScale(1.5f);
    addChild(win, Z_Result);
    
    //  次のレベルの設定
    if (_level >= 7)
    {
        _level = 1;
    }else{
        _nextLevel = _level + 1;
    }
    
    //  指定秒後に次のシーンへ
    scheduleOnce(schedule_selector(GameMain::nextScene), 3);
}

void GameMain::loseAnimation()
{
    auto whiteLayer = LayerColor::create(Color4B(255,255,255,127),WINSIZE.width, WINSIZE.height);
    whiteLayer->setPosition(Point::ZERO);
    addChild(whiteLayer, Z_Result);
    
    //  Win画像を表示する
    auto win = Sprite::create("Lose.png");
    win->setPosition(Point(WINSIZE.width / 2, WINSIZE.height / 2));
    win->setScale(1.5f);
    addChild(win, Z_Result);
    
    //  指定秒後に次のシーンへ
    scheduleOnce(schedule_selector(GameMain::changeScene), 3);

}

void GameMain::clearAnimation()
{
    auto whiteLayer = LayerColor::create(Color4B(0,0,0,255),WINSIZE.width, WINSIZE.height);
    whiteLayer->setPosition(Point::ZERO);
    addChild(whiteLayer, Z_Result);
    
    //  Clear画像を表示する
    auto win = Sprite::create("Clear.png");
    win->setPosition(Point(WINSIZE.width / 2, WINSIZE.height / 2));
    win->setScale(1.5f);
    addChild(win, Z_Result);
    //  指定秒後に次のシーンへ
    scheduleOnce(schedule_selector(GameMain::changeScene), 3);
}

void GameMain::nextScene(float dt)
{
    auto scene = GameMain::createScene(_nextLevel);
    Director::getInstance()->replaceScene(scene);
}

void GameMain::changeScene(float dt)
{
    auto scene = GameSceneTitle::createScene();
    Director::getInstance()->replaceScene(scene);
}
