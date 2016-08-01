//
//  HowToPlayScene.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-08-01.
//
//

#ifndef HowToPlayScene_hpp
#define HowToPlayScene_hpp

#include <stdio.h>

class HowToPlayScene : public cocos2d::Layer
{
CC_CONSTRUCTOR_ACCESS:
    HowToPlayScene();
    virtual ~HowToPlayScene();
    
public:
    CREATE_FUNC(HowToPlayScene);
    static cocos2d::Scene* createScene();
    
    bool init() override;
};

#endif /* HowToPlayScene_hpp */
