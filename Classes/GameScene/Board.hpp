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
    
    void resetAvailableBigTiles(int nextSmallTileNum);
    bool makeMoveFromTouch(cocos2d::Touch* touch, Block::Player player);
    bool makeMoveFromTile(std::pair<int, int> tile, Block::Player player);
    bool checkBigTileForWin(int bigTileNum, Block::Player player);
    bool checkBigTileFull(int bigTileNum);
    bool checkWin();
    bool checkDraw();
    void undoMove(Block::Player player);
    
    /* getters & setters start*/
    // big tile list
    BigTile** getBigTileList() { return _bigTileList; }
    /* getters & setters end*/
private:
    cocos2d::Sprite* _board;
    std::pair<int, int> _currentTile;
    Block* _currentBlock;
    std::vector<int> _availableBigTiles;
    std::map<std::pair<int, int>, Block::Player> _tileMap;
    BigTile* _bigTileList[9];
};

#endif /* Board_hpp */
