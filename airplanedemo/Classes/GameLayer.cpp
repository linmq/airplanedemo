//
//  GameLayer.cpp
//  airplanedemo
//
//  Created by Leo Lin on 11/9/13.
//
//

#include "GameLayer.h"


GameLayer::GameLayer(void)
{
    bulletLayer = NULL;
}

GameLayer::~GameLayer(void)
{
}

bool GameLayer::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        // add all png
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot_background.plist");
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot.plist");
        
        // load background1
        background1 = CCSprite::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
        background1->setAnchorPoint(ccp(0, 0));
        background1->setPosition(ccp(0, 0));
        this->addChild(background1);
        
        // load background2
        background2 = CCSprite::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
        background2->setAnchorPoint(ccp(0, 0));
        background2->setPosition( ccp(0, background2->getContentSize().height-2));
        this->addChild(background2);
        
        // add planeLayer
        this->planeLayer = PlaneLayer::create();
        this->addChild(planeLayer);
        this->schedule(schedule_selector(GameLayer::backgroundMove), 0.01f);
        
        // add bulletLayer
        /*
        this->bulletLayer = BulletLayer::create();
        this->addChild(bulletLayer);
        this->bulletLayer->StartShoot();
        */
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void GameLayer::backgroundMove(float dt)
{
   background1->setPositionY(background1->getPositionY()-2);
    background2->setPositionY(background1->getPositionY()+background1->getContentSize().height-2);
	if (background2->getPositionY()==0)
	{
		background1->setPositionY(0);
	}
}