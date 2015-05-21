//
//  GameSceneTitle.cpp
//  Text_Adv_ver2
//
//  Created by 小澤勇太 on 2014/10/16.
//
//

#include "GameSceneTitle.h"
#include "GameMain.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

USING_NS_CC;

#define WINSIZE Director::getInstance()->getWinSize()


//  タイトル画面の表示
Scene *GameSceneTitle::createScene()
{
    Scene *scene = Scene::create();
    GameSceneTitle *layer = GameSceneTitle::create();
    scene -> addChild(layer);
    return scene;
}

//  初期化
bool GameSceneTitle::init()
{
    if (! CCLayer::init())
    {
        return false;
    }
    
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
  
    initBackground();
    
    
    makeItem();         //背景・ボタンなどの設定
    
    
    return true;
}

//  背景の設定
void GameSceneTitle::initBackground()
{
    //  画面座標
    Size winSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    

    //  背景を設置
    Sprite *spBG = Sprite::create("background_t_1.png");
    spBG->setPosition(Point(origin.x + winSize.width/2,origin.y + winSize.height/2));
    //spBG->setRotation(90);
    spBG->setScale(0.34);
    this->addChild(spBG,0);
    
    //  タイトル画像
    Sprite* Title = Sprite::create("title_icon_1.png");
    Title->setPosition(Point(origin.x + winSize.width * 0.5, origin.y + winSize.height * 0.5 + 160));
    this->addChild(Title, 2);
    
    
}

//  Continueボタンの設定
void GameSceneTitle::makeItem()
{
    
    //  コンティニューボタンの作成
    auto continueButton = MenuItemImage::create("title-window_1.png",
                                                "title_window_2.png",
                                                CC_CALLBACK_1(GameSceneTitle::changeMode_continue,this));
    
    continueButton->setPosition(Point(WINSIZE.width / 1.15, WINSIZE.height / 3.8));
    
                             
    auto g_continue = Menu::create(continueButton,NULL);
    g_continue->setPosition(Point::ZERO);
    this->addChild(g_continue,1);
    
    //  Continueアイコン設置
    Sprite* Continue = Sprite::create("title_icon_3.png");
    Continue->setPosition(Point(WINSIZE.width / 1.16, WINSIZE.height / 3.7));
    this->addChild(Continue, 2);
}


void GameSceneTitle::changeMode_continue(Ref *pSender)
{
    Scene *pScene = GameMain::createScene();
    
    TransitionFade* transition = TransitionFade::create(0.5f,pScene);
    
    Director::getInstance()->replaceScene(transition);
}

