//
//  GameLayer.h
//  airplanedemo
//
//  Created by Leo Lin on 11/9/13.
//
//

#ifndef airplanedemo_GameLayer_h
#define airplanedemo_GameLayer_h

#include "cocos2d.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"

USING_NS_CC;

class GameLayer : public CCLayer
{
public:
    GameLayer(void);
    ~GameLayer(void);
    LAYER_CREATE_FUNC(GameLayer);
    virtual bool init();
    
    void backgroundMove(float dt);
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    void registerWithTouchDispatcher();
    
public:
    CCSprite * background1;
    CCSprite * background2;
    
    PlaneLayer * planeLayer;
    BulletLayer * bulletLayer;
};


#endif
