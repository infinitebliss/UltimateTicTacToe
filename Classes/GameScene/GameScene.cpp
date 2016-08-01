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
#include "SinglePlayerLayer.hpp"

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
    
    // user default
    UserDefault* ud = UserDefault::getInstance();
    
    // place background
    Sprite* background = Sprite::create("bg_white.png");
    background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(background);
    
    // place logo
    Sprite* logo = Sprite::create("logo.png");
    logo->setPosition(Vec2(winSize.width / 2.0, winSize.height - 250));
    this->addChild(logo);
    
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
    
    // place redo button
    cocos2d::ui::Button* redo = cocos2d::ui::Button::create("redo.png", "redo_pressed.png");
    redo->setPosition(Vec2(winSize.width - redo->getContentSize().width / 2.0 - 50, winSize.height - redo->getContentSize().height / 2.0 - 50));
    redo->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
            {
                _multiPlayerLayer->removeAllChildrenWithCleanup(true);
                _multiPlayerLayer->removeFromParentAndCleanup(true);
                _multiPlayerLayer = MultiPlayerLayer::create();
                this->addChild(_multiPlayerLayer);
                break;
            }
            default:
                break;
        }
    });
    this->addChild(redo);
    
    // place ad banner
    Sprite* ad = Sprite::create("ad.png");
    ad->setPosition(Vec2(winSize.width / 2.0, ad->getContentSize().height / 2.0));
    this->addChild(ad);
    
    if(ud->getBoolForKey("singleplayer")){
        SinglePlayerLayer* singleplayerlayer = SinglePlayerLayer::create();
        this->addChild(singleplayerlayer);
    }
    else{
        // add the multiplayer layer
        _multiPlayerLayer = MultiPlayerLayer::create();
        this->addChild(_multiPlayerLayer);
    }
    
    return true;
}