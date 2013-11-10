//
//  GameScene.h
//  airplanedemo
//
//  Created by Leo Lin on 11/8/13.
//
//

#ifndef airplanedemo_GameScene_h
#define airplanedemo_GameScene_h

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

class GameScene : public CCScene
{
public:
    
    GameScene(void);
    ~GameScene(void);
    
    SCENE_CREATE_FUNC(GameScene);
    
    virtual bool init();
    GameLayer * _gameLayer;
};

#endif
