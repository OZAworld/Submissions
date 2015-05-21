//
//  FirstScene.cpp
//  Text_Adv
//
//  Created by 小澤勇太 on 2014/11/19.
//
//

#include "FirstScene.h"
#include "GameSceneTitle.h"

using namespace cocos2d;
using namespace std;

USING_NS_CC;

//  タイトル画面の表示
Scene *FirstScene::createScene()
{
    Scene *scene = Scene::create();
    FirstScene *layer = FirstScene::create();
    scene -> addChild(layer);
    return scene;
}

bool FirstScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    initBackground();
    
    
    this->scheduleOnce(schedule_selector(FirstScene::gameStart), 1.7f);

    
    return true;
}



void FirstScene::initBackground()
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
    Title->setPosition(Point(origin.x + winSize.width * 0.5, origin.y + 700));
    this->addChild(Title, 2);
    
    Title->runAction(MoveTo::create(1.5f, Point(origin.x + winSize.width * 0.5, origin.y + winSize.height * 0.5 + 160)));
    Point pos = Title->getPosition();
    
    
}


void FirstScene::gameStart(float milli)
{
    auto scene = GameSceneTitle::createScene();
    
    TransitionFade* fade = TransitionFade::create(0.7f, scene, Color3B::WHITE);
    Director::getInstance()->replaceScene(fade);
}





