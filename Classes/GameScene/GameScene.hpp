//
//  GameScene.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "MultiPlayerLayer.hpp"

class GameScene :public cocos2d::Layer
{
CC_CONSTRUCTOR_ACCESS:
    GameScene();
    virtual ~GameScene();
    
public:
    static cocos2d::Scene* createScene();
    bool init()override;
    CREATE_FUNC(GameScene);
    
private:
    MultiPlayerLayer* _multiPlayerLayer;
};

#endif /* GameScene_hpp */
