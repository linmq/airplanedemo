//
//  Enemy1Sprite.cpp
//  airplanedemo
//
//  Created by Leo Lin on 11/15/13.
//
//

#include "Enemy1Sprite.h"


Enemy1Sprite * Enemy1Sprite::create(CCSpriteFrame * pSpriteFrame)
{
    Enemy1Sprite * pobSprite = new Enemy1Sprite;
    if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->life = ENEMY_MAXLIFE;
        pobSprite->autorelease();
        return pobSprite;
    }
    
    CC_SAFE_DELETE(pobSprite);
    
    return NULL;
}