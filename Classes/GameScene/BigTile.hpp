//
//  BigTile.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-06-16.
//
//

#ifndef BigTile_hpp
#define BigTile_hpp

#include <stdio.h>
#include "Block.hpp"

#include "SmallTile.hpp"

class BigTile :public cocos2d::Node
{
CC_CONSTRUCTOR_ACCESS:
    BigTile();
    virtual ~BigTile();
    
public:
    bool init(int idx);
    static BigTile* create(int idx);
    
    /* getters & setters start*/
    // tile num
    int getBigTileNum() { return _bigTileNum; }
    
    // done
    bool getDone() { return _done; }
    void setDone( bool done ) { _done = done; }
    
    // player won
    Block::Player getPlayerWon() { return _playerWon; }
    void setPlayerWon( Block::Player playerWon ) {_playerWon = playerWon; }
    
    // yellow bg
    cocos2d::Sprite* getYellowBG() { return _yellowBG; }
    
    // pink bg
    cocos2d::Sprite* getPinkBG() { return _pinkBG; }
    
    // blue bg
    cocos2d::Sprite* getBlueBG() { return _blueBG; }
    

    // small tile list
    SmallTile** getSmallTileList() { return _smallTileList; }
    /* getters & setters end */
private:
    int _bigTileNum;
    bool _done;
    Block::Player _playerWon;
    cocos2d::Sprite* _yellowBG;
    cocos2d::Sprite* _pinkBG;
    cocos2d::Sprite* _blueBG;
    cocos2d::Sprite* _board;
    SmallTile* _smallTileList[9];
};

#endif /* BigTile_hpp */
