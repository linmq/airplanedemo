//
//  WelcomeScene.cpp
//  airplanedemo
//
//  Created by Leo Lin on 11/9/13.
//
//

#include "WelcomeScene.h"

WelcomeScene :: WelcomeScene(void)
{
    _welcomeLayer = NULL;
}

WelcomeScene::~WelcomeScene()
{
}

bool WelcomeScene::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCScene::init());
        _welcomeLayer = WelcomeLayer::create();
        CC_BREAK_IF(!_welcomeLayer);
        this->addChild(_welcomeLayer);
        PreloadMusic();
        bRet = true;
    } while (0);
    
    return bRet;
}

void WelcomeScene::PreloadMusic()
{
    
}