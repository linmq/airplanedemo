//
//  PlaneLayer.h
//  airplanedemo
//
//  Created by Leo Lin on 11/10/13.
//
//

#ifndef airplanedemo_PlaneLayer_h
#define airplanedemo_PlaneLayer_h

#include "cocos2d.h"

USING_NS_CC;

const int AIRPLANE=747;

class PlaneLayer : public CCLayer
{
public:
    PlaneLayer(void);
    ~PlaneLayer(void);
    
    static PlaneLayer * create();
    
    void MoveTo(CCPoint location);
    
    virtual bool init();
    
    void Blowup(int passScore);
    
    void RemovePlane();
    
public:
    
    static PlaneLayer * sharePlane;
    
    bool isAlive;
    
    int score;
};

#endif
