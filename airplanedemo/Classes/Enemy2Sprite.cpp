//
//  Enemy2Sprite.cpp
//  airplanedemo
//
//  Created by Leo Lin on 11/16/13.
//
//

#include "Enemy2Sprite.h"


Enemy2Sprite * Enemy2Sprite::create(CCSpriteFrame * pSpriteFrame)
{
    Enemy2Sprite * pobSprite = new Enemy2Sprite;
    if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->life = ENEMY2_MAXLIFE;
        pobSprite->autorelease();
        return pobSprite;
    }
    
    CC_SAFE_DELETE(pobSprite);
    
    return NULL;
}