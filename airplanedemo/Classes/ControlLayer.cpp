//
//  ControlLayer.cpp
//  airplanedemo
//
//  Created by Leo Lin on 11/17/13.
//
//

#include "ControlLayer.h"

ControlLayer::ControlLayer(void)
{
    pPauseItem=NULL;
}

ControlLayer::~ControlLayer(void)
{
}

bool ControlLayer::init()
{
	bool bRet=false;
	do
	{
        CC_BREAK_IF(!CCLayer::init());
        
        CCSize winSize=CCDirector::sharedDirector()->getWinSize();
        
        CCSprite* normalPause=CCSprite::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));
		CCSprite* pressedPause=CCSprite::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));
        pPauseItem=CCMenuItemImage::create();
        pPauseItem->initWithNormalSprite(normalPause,pressedPause,NULL,this,menu_selector(ControlLayer::menuPauseCallback));
        pPauseItem->setPosition(ccp(normalPause->getContentSize().width/2+10,winSize.height-normalPause->getContentSize().height/2-10));
        CCMenu *menuPause=CCMenu::create(pPauseItem,NULL);
		menuPause->setPosition(CCPointZero);
		this->addChild(menuPause,101);
        
        bRet = true;
        
    }while (0);
    
    return bRet;
}

void ControlLayer::menuPauseCallback(CCObject* pSender)
{
    if(!CCDirector::sharedDirector()->isPaused())
    {
        pPauseItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_nor.png"));
		pPauseItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_resume_pressed.png"));
        CCDirector::sharedDirector()->pause();
        //this->addChild(noTouchLayer);
    }
    else
    {
        pPauseItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_nor.png"));
		pPauseItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_pause_pressed.png"));
        CCDirector::sharedDirector()->resume();
        //this->removeChild(noTouchLayer,true);
    }
}