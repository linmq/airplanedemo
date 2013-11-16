//
//  Enemy1Sprite.h
//  airplanedemo
//
//  Created by Leo Lin on 11/15/13.
//
//

#ifndef airplanedemo_Enemy1Sprite_h
#define airplanedemo_Enemy1Sprite_h

#include "cocos2d.h"
USING_NS_CC;

const int ENEMY1_MAXLIFE=1;

class Enemy1Sprite : public CCSprite
{
public:

    static Enemy1Sprite * create(CCSpriteFrame * pSpriteFrame);
    
public:

    int life;
};

#endif
