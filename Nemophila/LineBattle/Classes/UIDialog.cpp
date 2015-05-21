//
//  UIDialog.cpp
//  LineBattle
//
//  Created by 小澤勇太 on 2014/12/10.
//
//

#include "UIDialog.h"

UIDialog::UIDialog(Widget::ccWidgetTouchCallback& callback)
: _callback(callback), _uiLayer(nullptr)
{
}

UIDialog* UIDialog::create(Widget::ccWidgetTouchCallback& callback)
{
    auto dialog = new UIDialog(callback);
    dialog->init();
    dialog->autorelease();
    return dialog;
}

#define kModalLayerPriority -1

bool UIDialog::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    _uiLayer = Layer::create();
    addChild(_uiLayer);
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event)->bool{
        return true;
    };
    auto dip = Director::getInstance()->getEventDispatcher();
    dip->addEventListenerWithSceneGraphPriority(listener, this);
    dip->setPriority(listener, kModalLayerPriority);
    
    
    auto size = Director::getInstance()->getVisibleSize();
    ui::ScrollView* sc = ui::ScrollView::create();
    sc->setContentSize(size);
    sc->setBounceEnabled(true);
    sc->setDirection(ui::ScrollView::Direction::VERTICAL);
    sc->setContentSize(Size(1136,size.height));
    sc->setInnerContainerSize(Size(1136, sc->getContentSize().height + 300));
    
    sc->setPosition(Vec2((size.width - sc->getContentSize().width) / 2, size.height - sc->getContentSize().height));
    
    Button* button = Button::create("mob_1.png");
    button->setPosition(Vec2(568, 320));
    button->addTouchEventListener(_callback);
    sc->addChild(button);
    
    
    auto s = sc->getContentSize();
    
    Text *alert = Text::create("What's New", "fonts/Marker Felt.ttf", 30);
    alert->setColor(Color3B(159, 168, 176));
    alert->setPosition( Vec2(s.width / 2.0f, s.height/2+50) );
    addChild(alert);
    
    alert = Text::create("Tap Start", "fonts/Marker Felt.ttf", 30);
    alert->setColor(Color3B(159, 168, 176));
    alert->setPosition(Vec2(sc->getContentSize().width / 2.0f, sc->getContentSize().height / 2.0f - alert->getContentSize().height * 3.125));
    sc->addChild(alert);
    
    _uiLayer->addChild(sc);
    
    return true;
}

void UIDialog::close()
{
    Action* action = RemoveSelf::create();
    runAction(action);
}