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

    
    return true;
}
