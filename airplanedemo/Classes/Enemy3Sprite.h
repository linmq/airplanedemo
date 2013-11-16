//
//  Enemy3Sprite.h
//  airplanedemo
//
//  Created by Leo Lin on 11/16/13.
//
//

#ifndef airplanedemo_Enemy3Sprite_h
#define airplanedemo_Enemy3Sprite_h

#include "cocos2d.h"
USING_NS_CC;

const int ENEMY3_MAXLIFE=2;

class Enemy3Sprite : public CCSprite
{
public:

    static Enemy3Sprite * create(CCSpriteFrame * pSpriteFrame);
    
public:

    int life;
};

#endif
