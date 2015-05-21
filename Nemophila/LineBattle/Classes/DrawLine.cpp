//
//  DrawLine.cpp
//  LineBattle
//
//  Created by 小澤勇太 on 2014/12/10.
//
//

#include "DrawLine.h"

DrawLine::DrawLine(std::vector<Vec2*>* vecs)
: _node(nullptr), _vects(vecs)
{
}

DrawLine* DrawLine::create(std::vector<Vec2*>* vecs)
{
    auto node = new DrawLine(vecs);
    node->init();
    node->autorelease();
    return node;
}

bool DrawLine::init()
{
    if (!DrawNode::init())
        return false;
    
    _node = DrawNode::create();
    addChild(_node);
    
    // from,to,radius,color
    Vec2* tmpVec = nullptr;
    if (_vects != nullptr){
        for(auto* vec : *_vects){
            
            if (tmpVec != nullptr){
                _node->drawSegment(Vec2(tmpVec->x,tmpVec->y), Vec2(vec->x,vec->y), 3, Color4F::BLACK);
                
            }
            tmpVec = vec;
        }
    }
    
    return true;
    
}

void DrawLine::remove()
{
    Action* action = RemoveSelf::create();
    runAction(action);
}