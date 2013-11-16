//
//  Enemy3Layer.h
//  airplanedemo
//
//  Created by Leo Lin on 11/16/13.
//
//

#ifndef airplanedemo_Enemy3Layer_h
#define airplanedemo_Enemy3Layer_h

#include "cocos2d.h"
#include "Enemy3Sprite.h"

USING_NS_CC;

class Enemy3Layer : public CCLayer
{
public:
    Enemy3Layer(void);
    ~Enemy3Layer(void);
    LAYER_CREATE_FUNC(Enemy3Layer);
    
    virtual bool init();
    
    void AddEnemy3(float dt);
    void enemy3MoveFinished(CCNode* pSender);
    void enemy3Blowup(Enemy3Sprite* enemy3);
    void RemoveEnemy3(CCNode* pTarget, void* data);
    void RemoveAllEnemy3();
    
public:
    CCArray* m_pAllEnemy3;
    CCSpriteFrame* enemy3SpriteFrame_1;
    CCSpriteFrame* enemy3SpriteFrame_2;
    
};


#endif
