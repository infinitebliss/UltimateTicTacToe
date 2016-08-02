//
//  Rule.cpp
//  UltimateTicTacToe
//
//  Created by Risa Yoneyama on 2016-08-02.
//
//

#include "Rule.hpp"

USING_NS_CC;

Rule::Rule()
{
    
}

Rule::~Rule()
{
    
}

Rule* Rule::create(int ruleNum)
{
    Rule* rule = new Rule();
    
    if(rule && rule->init(ruleNum))
    {
        rule->autorelease();
        return rule;
    }
    CC_SAFE_DELETE(rule);
    return nullptr;
}

bool Rule::init(int ruleNum)
{
    if(!Node::init()) return false;
    
    _ruleNum = ruleNum;
    
    // bg
    Sprite* bg = Sprite::create("rule_bg.png");
    bg->setPosition(Vec2(bg->getContentSize().width / 2.0, bg->getContentSize().height / 2.0));
    this->addChild(bg);
    this->setContentSize(bg->getContentSize());
    this->setAnchorPoint(Vec2(0.5, 0.5));
    
    // title
    Sprite* title = Sprite::create(this->getTitleFileName());
    title->setPosition(Vec2(this->getContentSize().width / 2.0, this->getContentSize().height - 50));
    this->addChild(title);
    
    // text
    Sprite* text = Sprite::create(this->getTextFileName());
    text->setPosition(Vec2(this->getContentSize().width / 2.0, this->getContentSize().height / 2.0));
    this->addChild(text);
    
//    // image
//    Sprite* image = Sprite::create(this->getImageFileName());
//    image->setPosition(Vec2(this->getContentSize().width / 2.0, this->getContentSize().height - 450));
//    this->addChild(image);
    
    return true;
}

std::string Rule::getTitleFileName()
{
    std::string fileName = "";
    fileName = StringUtils::format("rule%d_title.png", _ruleNum);
    return fileName;
}

std::string Rule::getTextFileName()
{
    std::string fileName = "";
    fileName = StringUtils::format("rule%d_text.png", _ruleNum);
    return fileName;
}

std::string Rule::getImageFileName()
{
    std::string fileName = "";
    fileName = StringUtils::format("rule%d_image.png", _ruleNum);
    return fileName;
}