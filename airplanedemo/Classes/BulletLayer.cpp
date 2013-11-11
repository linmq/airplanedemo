//
//  BulletLayer.cpp
//  airplanedemo
//
//  Created by Leo Lin on 11/11/13.
//
//

#include "BulletLayer.h"

BulletLayer::BulletLayer(void)
{
    bulletBatchNode = NULL;
}

BulletLayer::~BulletLayer()
{
    
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

void BulletLayer::AddBullet(float dt)
{
    CCSprite* bullet=CCSprite::createWithSpriteFrameName("bullet1.png");
    bulletBatchNode->addChild(bullet);//这里子弹要添加到bulletBatchNode中，效果如下左图
//    this->addChild(bullet);
}