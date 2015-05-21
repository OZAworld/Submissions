//
//  GameSceneTitle.h
//  Text_Adv
//
//  Created by 小澤勇太 on 2014/10/16.
//
//

#ifndef __Text_Adv__GameSceneTitle__
#define __Text_Adv__GameSceneTitle__



#include "cocos2d.h"

class GameSceneTitle : public cocos2d::Layer
{
private:
    void makeItem();
    void initBackground();
    
public:
    static cocos2d::Scene *createScene();
    
    //  初期化のメソッド
    virtual bool init();
    
    
    CREATE_FUNC(GameSceneTitle);
    
    void changeMode_continue(cocos2d::Ref *pSender);
};


#endif /* defined(__Text_Adv__GameSceneTitle__) */
