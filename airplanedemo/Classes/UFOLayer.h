//
//  UFOLayer.h
//  airplanedemo
//
//  Created by Leo Lin on 11/17/13.
//
//

#ifndef airplanedemo_UFOLayer_h
#define airplanedemo_UFOLayer_h

#include "cocos2d.h"

USING_NS_CC;

class UFOLayer : public CCLayer
{
public:
    
    UFOLayer(void);
    
    ~UFOLayer(void);
    
    virtual bool init();
    
    LAYER_CREATE_FUNC(UFOLayer);
    
    void AddMutiBullets(float dt);
    
    void mutiBulletsMoveFinished(CCNode* pSender);
    
    void AddBigBoom(float dt);
    
    void bigBoomMoveFinished(CCNode* pSender);
    
    void RemoveMutiBullets(CCSprite* mutiBullets);
    
    void RemoveBigBoom(CCSprite* bigBoom);
    
public:
    
    CCArray* m_pAllMutiBullets;
    
    CCArray* m_pAllBigBoom;
};


#endif
