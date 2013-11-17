//
//  GameLayer.cpp
//  airplanedemo
//
//  Created by Leo Lin on 11/9/13.
//
//

#include "GameLayer.h"
#include "Enemy1Sprite.h"
#include "Enemy2Sprite.h"
#include "Enemy3Sprite.h"
#include "UFOLayer.h"

GameLayer::GameLayer(void)
{
    planeLayer=NULL;
    bulletLayer = NULL;
    enemy1Layer=NULL;
	enemy2Layer=NULL;
	enemy3Layer=NULL;
	controlLayer=NULL;
    
    score=0;
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
        this->bulletLayer = BulletLayer::create();
        this->addChild(bulletLayer);
        this->bulletLayer->StartShoot();
        
        // add enemy1Layer
        this->enemy1Layer = Enemy1Layer::create();
        this->addChild(enemy1Layer);
        
        // add enemy2Layer
        this->enemy2Layer = Enemy2Layer::create();
        this->addChild(enemy2Layer);
        
        // add enemy3Layer
        this->enemy3Layer = Enemy3Layer::create();
        this->addChild(enemy3Layer);
        
        //加入controlLayer
		this->controlLayer=ControlLayer::create();
		this->addChild(controlLayer);
        
        //加入UFOLayer
		this->ufoLayer=UFOLayer::create();
		this->addChild(ufoLayer);
        
        // set touch enabled
        this->setTouchEnabled(true);
        
        // collision detection
        this->scheduleUpdate();
        
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

void GameLayer::registerWithTouchDispatcher()
{
    CCDirector * pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (this->planeLayer->isAlive)
    {
        CCPoint beginPoint = pTouch->locationInView();
        beginPoint = CCDirector::sharedDirector()->convertToGL(beginPoint);
        // juggle the area of drag
        CCRect planeRect = this->planeLayer->getChildByTag(AIRPLANE)->boundingBox();
        planeRect.origin.x -= 15;
        planeRect.origin.y -= 15;
        planeRect.size.width += 30;
        planeRect.size.height += 30;
        if (CCRect::CCRectContainsPoint(planeRect, this->getParent()->convertTouchToNodeSpace(pTouch)) == true)
        {
            CCPoint endPoint = pTouch->previousLocationInView();
            endPoint = CCDirector::sharedDirector()->convertToGL(endPoint);
            
            CCPoint offSet = ccpSub(beginPoint, endPoint);
            CCPoint toPoint = ccpAdd(this->planeLayer->getChildByTag(AIRPLANE)->getPosition(), offSet);
            this->planeLayer->MoveTo(toPoint);
        }
    }
}

void GameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void GameLayer::update(float dt)
{
    CCArray* bulletsToDelete = CCArray::create();
    bulletsToDelete->retain();
    CCObject *bt, *et, *ut;
    
/*
    if (this->bulletLayer->m_pAllBullet->count()>0)
    {
        CCSprite * bullet = (CCSprite*)this->bulletLayer->m_pAllBullet->objectAtIndex(0);
        CCLog("bullet:origin %d %d size %d %d", bullet->boundingBox().origin.x, bullet->boundingBox().origin.y,bullet->boundingBox().size.width, bullet->boundingBox().size.height );
    }
    */
    
    //enemy1 && bullet CheckCollision
    CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt)
    {
        CCSprite* bullet = (CCSprite*)bt;
        
        CCArray* enemy1sToDelete = CCArray::create();
        enemy1sToDelete->retain();
        CCARRAY_FOREACH(this->enemy1Layer->m_pAllEnemy1, et)
        {
            Enemy1Sprite * enemy1 = (Enemy1Sprite*)et;
            if (CCRect::CCRectIntersectsRect(bullet->boundingBox(), enemy1->boundingBox()))
            {
                if (enemy1->life == 1)
                {
                    enemy1->life -- ;
                    bulletsToDelete->addObject(bullet);
                    enemy1sToDelete->addObject(enemy1);
                    score+=ENEMY1_SCORE;
					this->controlLayer->updateScore(score);
                    //CCLog("bullet:origin %d %d size %d %d", bullet->boundingBox().origin.x, bullet->boundingBox().origin.y,bullet->boundingBox().size.width, bullet->boundingBox().size.height );
                    //CCLog("enemy1:origin %d %d size %d %d", enemy1->boundingBox().origin.x, enemy1->boundingBox().origin.y,enemy1->boundingBox().size.width, enemy1->boundingBox().size.height);
                }
                else ;
            }
        }
        CCARRAY_FOREACH(enemy1sToDelete, et)
        {
            Enemy1Sprite * enemy1 = (Enemy1Sprite*)et;
            this->enemy1Layer->enemy1Blowup(enemy1);
        }
        enemy1sToDelete->release();
    }
    CCARRAY_FOREACH(bulletsToDelete, bt)
    {
        CCSprite* bullet=(CCSprite*)bt;
		this->bulletLayer->RemoveBullet(bullet);
    }
    
    //ememy2 & bullet CheckCollision
    CCARRAY_FOREACH(this->bulletLayer->m_pAllBullet, bt)
    {
        CCSprite * bullet = (CCSprite*)bt;
        
        CCArray * enemy2sToDelete = CCArray::create();
        enemy2sToDelete->retain();
        CCARRAY_FOREACH(this->enemy2Layer->m_pAllEnemy2, et)
        {
            Enemy2Sprite * enemy2 = (Enemy2Sprite*)et;
            if (CCRect::CCRectIntersectsRect(bullet->boundingBox(), enemy2->boundingBox()))
            {
                if (enemy2->life>1)
                {
                    enemy2->life--;
                    bulletsToDelete->addObject(bullet);
                }
                else if(enemy2->life == 1)
                {
                    enemy2->life--;
                    bulletsToDelete->addObject(bullet);
                    enemy2sToDelete->addObject(enemy2);
                    score+=ENEMY2_SCORE;
					this->controlLayer->updateScore(score);
                }
                else ;
            }
        }
        CCARRAY_FOREACH(enemy2sToDelete, et)
        {
            Enemy2Sprite * enemy2 = (Enemy2Sprite*)et;
            this->enemy2Layer->enemy2Blowup(enemy2);
        }
        enemy2sToDelete->release();
    }
    CCARRAY_FOREACH(bulletsToDelete,bt)
	{
		CCSprite* bullet=(CCSprite*)bt;
		this->bulletLayer->RemoveBullet(bullet);
	}
    
    
    CCRect airplaneRect=this->planeLayer->getChildByTag(AIRPLANE)->boundingBox();
	airplaneRect.origin.x+=30;
	airplaneRect.size.width-=60;
	//enemy1 & airplane CheckCollosion
	CCARRAY_FOREACH(this->enemy1Layer->m_pAllEnemy1,et)
	{
		Enemy1Sprite* enemy1=(Enemy1Sprite*)et;
		if (enemy1->life>0)
		{
			if (CCRect::CCRectIntersectsRect(airplaneRect,enemy1->boundingBox()))
			{
				//卸载所有任务计划
				this->unscheduleAllSelectors();
				this->bulletLayer->StopShoot();
				//this->mutiBulletsLayer->StopShoot();
				//this->planeLayer->Blowup(score);
				return;
			}
		}
	}
    
	//enemy2 & airplane CheckCollosion
	CCARRAY_FOREACH(this->enemy2Layer->m_pAllEnemy2,et)
	{
		Enemy2Sprite* enemy2=(Enemy2Sprite*)et;
		if (enemy2->life>0)
		{
			if (CCRect::CCRectIntersectsRect(airplaneRect,enemy2->boundingBox()))
			{
				//卸载所有任务计划
				this->unscheduleAllSelectors();
				this->bulletLayer->StopShoot();
				//this->mutiBulletsLayer->StopShoot();
				//this->planeLayer->Blowup(score);
				return;
			}
		}
	}
    
	//enemy3 & airplane CheckCollosion
	CCARRAY_FOREACH(this->enemy3Layer->m_pAllEnemy3,et)
	{
		Enemy3Sprite* enemy3=(Enemy3Sprite*)et;
		if (enemy3->life>0)
		{
			if (CCRect::CCRectIntersectsRect(airplaneRect,enemy3->boundingBox()))
			{
				//卸载所有任务计划
				this->unscheduleAllSelectors();
				this->bulletLayer->StopShoot();
				//this->mutiBulletsLayer->StopShoot();
				//this->planeLayer->Blowup(score);
				return;
			}
		}
	}
}

