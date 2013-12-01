//
//  GameOverLayer.cpp
//  airplanedemo
//
//  Created by Leo Lin on 11/21/13.
//
//

#include "GameOverLayer.h"
#include "GameScene.h"

int GameOverLayer::highestHistoryScore=0;

GameOverLayer::GameOverLayer(void)
{
	score=0;
	highestScore=NULL;
}

GameOverLayer::~GameOverLayer(void)
{
}

GameOverLayer* GameOverLayer::create(int passScore)
{
    GameOverLayer *pRet = new GameOverLayer();
    pRet->score=passScore;
    if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool GameOverLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCLayer::init());
        
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();
        
        // add gameover_background
	    CCSprite* background=CCSprite::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("gameover.png"));
		background->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(background);
        
        // add BackMenu
		CCSprite* normalBackToGame=CCSprite::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));
		CCSprite* pressedBackToGame=CCSprite::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btn_finish.png"));
		CCMenuItemImage* pBackItem=CCMenuItemImage::create();
        pBackItem->initWithNormalSprite(normalBackToGame,pressedBackToGame,NULL,this,menu_selector(GameOverLayer::menuBackCallback));
		pBackItem->setPosition(ccp(winSize.width-normalBackToGame->getContentSize().width/2-10,normalBackToGame->getContentSize().height/2+10));
		CCMenu *menuBack=CCMenu::create(pBackItem,NULL);
		menuBack->setPosition(CCPointZero);
		this->addChild(menuBack);
        
        // show score
        CCString *strScore = CCString::createWithFormat("%d", score);
        CCLabelBMFont * finalScore = CCLabelBMFont::create(strScore->m_sString.c_str(), "font.fnt");
        finalScore->setColor(ccc3(143, 146, 147));
        finalScore->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(finalScore);
        
        if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		}
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("game_over.mp3");
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void GameOverLayer::menuBackCallback(CCObject* pSender)
{
    CCScene* pScene=GameScene::create();
	CCTransitionSlideInL* animateScene=CCTransitionSlideInL::create(1.0f,pScene);
	CCDirector::sharedDirector()->replaceScene(animateScene);
}