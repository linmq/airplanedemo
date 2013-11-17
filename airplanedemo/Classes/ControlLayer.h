//
//  ControlLayer.h
//  airplanedemo
//
//  Created by Leo Lin on 11/17/13.
//
//

#ifndef airplanedemo_ControlLayer_h
#define airplanedemo_ControlLayer_h

#include "cocos2d.h"

USING_NS_CC;

const int MAX_SCORE=1000000000;

class ControlLayer : public CCLayer
{
public:
 
    ControlLayer(void);
 
    ~ControlLayer(void);
 
    virtual bool init();
 
    LAYER_CREATE_FUNC(ControlLayer);
 
    void menuPauseCallback(CCObject* pSender);
    
public:
    
    CCMenuItemImage* pPauseItem;
};


#endif
