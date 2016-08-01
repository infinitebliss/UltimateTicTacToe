//
//  GameOverLayer.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-07-29.
//
//

#ifndef GameOverLayer_hpp
#define GameOverLayer_hpp

#include "Block.hpp"

class GameOverLayer :public cocos2d::Layer
{
CC_CONSTRUCTOR_ACCESS:
    GameOverLayer();
    virtual ~GameOverLayer();
    
public:
    static GameOverLayer* create(Block::Player player);
    
    bool init(Block::Player player);
};

#endif /* GameOver_hpp */
