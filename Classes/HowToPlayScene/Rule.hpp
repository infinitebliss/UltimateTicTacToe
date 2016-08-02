//
//  Rule.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-08-02.
//
//

#ifndef Rule_hpp
#define Rule_hpp

#include <stdio.h>

class Rule :public cocos2d::Node
{
CC_CONSTRUCTOR_ACCESS:
    Rule();
    virtual ~Rule();
    
public:
    static Rule* create(int ruleNum);
    bool init(int ruleNum);
    
    std::string getTitleFileName();
    std::string getTextFileName();
    std::string getImageFileName();
    
private:
    int _ruleNum;
};

#endif /* Rule_hpp */
