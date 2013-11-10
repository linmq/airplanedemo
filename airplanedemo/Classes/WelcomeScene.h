//
//  WelcomeScene.h
//  airplanedemo
//
//  Created by Leo Lin on 11/9/13.
//
//

#ifndef airplanedemo_WelcomeScene_h
#define airplanedemo_WelcomeScene_h

#include "cocos2d.h"
#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"

class WelcomeScene : public CCScene
{
public:
    WelcomeScene(void);
    ~WelcomeScene(void);
    
    virtual bool init();
    
    SCENE_CREATE_FUNC(WelcomeScene);
    
    void PreloadMusic();
    
public:
    WelcomeLayer * _welcomeLayer;
    
};

#endif
