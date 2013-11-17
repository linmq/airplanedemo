//
//  BulletLayer.cpp
//  airplanedemo
//
//  Created by Leo Lin on 11/11/13.
//
//

#include "BulletLayer.h"
#include "PlaneLayer.h"

BulletLayer::BulletLayer(void)
{
    bulletBatchNode = NULL;
    
    m_pAllBullet = CCArray::create();
    m_pAllBullet->retain();
}

BulletLayer::~BulletLayer()
{
    m_pAllBullet->release();
    m_pAllBullet = NULL;
}

bool BulletLayer::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        CCTexture2D * texture = CCTextureCache::sharedTextureCache()->textureForKey("shoot.png");
        bulletBatchNode = CCSpriteBatchNode::create(texture);
        this->addChild(bulletBatchNode);
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void BulletLayer::StartShoot(float delay)
{
	this->schedule(schedule_selector(BulletLayer::AddBullet),0.15f,kCCRepeatForever,delay);
}

void BulletLayer::StopShoot()
{
    this->unschedule(schedule_selector(BulletLayer::AddBullet));
}

void BulletLayer::AddBullet(float dt)
{
    CCSprite* bullet=CCSprite::createWithSpriteFrameName("bullet1.png");
    //bulletBatchNode->addChild(bullet);//这里子弹要添加到bulletBatchNode中，效果如下左图
    this->addChild(bullet);
    this->m_pAllBullet->addObject(bullet);
    
    CCPoint planePosition = PlaneLayer::sharePlane->getChildByTag(AIRPLANE)->getPosition();
    CCPoint bulletPosition = ccp(planePosition.x, planePosition.y + PlaneLayer::sharePlane->getChildByTag(AIRPLANE)->getContentSize().height/2 );
    bullet->setPosition(bulletPosition);
    
    float length = CCDirector::sharedDirector()->getWinSize().height + bullet->getContentSize().height/2 -bulletPosition.y;
    float velocity = 420/1; //420 pexel/second
    float realMoveDuration = length/velocity;
    
    CCFiniteTimeAction * actionMove = CCMoveTo::create(realMoveDuration, ccp(bulletPosition.x, CCDirector::sharedDirector()->getWinSize().height + bullet->getContentSize().height/2 ));
    CCFiniteTimeAction * actionDone = CCCallFunc::create(this, callfunc_selector(BulletLayer::bulletMoveFinished));
    CCSequence * sequence = CCSequence::create(actionMove, actionDone);
    bullet->runAction(sequence);
}

void BulletLayer::bulletMoveFinished(CCNode * pSender)
{
    CCSprite * bullet = (CCSprite*)pSender;
    m_pAllBullet->removeObject(bullet);
    this->removeChild(bullet,true);
}

void BulletLayer::RemoveBullet(CCSprite * bullet)
{
    if (bullet!=NULL) {
        this->m_pAllBullet->removeObject(bullet);
        this->removeChild(bullet, true);
    }
}