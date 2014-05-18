//
//  Reverse.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__Reverse__
#define __DSPLibrary__Reverse__

#include <iostream>
#include "SimpleDelayLine.h"

class Reverse {
public:
    float _amp;
    SimpleDelayLine _delay;
public:
    Reverse(float time, float amp, int fs);
    void process (float input, float& output);
};


#endif /* defined(__DSPLibrary__Reverse__) */
