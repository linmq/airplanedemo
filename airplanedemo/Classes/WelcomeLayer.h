//
//  WelcomeLayer.h
//  airplanedemo
//
//  Created by Leo Lin on 11/9/13.
//
//

#ifndef airplanedemo_WelcomeLayer_h
#define airplanedemo_WelcomeLayer_h

#include "cocos2d.h"

USING_NS_CC;

class WelcomeLayer : public CCLayer
{
public:
    WelcomeLayer(void);
    ~WelcomeLayer(void);
    
    virtual bool init();
    
    LAYER_CREATE_FUNC(WelcomeLayer);
    
    void loadingDone(CCNode* pNode);
    
    //virtual void keyBackClicked(); //Android返回键
    
//    bool isHaveSaveFile();
    
  //  void getHighestHistoryScore();
};

#endif
