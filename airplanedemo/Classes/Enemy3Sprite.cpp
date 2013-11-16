//
//  Enemy3Sprite.cpp
//  airplanedemo
//
//  Created by Leo Lin on 11/16/13.
//
//

#include "Enemy3Sprite.h"


Enemy3Sprite * Enemy3Sprite::create(CCSpriteFrame * pSpriteFrame)
{
    Enemy3Sprite * pobSprite = new Enemy3Sprite;
    if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->life = ENEMY3_MAXLIFE;
        pobSprite->autorelease();
        return pobSprite;
    }
    
    CC_SAFE_DELETE(pobSprite);
    
    return NULL;
}