//
//  PitchShift.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__PitchShift__
#define __DSPLibrary__PitchShift__

#include <iostream>
#include "SimpleDelayLine.h"

class PitchShift {
public:
    float _speed;
    SimpleDelayLine _delay;
    int _timeCounter;
public:
    PitchShift(float speed, int bufferTimeLength, int fs);
    void process (float input, float& output);
};


#endif /* defined(__DSPLibrary__PitchShift__) */
