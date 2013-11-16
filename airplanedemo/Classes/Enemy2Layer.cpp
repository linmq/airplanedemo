//
//  Enemy2Layer.cpp
//  airplanedemo
//
//  Created by Leo Lin on 11/16/13.
//
//

#include "Enemy2Layer.h"

Enemy2Layer::Enemy2Layer(void)
{
    enemy2SpriteFrame = NULL;
    
    m_pAllEnemy2 = CCArray::create();
    m_pAllEnemy2->retain();
}

Enemy2Layer::~Enemy2Layer(void)
{
    m_pAllEnemy2->release();
    m_pAllEnemy2 = NULL;
}

bool Enemy2Layer::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        enemy2SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2.png");
        
        this->schedule(schedule_selector(Enemy2Layer::AddEnemy2), 3.0f);
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void Enemy2Layer::AddEnemy2(float dt)
{
    Enemy2Sprite * enemy2 = Enemy2Sprite::create(enemy2SpriteFrame);
    
    CCSize enemy2Size = enemy2->getContentSize();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int minX = enemy2Size.width/2;
    int maxX = winSize.width - enemy2Size.width/2;
    int rangeX = maxX - minX;
    int actualX = (rand()%rangeX) + minX;
    
    enemy2->setPosition(ccp(actualX, winSize.height+enemy2Size.height/2));
    this->addChild(enemy2);
    this->m_pAllEnemy2->addObject(enemy2);
    
    int minDuration = 3;
    int maxDuration = 6;
    int rangeDuration = maxDuration - minDuration;
    int actualDuration = (rand()%rangeDuration) + minDuration;
    
    CCFiniteTimeAction * actionMove = CCMoveTo::create(actualDuration, ccp(actualX, 0-enemy2->getContentSize().height/2));
    CCFiniteTimeAction * actionDone = CCCallFuncN::create(this, callfuncN_selector(Enemy2Layer::enemy2MoveFinished));
    
    CCSequence * sequence = CCSequence::create(actionMove, actionDone);
    enemy2->runAction(sequence);
}

void Enemy2Layer::enemy2MoveFinished(CCNode * pSender)
{
    Enemy2Sprite * enemy2 = (Enemy2Sprite*)pSender;
    this->removeChild(enemy2, true);
    this->m_pAllEnemy2->removeObject(enemy2);
}

void Enemy2Layer::enemy2Blowup(Enemy2Sprite* enemy2)
{
    CCAnimation * animation = CCAnimation::create();
    animation->setDelayPerUnit(0.1f);
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down4.png"));
    
    CCAnimate * animate = CCAnimate::create(animation);
    CCCallFuncND * removeEnemy2 = CCCallFuncND::create(this, callfuncND_selector(Enemy2Layer::RemoveEnemy2), (void*)enemy2);
    CCSequence * sequence = CCSequence::create(animate, removeEnemy2);
    enemy2->runAction(sequence);
}

void Enemy2Layer::RemoveEnemy2(CCNode* pTarget, void *data)
{
    Enemy2Sprite * enemy2 = (Enemy2Sprite*)data;
    if (enemy2!=NULL)
    {
        m_pAllEnemy2->removeObject(enemy2);
        this->removeChild(enemy2, true);
    }
}

void Enemy2Layer::RemoveAllEnemy2()
{
    CCObject * obj;
    CCARRAY_FOREACH(m_pAllEnemy2, obj)
    {
        Enemy2Sprite * enemy2 = (Enemy2Sprite*)obj;
        if (enemy2->life>0)
        {
            enemy2Blowup(enemy2);
        }
    }
}