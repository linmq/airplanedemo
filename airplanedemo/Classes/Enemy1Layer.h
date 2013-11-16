//
//  Enemy1Layer.h
//  airplanedemo
//
//  Created by Leo Lin on 11/15/13.
//
//

#ifndef airplanedemo_Enemy1Layer_h
#define airplanedemo_Enemy1Layer_h

#include "cocos2d.h"
#include "Enemy1Sprite.h"

USING_NS_CC;

class Enemy1Layer : public CCLayer
{
public:
    Enemy1Layer(void);
    ~Enemy1Layer(void);
    LAYER_CREATE_FUNC(Enemy1Layer);
    
    virtual bool init();
    
    void AddEnemy1(float dt);
    void enemy1MoveFinished(CCNode* pSender);
    void enemy1Blowup(Enemy1Sprite* enemy1);
    void RemoveEnemy1(CCNode* pTarget, void* data);
    void RemoveAllEnemy1();
    
public:
    CCArray* m_pAllEnemy1;
    CCSpriteFrame * enemy1SpriteFrame;
    
};


#endif
