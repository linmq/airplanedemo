//
//  Enemy2Sprite.h
//  airplanedemo
//
//  Created by Leo Lin on 11/16/13.
//
//

#ifndef airplanedemo_Enemy2Sprite_h
#define airplanedemo_Enemy2Sprite_h

#include "cocos2d.h"
USING_NS_CC;

const int ENEMY2_MAXLIFE=2;

class Enemy2Sprite : public CCSprite
{
public:

    static Enemy2Sprite * create(CCSpriteFrame * pSpriteFrame);
    
public:

    int life;
};

#endif
