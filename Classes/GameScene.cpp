//
//  GameScene.cpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#include "GameScene.hpp"

#include "TitleScene.hpp"
#include "MultiPlayerLayer.hpp"

#include "ui/CocosGUI.h"

USING_NS_CC;

GameScene::GameScene()
{
    
}

GameScene::~GameScene()
{
    
}

Scene* GameScene::createScene()
{
    Scene* scene = Scene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if(!Layer::init()) return false;
    
    // window size
    Size winSize = Director::getInstance()->getWinSize();
    
    // place background
    Sprite* background = Sprite::create("background.png");
    background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(background);
    
    // place menu button
    cocos2d::ui::Button* menu = cocos2d::ui::Button::create("menu.png", "menu_pressed.png");
    menu->setPosition(Vec2(menu->getContentSize().width / 2.0 + 30, winSize.height - menu->getContentSize().height / 2.0 - 30));
    menu->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
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
    
    // place logo
    Sprite* logo = Sprite::create("logo.png");
    logo->setPosition(Vec2(winSize.width / 2.0, winSize.height - 250));
    this->addChild(logo);
    
    // add the multiplayer layer
    MultiPlayerLayer* multiplayerlayer = MultiPlayerLayer::create();
    this->addChild(multiplayerlayer);
    
    return true;
}