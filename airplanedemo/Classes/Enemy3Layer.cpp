//
//  Enemy3Layer.cpp
//  airplanedemo
//
//  Created by Leo Lin on 11/16/13.
//
//

#include "Enemy3Layer.h"

Enemy3Layer::Enemy3Layer(void)
{
    enemy3SpriteFrame_1 = NULL;
    enemy3SpriteFrame_2 = NULL;
    
    m_pAllEnemy3 = CCArray::create();
    m_pAllEnemy3->retain();
}

Enemy3Layer::~Enemy3Layer(void)
{
    m_pAllEnemy3->release();
    m_pAllEnemy3 = NULL;
}

bool Enemy3Layer::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        enemy3SpriteFrame_1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n1.png");
        enemy3SpriteFrame_2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n2.png");
        
        this->schedule(schedule_selector(Enemy3Layer::AddEnemy3), 6.0f);
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void Enemy3Layer::AddEnemy3(float dt)
{
    Enemy3Sprite * enemy3 = Enemy3Sprite::create(enemy3SpriteFrame_1);
    
    CCSize enemy3Size = enemy3->getContentSize();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int minX = enemy3Size.width/2;
    int maxX = winSize.width - enemy3Size.width/2;
    int rangeX = maxX - minX;
    int actualX = (rand()%rangeX) + minX;
    
    enemy3->setPosition(ccp(actualX, winSize.height+enemy3Size.height/2));
    this->addChild(enemy3);
    this->m_pAllEnemy3->addObject(enemy3);
    
    int minDuration = 4;
    int maxDuration = 8;
    int rangeDuration = maxDuration - minDuration;
    int actualDuration = (rand()%rangeDuration) + minDuration;
    
    CCFiniteTimeAction * actionMove = CCMoveTo::create(actualDuration, ccp(actualX, 0-enemy3->getContentSize().height/2));
    CCFiniteTimeAction * actionDone = CCCallFuncN::create(this, callfuncN_selector(Enemy3Layer::enemy3MoveFinished));
    
    CCSequence * sequence = CCSequence::create(actionMove, actionDone);
    enemy3->runAction(sequence);
    
    CCAnimation * animation = CCAnimation::create();
    animation->setDelayPerUnit(0.1f);
    animation->addSpriteFrame(enemy3SpriteFrame_1);
    animation->addSpriteFrame(enemy3SpriteFrame_2);
    CCAnimate * animate = CCAnimate::create(animation);
    enemy3->runAction(CCRepeatForever::create(animate));
}

void Enemy3Layer::enemy3MoveFinished(CCNode * pSender)
{
    Enemy3Sprite * enemy3 = (Enemy3Sprite*)pSender;
    this->removeChild(enemy3, true);
    this->m_pAllEnemy3->removeObject(enemy3);
}

void Enemy3Layer::enemy3Blowup(Enemy3Sprite* enemy3)
{
    CCAnimation * animation = CCAnimation::create();
    animation->setDelayPerUnit(0.1f);
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down1.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down2.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down3.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down4.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down5.png"));
    animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down6.png"));
    
    CCAnimate * animate = CCAnimate::create(animation);
    CCCallFuncND * removeEnemy3 = CCCallFuncND::create(this, callfuncND_selector(Enemy3Layer::RemoveEnemy3), (void*)enemy3);
    CCSequence * sequence = CCSequence::create(animate, removeEnemy3);
    enemy3->runAction(sequence);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("enemy3_down.mp3");
}

void Enemy3Layer::RemoveEnemy3(CCNode* pTarget, void *data)
{
    Enemy3Sprite * enemy3 = (Enemy3Sprite*)data;
    if (enemy3!=NULL)
    {
        m_pAllEnemy3->removeObject(enemy3);
        this->removeChild(enemy3, true);
    }
}

void Enemy3Layer::RemoveAllEnemy3()
{
    CCObject * obj;
    CCARRAY_FOREACH(m_pAllEnemy3, obj)
    {
        Enemy3Sprite * enemy3 = (Enemy3Sprite*)obj;
        if (enemy3->life>0)
        {
            enemy3Blowup(enemy3);
        }
    }
}