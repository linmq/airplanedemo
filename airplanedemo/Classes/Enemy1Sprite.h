//
//  Enemy1Sprite.h
//  airplanedemo
//
//  Created by Leo Lin on 11/15/13.
//
//

#ifndef airplanedemo_Enemy_h
#define airplanedemo_Enemy_h

#include "cocos2d.h"
USING_NS_CC;

const int ENEMY_MAXLIFE=1;

class Enemy1Sprite : public CCSprite
{
public:

    static Enemy1Sprite * create(CCSpriteFrame * pSpriteFrame);
    
public:

    int life;
};

#endif
