//
//  GameOverLayer.h
//  airplanedemo
//
//  Created by Leo Lin on 11/21/13.
//
//

#ifndef airplanedemo_GameOverLayer_h
#define airplanedemo_GameOverLayer_h

#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public CCLayer
{
public:
	GameOverLayer(void);
    
	~GameOverLayer(void);
    
	virtual bool init();
    
    static GameOverLayer* create(int passScore);
    
    void menuBackCallback(CCObject* pSender);
    
    void beginChangeHighestScore(CCNode* pNode);
    
public:
    
    int score;
    
    static int highestHistoryScore;
    
    CCLabelBMFont* highestScore;
};


#endif
