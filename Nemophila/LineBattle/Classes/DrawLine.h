//
//  DrawLine.h
//  LineBattle
//
//  Created by 小澤勇太 on 2014/12/10.
//
//

#ifndef __LineBattle__DrawLine__
#define __LineBattle__DrawLine__

#include "cocos2d.h"

USING_NS_CC;

class DrawLine : public DrawNode
{
protected:
    DrawNode* _node;
    std::vector<Vec2*> * _vects;
    
public:
    DrawLine(std::vector<Vec2*>*);
    static DrawLine* create(std::vector<Vec2*>*);
    virtual bool init();
    void remove();
};

#endif /* defined(__LineBattle__DrawLine__) */
