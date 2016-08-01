//
//  GameOverLayer.cpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-07-29.
//
//

#include "GameOverLayer.hpp"
#include "GameScene.hpp"
#include "../TitleScene/TitleScene.hpp"

USING_NS_CC;

GameOverLayer::GameOverLayer()
{
    
}

GameOverLayer::~GameOverLayer()
{
    
}

GameOverLayer* GameOverLayer::create(Block::Player player)
{
    GameOverLayer* gameoverlayer = new GameOverLayer();
    if(gameoverlayer && gameoverlayer->init(player)){
        return gameoverlayer;
    }
    return nullptr;
}

bool GameOverLayer::init(Block::Player player)
{
    if(!Layer::init()) return false;
    
    // size of window
    Size winSize = Director::getInstance()->getWinSize();
    
    // popup background
    Sprite* popupbg = Sprite::create("gameover_popup.png");
    popupbg->setOpacity(200);
    this->addChild(popupbg);
    
    // player wins
    Sprite* playerwintitle = NULL;
    if(player == Block::Player::PLAYER1){
        playerwintitle = Sprite::create("player1wins.png");
    }
    else if(player == Block::Player::PLAYER2){
        playerwintitle = Sprite::create("player2wins.png");
    }
    else{
        playerwintitle = Sprite::create("draw.png");
    }
    playerwintitle->setPosition(Vec2(popupbg->getContentSize().width / 2.0, popupbg->getContentSize().height - 70));
    popupbg->addChild(playerwintitle);
    
    auto replayButton = MenuItemImage::create("playagain.png", "playagain.png", [](Ref* ref){
        // 「もう一度遊ぶ」ボタンを押したときの処理
        // 新しくMainSceneを作成して置き換えてやる
        auto scene = GameScene::createScene();
        auto transition = TransitionCrossFade::create(0.5,scene);
        Director::getInstance()->replaceScene(transition);
    });
    
    // 「タイトルへ戻る」ボタン
    auto titleButton = MenuItemImage::create("backtomenu.png", "backtomenu.png", [](Ref* ref){
                    auto scene = TitleScene::createScene();
                    auto transition = TransitionCrossFade::create(1.0, scene);
                    Director::getInstance()->replaceScene(transition);
    });
    
    // 2つのボタンからメニューを作成する
    auto menu = Menu::create(replayButton, titleButton, NULL);
    // ボタンを縦に並べる
    menu->alignItemsVerticallyWithPadding(15); // ボタンを縦に並べる
    menu->setPosition(Vec2(popupbg->getContentSize().width / 2.0, popupbg->getContentSize().height - 220));
    popupbg->addChild(menu);
    
    
    return true;
}