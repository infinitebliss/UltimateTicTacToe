//
//  HowToPlayScene.hpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-08-01.
//
//

#ifndef HowToPlayScene_hpp
#define HowToPlayScene_hpp

#include "Rule.hpp"

class HowToPlayScene : public cocos2d::Layer
{
CC_CONSTRUCTOR_ACCESS:
    HowToPlayScene();
    virtual ~HowToPlayScene();
    
public:
    CREATE_FUNC(HowToPlayScene);
    static cocos2d::Scene* createScene();
    
    bool init() override;
    
    void onTouchBegan();
    void onTouchMoved();
    void onTouchEnded();
    
private:
    int _currentRuleVectorPosition;
    Rule* _currentRule;
    Rule* _prevRule;
    Rule* _nextRule;
    
    std::vector<Rule*> _ruleVector;
    
    float _deltax;
    cocos2d::Vec2 _touchBegan;
    cocos2d::Vec2 _touchNow;
    cocos2d::Vec2 _touchEnded;
};

#endif /* HowToPlayScene_hpp */