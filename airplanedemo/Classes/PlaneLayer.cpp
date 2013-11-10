//
//  PlaneLayer.cpp
//  airplanedemo
//
//  Created by Leo Lin on 11/10/13.
//
//

#include "PlaneLayer.h"

PlaneLayer * PlaneLayer::sharePlane = NULL; // 静态变量要在cpp外初始化

PlaneLayer::PlaneLayer(void)
{
    isAlive = true;
}

PlaneLayer::~PlaneLayer(void)
{
}

PlaneLayer * PlaneLayer::create()
{
    PlaneLayer * pRet = new PlaneLayer();
    if (pRet && pRet->init() )
    {
        pRet->autorelease();
        sharePlane = pRet;
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool PlaneLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCLayer::init());
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCSprite * plane = CCSprite::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
        plane->setPosition( ccp(winSize.width/2, plane->getContentSize().height/2) );
        this->addChild(plane, 0, AIRPLANE);
        
        CCBlink * blank = CCBlink::create(1, 3);
        
        CCAnimation * animation = CCAnimation::create();
        animation->setDelayPerUnit(0.1f);
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
        animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2.png"));
        CCAnimate * animate = CCAnimate::create(animation);
        
        plane->runAction(blank);
        plane->runAction(CCRepeatForever::create(animate));
        
        bRet = true;
        
    } while (0);
    
    return bRet;
}