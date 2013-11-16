//
//  Enemy2Layer.h
//  airplanedemo
//
//  Created by Leo Lin on 11/16/13.
//
//

#ifndef airplanedemo_Enemy2Layer_h
#define airplanedemo_Enemy2Layer_h

#include "cocos2d.h"
#include "Enemy2Sprite.h"

USING_NS_CC;

class Enemy2Layer : public CCLayer
{
public:
    Enemy2Layer(void);
    ~Enemy2Layer(void);
    LAYER_CREATE_FUNC(Enemy2Layer);
    
    virtual bool init();
    
    void AddEnemy2(float dt);
    void enemy2MoveFinished(CCNode* pSender);
    void enemy2Blowup(Enemy2Sprite* enemy2);
    void RemoveEnemy2(CCNode* pTarget, void* data);
    void RemoveAllEnemy2();
    
public:
    CCArray* m_pAllEnemy2;
    CCSpriteFrame * enemy2SpriteFrame;
    
};


#endif
