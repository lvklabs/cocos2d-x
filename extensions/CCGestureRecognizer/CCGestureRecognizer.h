/****************************************************************************
Copyright (c) 2010 cocos2d-x.org
Copyright (c) 2013 Andres Pagliano

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

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
 *
 * NOTE: work in progress!
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

    CCPoint _p1Begin;
    CCPoint _p2Begin;
    CCPoint _p1;
    CCPoint _p2;

    void notifyTarget();
    void setPoint(CCSet *pTouches, CCPoint &p1);
    void setPoint(CCSet *pTouches, CCPoint &p1, CCPoint &p2);
    void reset();
};


/**
 * @brief The CCPinchGestureRecognizer class
 *
 * NOTE: work in progress!
 */
class CCPinchGestureRecognizer : public CCGestureRecognizer
{
public:

    float getScale();

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
};

/**
 * @brief The CCTapGestureRecognizer class
 *
 * NOTE: work in progress!
 */
class CCTapGestureRecognizer : public CCGestureRecognizer
{
public:
    virtual CCPoint locationInView();

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
};

/**
 * @brief The CCPanGestureRecognizer class
 *
 * NOTE: work in progress!
 */
class CCPanGestureRecognizer : public CCGestureRecognizer
{
public:
    virtual CCPoint locationInView();

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
};

/**
 * NOT IMPLEMENTED
 */
class CCRotationGestureRecognizer : public CCGestureRecognizer
{
    // TODO
};

/**
 * NOT IMPLEMENTED
 */
class CCSwipeGestureRecognizer : public CCGestureRecognizer
{
    // TODO
};

/**
 * NOT IMPLEMENTED
 */
class CCLongPressGestureRecognizer : public CCGestureRecognizer
{
    // TODO
};

#endif //CC_GESTURE_RECOGNIZER_H
