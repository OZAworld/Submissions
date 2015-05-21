//
//  UIDialog.h
//  LineBattle
//
//  Created by 小澤勇太 on 2014/12/10.
//
//

#ifndef __LineBattle__UIDialog__
#define __LineBattle__UIDialog__

#include "cocos2d.h"

#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class UIDialog : public Layer
{
protected:
    Layer* _uiLayer;
    Widget::ccWidgetTouchCallback& _callback;
    
public:
    UIDialog(Widget::ccWidgetTouchCallback& _callback);
    static UIDialog* create(Widget::ccWidgetTouchCallback& callback);
    virtual bool init();
    void close();
};

#endif /* defined(__LineBattle__UIDialog__) */
