//
//  CCGestureRecognizer.cpp
//
//  Created by Andres Pagliano
//  Copyright 2013 LavandaInk. All rights reserved.
//

#include "CCGestureRecognizer.h"

#include <cmath>

//--------------------------------------------------------------------------------------------------
// CCGestureRecognizer
//--------------------------------------------------------------------------------------------------

bool CCGestureRecognizer::init(cocos2d::CCObject *target, cocos2d::SEL_GestureHandler sel)
{
    _target = target;
    _selector = sel;
    _state = CCGestureRecognizerStatePossible;
    _delegate = 0;
    _enabled = true;

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

void CCGestureRecognizer::notifyTarget()
{
    if (_target && _selector) {
        (_target->*_selector)(this);
    }
}

//--------------------------------------------------------------------------------------------------
// CCPinchGestureRecognizer
//--------------------------------------------------------------------------------------------------


inline float distance(const CCPoint &p1, const CCPoint &p2)
{
    using namespace std;

    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

float CCPinchGestureRecognizer::getScale()
{
    float dStart = distance(_p1Start, _p2Start);
    float d = distance(_p1, _p2);

    //CCLOG("SCALE FACTOR d1 %f", dStart);
    //CCLOG("SCALE FACTOR d2 %f", d);

    return std::pow(2, (d - dStart)/200);
}

void CCPinchGestureRecognizer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    //CCLOG("SCALE FACTOR BEGAN %i", pTouches->count());

    if (!_enabled) {
        return;
    }

    if (_delegate && !_delegate->shouldBegin(this)) {
        return;
    }

    if (_state != CCGestureRecognizerStatePossible) {
        return;
    }

    if (pTouches->count() == 2) {
        _state = CCGestureRecognizerStateBegan;
        set(pTouches, _p1Start, _p2Start);
        set(pTouches, _p1, _p2);
        notifyTarget();
    }
}

void CCPinchGestureRecognizer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    //CCLOG("SCALE FACTOR MOVED %i", pTouches->count());

    if (!_enabled) {
        return;
    }

    if (pTouches->count() == 2) {
        if (_state == CCGestureRecognizerStatePossible) {
            ccTouchesBegan(pTouches, pEvent);
        } else if (_state == CCGestureRecognizerStateBegan || _state == CCGestureRecognizerStateChanged) {
            _state = CCGestureRecognizerStateChanged;
            set(pTouches, _p1, _p2);
            notifyTarget();
        }
    }
}

void CCPinchGestureRecognizer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    //CCLOG("SCALE FACTOR ENDED %i", pTouches->count());

    if (!_enabled) {
        return;
    }

    if (_state != CCGestureRecognizerStateBegan || _state != CCGestureRecognizerStateChanged) {
        return;
    }

    if (pTouches->count() == 2) {
        _state = CCGestureRecognizerStateEnded;
        set(pTouches, _p1, _p2);
        notifyTarget();
        reset();
    }
}

void CCPinchGestureRecognizer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    //CCLOG("SCALE FACTOR CANCELLED %i", pTouches->count());

    if (!_enabled) {
        return;
    }

    if (_state != CCGestureRecognizerStateBegan || _state != CCGestureRecognizerStateChanged) {
        return;
    }

    if (pTouches->count() == 2) {
        _state = CCGestureRecognizerStateCancelled;
        set(pTouches, _p1, _p2);
        notifyTarget();
        reset();
    }
}

void CCPinchGestureRecognizer::set(CCSet *pTouches, CCPoint &p1, CCPoint &p2)
{
    for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it) {
        if (it == pTouches->begin()) {
            p1 = dynamic_cast<CCTouch*>(*it)->getLocationInView();
        } else {
            p2 = dynamic_cast<CCTouch*>(*it)->getLocationInView();
        }
    }
}

void CCPinchGestureRecognizer::reset()
{
    _state = CCGestureRecognizerStatePossible;
    _p1Start = CCPoint(0, 0);
    _p2Start = CCPoint(0, 0);
    _p1 = CCPoint(0, 0);
    _p2 = CCPoint(0, 0);
}
