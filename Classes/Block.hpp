//
//  Block.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>

class Block :public cocos2d::Node
{
CC_CONSTRUCTOR_ACCESS:
    Block();
    ~Block();
    
public:
    // player
    enum class Player{
        PLAYER1 = 0,
        PLAYER2
    };
    
    bool init(Player idx);
    static Block* create(Player idx);
    
private:
    cocos2d::Sprite* _block;
};

#endif /* Block_hpp */
