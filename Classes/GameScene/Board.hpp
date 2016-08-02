//
//  Board.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>

#include "BigTile.hpp"

class Board :public cocos2d::Node
{
CC_CONSTRUCTOR_ACCESS:
    Board();
    virtual ~Board();
    
public:
    bool init()override;
    CREATE_FUNC(Board);
    
    bool checkWin();
    bool checkDraw();
    
    /* getters & setters start*/
    // big tile list
    BigTile** getBigTileList() { return _bigTileList; }
    /* getters & setters end*/
private:
    cocos2d::Sprite* _board;
    BigTile* _bigTileList[9];
};

#endif /* Board_hpp */
