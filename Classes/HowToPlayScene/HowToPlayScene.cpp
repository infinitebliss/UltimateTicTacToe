//
//  HowToPlayScene.cpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-08-01.
//
//

#include "HowToPlayScene.hpp"

#include "TitleScene.hpp"

#include "ui/CocosGUI.h"

USING_NS_CC;

static const int NUM_OF_RULES = 2;

HowToPlayScene::HowToPlayScene()
{
    
}

HowToPlayScene::~HowToPlayScene()
{
    
}

Scene* HowToPlayScene::createScene()
{
    Scene* scene = Scene::create();
    HowToPlayScene* layer = HowToPlayScene::create();
    scene->addChild(layer);
    return scene;
}

bool HowToPlayScene::init()
{
    if(!Layer::init()) return false;
    
    // get window size
    Size winSize = Director::getInstance()->getWinSize();
    
    // place background
    Sprite* background = Sprite::create("bg_white.png");
    background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(background);
    
    // place ad banner
    Sprite* ad = Sprite::create("ad.png");
    ad->setPosition(Vec2(winSize.width / 2.0, ad->getContentSize().height / 2.0));
    this->addChild(ad);
    
    // how to play
    Sprite* howtoplay = Sprite::create("howtoplay_title.png");
    howtoplay->setPosition(Vec2(winSize.width / 2.0, winSize.height - 200));
    this->addChild(howtoplay);
    
    // place menu button
    cocos2d::ui::Button* menu = cocos2d::ui::Button::create("menu.png", "menu_pressed.png");
    menu->setPosition(Vec2(menu->getContentSize().width / 2.0 + 50, winSize.height - menu->getContentSize().height / 2.0 - 50));
    menu->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                CCLOG("menu");
                // start game
                Scene* scene = TitleScene::createScene();
                TransitionSlideInT* transition = TransitionSlideInT::create(1.0, scene);
                Director::getInstance()->replaceScene(transition);
                break;
            }
            default:
                break;
        }
    });
    this->addChild(menu);
    
    for(int i = 0; i < NUM_OF_RULES; i++){
        Rule* rule = Rule::create(i + 1);
        rule->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
        rule->setVisible(false);
        _ruleVector.push_back(rule);
        this->addChild(rule);
    }
    
    _currentRuleVectorPosition = 0;
    _currentRule = _ruleVector[_currentRuleVectorPosition];
    _currentRule->setVisible(true);
    
    Sprite* selector = Sprite::create("selector.png");
    selector->setPosition(Vec2(winSize.width / 2.0, 200));
    this->addChild(selector);
    
    // touch event listener settings
    auto listener = EventListenerTouchOneByOne::create();
    // touch began
    listener->onTouchBegan = [this] (Touch *touch, Event *event)
    {
        _touchBegan = touch->getLocation();
        this->onTouchBegan();
        return true;
    };
    // touch moved
    listener->onTouchMoved = [this] (Touch *touch, Event *event)
    {
        _touchNow = touch->getLocation();
        this->onTouchMoved();
    };
    // touch ended
    listener->onTouchEnded = [this] (Touch *touch, Event *event)
    {
        _touchEnded = touch->getLocation();
        this->onTouchEnded();
        
    };
    // touch cancelled
    listener->onTouchCancelled = [this] (Touch *touch, Event *event)
    {
        CCLOG("on touch cancelled");
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void HowToPlayScene::onTouchBegan()
{
    Size winSize = Director::getInstance()->getWinSize();
    _currentRule = _ruleVector[_currentRuleVectorPosition];
    if(_currentRuleVectorPosition < NUM_OF_RULES - 1){
        _nextRule = _ruleVector[_currentRuleVectorPosition + 1];
        _nextRule->setPosition(Vec2(winSize.width + winSize.width / 2.0, winSize.height / 2.0));
        _nextRule->setVisible(true);
    }
    if(0 < _currentRuleVectorPosition)
    {
        _prevRule = _ruleVector[_currentRuleVectorPosition - 1];
        _prevRule->setPosition(Vec2(-winSize.width / 2.0, winSize.height / 2.0));
        _prevRule->setVisible(true);
    }
}
void HowToPlayScene::onTouchMoved()
{
    Size winSize = Director::getInstance()->getWinSize();
    _deltax = _touchNow.x - _touchBegan.x;
    if(_deltax < 0) // swipe left
    {
        _currentRule->setPosition(Vec2(winSize.width / 2.0 + _deltax, winSize.height / 2.0));
        if(_currentRuleVectorPosition < NUM_OF_RULES - 1){
            _nextRule->setPosition(Vec2(winSize.width + winSize.width / 2.0 + _deltax, winSize.height / 2.0));
        }
    }
    else if(0 < _deltax)
    {
        _currentRule->setPosition(Vec2(winSize.width / 2.0 + _deltax, winSize.height / 2.0));
        if(0 < _currentRuleVectorPosition){
            _prevRule->setPosition(Vec2(-winSize.width / 2.0 + _deltax, winSize.height / 2.0));
        }
    }
}

void HowToPlayScene::onTouchEnded()
{
    Size winSize = Director::getInstance()->getWinSize();
    if(_currentRuleVectorPosition == NUM_OF_RULES - 1 && _currentRule->getPosition().x <= winSize.width / 2.0){
        _currentRule->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    }
    else if(_currentRuleVectorPosition == 0 && winSize.width / 2.0 <= _currentRule->getPosition().x)
    {
        _currentRule->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    }
    else if(0 < _currentRule->getPosition().x && _currentRule->getPosition().x < winSize.width / 2.0)
    {
        _currentRule->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
        _nextRule->setPosition(Vec2(winSize.width + winSize.width / 2.0, winSize.height / 2.0));
    }
    else if(winSize.width / 2.0 < _currentRule->getPosition().x && _currentRule->getPosition().x < winSize.width)
    {
        _currentRule->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
        _prevRule->setPosition(Vec2(-winSize.width / 2.0, winSize.height / 2.0));
    }
    else if(_currentRule->getPosition().x <= 0){
        _currentRule->setPosition(Vec2(-winSize.width / 2.0, winSize.height / 2.0));
        _nextRule->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
        _currentRuleVectorPosition++;
    }
    else if(winSize.width <= _currentRule->getPosition().x)
    {
        _currentRule->setPosition(Vec2(winSize.width + winSize.width / 2.0, winSize.height / 2.0));
        _prevRule->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
        _currentRuleVectorPosition--;
    }
    CCLOG("%d", _currentRuleVectorPosition);
}
