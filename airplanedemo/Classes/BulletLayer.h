//
//  BulletLayer.h
//  airplanedemo
//
//  Created by Leo Lin on 11/11/13.
//
//

#ifndef airplanedemo_BulletLayer_h
#define airplanedemo_BulletLayer_h

#include "cocos2d.h"

USING_NS_CC;

class BulletLayer : public CCLayer
{
public:
    BulletLayer(void);
    ~BulletLayer(void);
    
    LAYER_CREATE_FUNC(BulletLayer);
    
    virtual bool init(void);
    
    void AddBullet(float dt);
    
    void StartShoot(float delay=0.0f);
    
public:
    CCSpriteBatchNode* bulletBatchNode;
    
};

#endif
