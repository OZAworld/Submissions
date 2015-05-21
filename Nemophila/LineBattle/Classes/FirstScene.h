//
//  FirstScene.h
//  Text_Adv
//
//  Created by 小澤勇太 on 2014/11/19.
//
//

#ifndef __Text_Adv__FirstScene__
#define __Text_Adv__FirstScene__

#include "cocos2d.h"

class FirstScene : public cocos2d::Layer
{
private:
    //void makeItem();
    void initBackground();
    
public:
    static cocos2d::Scene *createScene();
    
    //  初期化のメソッド
    virtual bool init();
    
    
    CREATE_FUNC(FirstScene);
    
    void gameStart(float milli);
    //void changeMode_newgame(cocos2d::Object *pSender);       //　スタートボタン押下時の処理宣言
    //void changeMode_continue(cocos2d::Object *pSender);
};



#endif /* defined(__Text_Adv__FirstScene__) */
