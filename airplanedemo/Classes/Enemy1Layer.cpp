//
//  Enemy1Layer.cpp
//  airplanedemo
//
//  Created by Leo Lin on 11/15/13.
//
//

#include "Enemy1Layer.h"

Enemy1Layer::Enemy1Layer(void)
{
    enemy1SpriteFrame = NULL;
    
    m_pAllEnemy1 = CCArray::create();
    m_pAllEnemy1->retain();
}

Enemy1Layer::~Enemy1Layer(void)
{
    m_pAllEnemy1->release();
    m_pAllEnemy1 = NULL;
}

bool Enemy1Layer::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        enemy1SpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1.png");
        
        this->schedule(schedule_selector(Enemy1Layer::AddEnemy1), 0.5f);
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void Enemy1Layer::AddEnemy1(float dt)
{
    Enemy1Sprite * enemy1 = Enemy1Sprite::create(enemy1SpriteFrame);
    
    CCSize enemy1Size = enemy1->getContentSize();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int minX = enemy1Size.width/2;
    int maxX = winSize.width - enemy1Size.width/2;
    int rangeX = maxX - minX;
    int actualX = (rand()%rangeX) + minX;
    
    enemy1->setPosition(ccp(actualX, winSize.height+enemy1Size.height/2));
    this->addChild(enemy1);
    this->m_pAllEnemy1->addObject(enemy1);
    
    int minDuration = 2;
    int maxDuration = 4;
    int rangeDuration = maxDuration - minDuration;
    int actualDuration = (rand()%rangeDuration) + minDuration;
    
    CCFiniteTimeAction * actionMove = CCMoveTo::create(actualDuration, ccp(actualX, 0-enemy1->getContentSize().height/2));
    CCFiniteTimeAction * actionDone = CCCallFuncN::create(this, callfuncN_selector(Enemy1Layer::enemy1MoveFinished));
    
    CCSequence * sequence = CCSequence::create(actionMove, actionDone);
    enemy1->runAction(sequence);
}

void Enemy1Layer::enemy1MoveFinished(CCNode * pSender)
{
    Enemy1Sprite * enemy1 = (Enemy1Sprite*)pSender;
    this->removeChild(enemy1, true);
    this->m_pAllEnemy1->removeObject(enemy1);
}

void Enemy1Layer::enemy1Blowup(Enemy1Sprite* enemy1)
{
    CCAnimation * animation = CCAnimation::create();
    animation->setDelayPerUnit(0.1f);
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down4.png"));
    
    CCAnimate * animate = CCAnimate::create(animation);
    CCCallFuncND * removeEnemy1 = CCCallFuncND::create(this, callfuncND_selector(Enemy1Layer::RemoveEnemy1), (void*)enemy1);
    CCSequence * sequence = CCSequence::create(animate, removeEnemy1);
    enemy1->runAction(sequence);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("enemy1_down.mp3");
}

void Enemy1Layer::RemoveEnemy1(CCNode* pTarget, void *data)
{
    Enemy1Sprite * enemy1 = (Enemy1Sprite*)data;
    if (enemy1!=NULL)
    {
        m_pAllEnemy1->removeObject(enemy1);
        this->removeChild(enemy1, true);
    }
}

void Enemy1Layer::RemoveAllEnemy1()
{
    CCObject * obj;
    CCARRAY_FOREACH(m_pAllEnemy1, obj)
    {
        Enemy1Sprite * enemy1 = (Enemy1Sprite*)obj;
        if (enemy1->life>0)
        {
            enemy1Blowup(enemy1);
        }
    }
}