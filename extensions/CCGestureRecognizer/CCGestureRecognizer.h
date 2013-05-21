//
//  CCGestureRecognizer.h
//
//  Created by Andres Pagliano
//  Copyright 2013 LavandaInk. All rights reserved.
//

#ifndef CC_GESTURE_RECOGNIZER_H
#define CC_GESTURE_RECOGNIZER_H

#include "cocos2d.h"

using namespace cocos2d;

class CCGestureRecognizer;

/**
 * The states a gesture recognizer
 */
enum CCGestureRecognizerState
{
    CCGestureRecognizerStatePossible,
    CCGestureRecognizerStateBegan,
    CCGestureRecognizerStateChanged,
    CCGestureRecognizerStateEnded,
    CCGestureRecognizerStateCancelled,
    CCGestureRecognizerStateFailed,
    CCGestureRecognizerStateRecognized = CCGestureRecognizerStateEnded
};


/**
 * Delegates of a gesture recognizer
 */
class CCGestureRecognizerDelegate
{
public:

    // Optional
    virtual bool shouldBegin(CCGestureRecognizer *recognizer)
    {
        CC_UNUSED_PARAM(recognizer);
        return true;
    }

    // Optional
    virtual bool shouldReceiveTouch(CCGestureRecognizer *recognizer, CCTouch *touch)
    {
        CC_UNUSED_PARAM(recognizer);
        CC_UNUSED_PARAM(touch);
        return true;
    }

    // Optional
    virtual bool shouldRecognizeSimultaneously(CCGestureRecognizer *recognizer1,
                                               CCGestureRecognizer *recognizer2)
    {
        CC_UNUSED_PARAM(recognizer1);
        CC_UNUSED_PARAM(recognizer2);
        return true;
    }

    virtual ~CCGestureRecognizerDelegate() { }
};

/**
 * CCGestureRecognizer is an abstract base class for concrete gesture-recognizer classes.
 */
class CCGestureRecognizer : public CCObject, public CCTouchDelegate
{
public:
    virtual bool init(CCObject *target, SEL_GestureHandler sel);

    static CCGestureRecognizer *create(CCObject *target, SEL_GestureHandler sel);

    virtual CCGestureRecognizerState getState();

    virtual CCPoint locationInView();

    virtual int getNumberOfTouches();

    CC_SYNTHESIZE(bool, _enabled, Enabled)
    CC_SYNTHESIZE(CCGestureRecognizerDelegate *, _delegate, Delegate)

    // CCTouchDelegate
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

protected:
    CCObject *_target;
    SEL_GestureHandler _selector;
    CCGestureRecognizerState _state;
};


class CCPinchGestureRecognizer : public CCGestureRecognizer
{
public:

    float getScale();

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

private:
    CCPoint _p1Start;
    CCPoint _p2Start;
    CCPoint _p1End;
    CCPoint _p2End;
};

class CCTapGestureRecognizer : public CCGestureRecognizer
{
};

class CCPanGestureRecognizer : public CCGestureRecognizer
{
};

class CCRotationGestureRecognizer : public CCGestureRecognizer
{
};

class CCSwipeGestureRecognizer : public CCGestureRecognizer
{
};

class CCLongPressGestureRecognizer : public CCGestureRecognizer
{
};

#endif //CC_GESTURE_RECOGNIZER_H
