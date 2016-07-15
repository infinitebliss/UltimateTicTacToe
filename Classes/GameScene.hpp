//
//  GameScene.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>

class GameScene :public cocos2d::Layer
{
CC_CONSTRUCTOR_ACCESS:
    GameScene();
    ~GameScene();
    
public:
    static cocos2d::Scene* createScene();
    bool init()override;
    CREATE_FUNC(GameScene);
};

#endif /* GameScene_hpp */
