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

#include "CCGestureRecognizer.h"

#include <cmath>

//--------------------------------------------------------------------------------------------------
// Helpers
//--------------------------------------------------------------------------------------------------

namespace
{

inline float distance(const CCPoint &p1, const CCPoint &p2)
{
    using namespace std;

    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

}

//--------------------------------------------------------------------------------------------------
// CCGestureRecognizer
//--------------------------------------------------------------------------------------------------

bool CCGestureRecognizer::init(cocos2d::CCObject *target, cocos2d::SEL_GestureHandler sel)
{
    _target = target;
    _selector = sel;
    _delegate = 0;
    _enabled = true;
    reset();

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
    return CCPoint(0, 0);
}

int CCGestureRecognizer::getNumberOfTouches()
{
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

void CCGestureRecognizer::setPoint(CCSet *pTouches, CCPoint &p1)
{
    p1 = dynamic_cast<CCTouch*>(*pTouches->begin())->getLocationInView();
}

void CCGestureRecognizer::setPoint(CCSet *pTouches, CCPoint &p1, CCPoint &p2)
{
    for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it) {
        if (it == pTouches->begin()) {
            p1 = dynamic_cast<CCTouch*>(*it)->getLocationInView();
        } else {
            p2 = dynamic_cast<CCTouch*>(*it)->getLocationInView();
            break;
        }
    }
}

void CCGestureRecognizer::reset()
{
    _state = CCGestureRecognizerStatePossible;
    _p1Begin = CCPoint(0, 0);
    _p2Begin = CCPoint(0, 0);
    _p1 = CCPoint(0, 0);
    _p2 = CCPoint(0, 0);
}

//--------------------------------------------------------------------------------------------------
// CCPinchGestureRecognizer
//--------------------------------------------------------------------------------------------------

float CCPinchGestureRecognizer::getScale()
{
    float dBegin = distance(_p1Begin, _p2Begin);
    float d = distance(_p1, _p2);

    //CCLOG("SCALE FACTOR 1x1 %f 1x2 %f", _p1Begin.x, _p1.x);
    //CCLOG("SCALE FACTOR 1y1 %f 1y2 %f", _p1Begin.y, _p1.y);
    //CCLOG("SCALE FACTOR 2x1 %f 2x2 %f", _p2Begin.x, _p2.x);
    //CCLOG("SCALE FACTOR 2y1 %f 2y2 %f", _p2Begin.y, _p2.y);

    return std::pow(2, (d - dBegin)/100);
}

void CCPinchGestureRecognizer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);

    // Nothing to do
}

void CCPinchGestureRecognizer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pEvent);

    if (!_enabled) {
        return;
    }

    if (pTouches->count() == 2) {
        if (_state == CCGestureRecognizerStatePossible) {
            if (_delegate && !_delegate->shouldBegin(this)) {
                return;
            }

            _state = CCGestureRecognizerStateBegan;
            setPoint(pTouches, _p1Begin, _p2Begin);
            setPoint(pTouches, _p1, _p2);
            notifyTarget();
        } else if (_state == CCGestureRecognizerStateBegan || _state == CCGestureRecognizerStateChanged) {
            _state = CCGestureRecognizerStateChanged;
            setPoint(pTouches, _p1, _p2);
            notifyTarget();
        }
    }
}

void CCPinchGestureRecognizer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pEvent);

    if (!_enabled) {
        return;
    }

    if (pTouches->count() == 2) {
        if (_state == CCGestureRecognizerStateBegan || _state == CCGestureRecognizerStateChanged) {
            _state = CCGestureRecognizerStateEnded;
            setPoint(pTouches, _p1, _p2);
            notifyTarget();
            reset();
        }
    }
}

void CCPinchGestureRecognizer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pEvent);

    if (!_enabled) {
        return;
    }

    if (pTouches->count() == 2) {
        if (_state == CCGestureRecognizerStateBegan || _state == CCGestureRecognizerStateChanged) {
            _state = CCGestureRecognizerStateCancelled;
            setPoint(pTouches, _p1, _p2);
            notifyTarget();
            reset();
        }
    }
}


//--------------------------------------------------------------------------------------------------
// CCTapGestureRecognizer
//--------------------------------------------------------------------------------------------------

CCPoint CCTapGestureRecognizer::locationInView()
{
    return _p1;
}

void CCTapGestureRecognizer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);

    if (!_enabled) {
        return;
    }

    if (_delegate && !_delegate->shouldBegin(this)) {
        return;
    }

    if (pTouches->count() == 1) {
        if (_state == CCGestureRecognizerStatePossible) {
            _state = CCGestureRecognizerStateRecognized;
            setPoint(pTouches, _p1);
            notifyTarget();
        }
    }

}

void CCTapGestureRecognizer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCTapGestureRecognizer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}

void CCTapGestureRecognizer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);
}


//--------------------------------------------------------------------------------------------------
// CCPanGestureRecognizer
//--------------------------------------------------------------------------------------------------

CCPoint CCPanGestureRecognizer::locationInView()
{
    return _p1;
}

void CCPanGestureRecognizer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pTouches);
    CC_UNUSED_PARAM(pEvent);

    // Nothing to do
}

void CCPanGestureRecognizer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pEvent);

    if (!_enabled) {
        return;
    }

    // For simplicity we only use the first touch
    if (pTouches->count() >= 1) {
        if (_state == CCGestureRecognizerStatePossible) {
            if (_delegate && !_delegate->shouldBegin(this)) {
                return;
            }

            _state = CCGestureRecognizerStateBegan;
            setPoint(pTouches, _p1Begin);
            setPoint(pTouches, _p1);
            notifyTarget();
        } else if (_state == CCGestureRecognizerStateBegan || _state == CCGestureRecognizerStateChanged) {
            _state = CCGestureRecognizerStateChanged;
            setPoint(pTouches, _p1);
            notifyTarget();
        }
    }
}

void CCPanGestureRecognizer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pEvent);

    if (!_enabled) {
        return;
    }

    if (pTouches->count() >= 1) {
        if (_state == CCGestureRecognizerStateBegan || _state == CCGestureRecognizerStateChanged) {
            _state = CCGestureRecognizerStateEnded;
            setPoint(pTouches, _p1);
            notifyTarget();
            reset();
        }
    }
}

void CCPanGestureRecognizer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    CC_UNUSED_PARAM(pEvent);

    if (!_enabled) {
        return;
    }

    if (pTouches->count() >= 1) {
        if (_state == CCGestureRecognizerStateBegan || _state == CCGestureRecognizerStateChanged) {
            _state = CCGestureRecognizerStateCancelled;
            setPoint(pTouches, _p1);
            notifyTarget();
            reset();
        }
    }
}

