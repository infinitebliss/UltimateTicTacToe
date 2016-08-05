//
//  SinglePlayerLayer.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-07-29.
//
//

#ifndef SinglePlayerLayer_hpp
#define SinglePlayerLayer_hpp

#include "Block.hpp"

#include "Bots.hpp"
#include "Board.hpp"

class SinglePlayerLayer : public cocos2d::Layer
{
CC_CONSTRUCTOR_ACCESS:
    SinglePlayerLayer();
    virtual ~SinglePlayerLayer();
    
public:
    CREATE_FUNC(SinglePlayerLayer);
    
    bool init()override;
    void update(float dt) override;
    
    enum class GameState
    {
        WAITING = 0,
        THINKING,
        DONE
    };
    void onTouchBegan(cocos2d::Touch* touch);
    void botMove();
    void gameDone();
    
private:
    Bots* _bots;
    Board* _board;
    Block::Player _player;
    GameState _gameState;
    cocos2d::Sprite* _playerNow;
    int _timer;
    int _updateTimes;
};

#endif /* SinglePlayerLayer_hpp */
