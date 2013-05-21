//
//  CCGestureRecognizer.cpp
//
//  Created by Andres Pagliano
//  Copyright 2013 LavandaInk. All rights reserved.
//

#include "CCGestureRecognizer.h"


//--------------------------------------------------------------------------------------------------
// CCGestureRecognizer
//--------------------------------------------------------------------------------------------------

bool CCGestureRecognizer::init(cocos2d::CCObject *target, cocos2d::SEL_GestureHandler sel)
{
    _target = target;
    _selector = sel;
    _state = CCGestureRecognizerStatePossible;
    _delegate = 0;

    return true;
}

CCGestureRecognizer *CCGestureRecognizer::create(CCObject *target, SEL_GestureHandler sel)
{
    CCGestureRecognizer * gr = new CCGestureRecognizer();
    gr->init(target, sel);
    gr->autorelease();

    return gr;
}

CCGestureRecognizerState CCGestureRecognizer::getState()
{
    return _state;
}

CCPoint CCGestureRecognizer::locationInView()
{
    // TODO

    return CCPoint(0, 0);
}

int CCGestureRecognizer::getNumberOfTouches()
{
    // TODO

     return 0;
}

void CCGestureRecognizer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCGestureRecognizer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCGestureRecognizer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCGestureRecognizer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

//--------------------------------------------------------------------------------------------------
// CCPinchGestureRecognizer
//--------------------------------------------------------------------------------------------------

float CCPinchGestureRecognizer::getScale()
{
    return 0;
}

void CCPinchGestureRecognizer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
}

void CCPinchGestureRecognizer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
}

void CCPinchGestureRecognizer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
}

void CCPinchGestureRecognizer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
}
