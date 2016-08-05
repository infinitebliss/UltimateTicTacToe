//
//  Bots.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-08-03.
//
//

#ifndef Bots_hpp
#define Bots_hpp

#include "Block.hpp"

#include "Board.hpp"

class Bots :public cocos2d::Node
{
CC_CONSTRUCTOR_ACCESS:
    Bots();
    virtual ~Bots();
    
public:
    bool init()override;
    CREATE_FUNC(Bots);
    
    std::pair<int, int> randomBot(Board* board);
    std::pair<int, int> monteCarloBot(Board* board, Block::Player playerNext);
    
private:
    float _botThinkingTime;
    std::string _mode;
};

#endif /* Bots_hpp */
