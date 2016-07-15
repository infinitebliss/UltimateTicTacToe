//
//  MultiPlayerLayer.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#ifndef MultiPlayerLayer_hpp
#define MultiPlayerLayer_hpp

#include <stdio.h>

#include "Board.hpp"
#include "Block.hpp"

class MultiPlayerLayer :public cocos2d::Layer
{
CC_CONSTRUCTOR_ACCESS:
    MultiPlayerLayer();
    ~MultiPlayerLayer();
    
public:
    // class method
    bool init()override;
    CREATE_FUNC(MultiPlayerLayer);
    
    void onTouchBegan(cocos2d::Touch* touch);
    void resetAvailableBigTiles(int nextSmallTileNum);
    
private:
    Board* _board;
    Block* _currentBlock;
    Block::Player _player;
    std::map<std::pair<int, int>, Block::Player> _tileMap;
    std::vector<int> _availableBigTiles;
};

#endif /* MultiPlayerLayer_hpp */
