//
//  TitleScene.cpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#include "TitleScene.hpp"

#include "GameScene.hpp"

USING_NS_CC;

TitleScene::TitleScene()
{
    
}

TitleScene::~TitleScene()
{
    
}

Scene* TitleScene::createScene()
{
    Scene* scene = Scene::create();
    TitleScene* layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

bool TitleScene::init()
{
    if(!Layer::init()) return false;
    
    // get window size
    Size winSize = Director::getInstance()->getWinSize();
    
    //
    
    // place background
    Sprite* background = Sprite::create("background.png");
    background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(background);
    
    // place logo
    Sprite* icon = Sprite::create("icon.png");
    icon->setPosition(Vec2(175, winSize.height - 450));
    this->addChild(icon);
    
    // place title
    Sprite* title = Sprite::create("title.png");
    title->setPosition(Vec2(winSize.width / 2.0, winSize.height + title->getContentSize().height / 2.0));
    this->addChild(title);
    // animate title
    MoveBy* move1 = MoveBy::create(0.5, Vec2(0, -700));
    title->runAction(move1);
    
    // MENU
    // single player mode
    MenuItemImage* singleplayer = MenuItemImage::create("single.png", "single_pressed.png", [&](Ref* ref){

    });
    // multi player mode
    MenuItemImage* multiplayer = MenuItemImage::create("multi.png", "multi_pressed.png", [&](Ref* ref){
        // make sure they cant press twice
        this->getEventDispatcher()->removeAllEventListeners();
        // start game
        Scene* scene = GameScene::createScene();
        TransitionSlideInB* transition = TransitionSlideInB::create(1.0, scene);
        Director::getInstance()->replaceScene(transition);
    });
    // create menu
    Menu* menu = Menu::create(singleplayer, multiplayer, NULL);
    menu->alignItemsVerticallyWithPadding(0);
    menu->setPosition(Vec2(winSize.width + menu->getContentSize().width / 2.0, winSize.height - 900));
    menu->setAnchorPoint(Vec2(0.5, 1));
    this->addChild(menu);
    
    // animate menu
    MoveTo* move2 = MoveTo::create(0.5, Vec2(winSize.width / 2.0, winSize.height - 900));
    menu->runAction(move2);
    return true;
}