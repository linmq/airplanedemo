//
//  WelcomeLayer.cpp
//  airplanedemo
//
//  Created by Leo Lin on 11/9/13.
//
//

#include "WelcomeLayer.h"
#include "GameScene.h"
//#include "GameOverLayer.h"

WelcomeLayer::WelcomeLayer(void)
{
}

WelcomeLayer::~WelcomeLayer()
{
}

bool WelcomeLayer::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        //png加入全局cache中
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot_backgroud.plist");
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot.plist");
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        // add background
        CCSprite* background = CCSprite::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
        background->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(background);
        
        // add copyright
        CCSprite* copyright = CCSprite::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("shoot_copyright.png"));
        copyright->setAnchorPoint(ccp(0.5, 0));
        copyright->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(copyright);
        
        // add loading
        CCSprite * loading = CCSprite::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
        loading->setPosition(ccp(winSize.width/2, winSize.height/2-40));
        this->addChild(loading);
        
        CCAnimation * animation = CCAnimation::create();
        animation->setDelayPerUnit(0.2f);
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading2.png"));
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading3.png"));
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading4.png"));
        
        CCAnimate * animate = CCAnimate::create( animation );
        CCRepeat * repeat = CCRepeat::create(animate, 2);
        CCCallFuncN * repeatdone = CCCallFuncN::create( this, callfuncN_selector(WelcomeLayer::loadingDone));
        CCSequence * sequence = CCSequence::create(repeat, repeatdone);
        loading->runAction(sequence);
        
        //getHighesHistorySorce();
        
        this->setKeypadEnabled(true);
        
        bRet = true;
        
    } while (0);
    
    return bRet;
}

void WelcomeLayer::loadingDone(CCNode * pNode)
{
    CCScene * pScene = GameScene::create();
    CCTransitionMoveInB * animateScene = CCTransitionMoveInB::create(0.5f, pScene);
}