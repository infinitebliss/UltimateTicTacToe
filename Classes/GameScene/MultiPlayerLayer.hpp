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

#include "ui/CocosGUI.h"

class MultiPlayerLayer :public cocos2d::Layer
{
CC_CONSTRUCTOR_ACCESS:
    MultiPlayerLayer();
    virtual ~MultiPlayerLayer();
    
public:
    // ----- class method ----- //
    CREATE_FUNC(MultiPlayerLayer);
    
    // ----- instance methods ----- //
    bool init()override;
    void onTouchBegan(cocos2d::Touch* touch);
    void resetAvailableBigTiles(int nextSmallTileNum);
    void checkBigTileFull(int bigTileNum);
    void checkBigTileForWin(int bigTileNum);
    void checkBoardForWin();
    void checkBoardFull();
    void gameDone();
    
private:
    // ----- instance variables ----- //
    cocos2d::Sprite* _playerNow;
    cocos2d::ui::Button* _undo;
    Board* _board;
    Block* _currentBlock;
    Block::Player _player;
    std::pair<int, int> _tile;
    std::map<std::pair<int, int>, Block::Player> _tileMap;
    std::vector<int> _availableBigTiles;
    std::map<std::pair<int, int>, Block::Player> _prevTileMap;
};

#endif /* MultiPlayerLayer_hpp */
