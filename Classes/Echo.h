//
//  Echo.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__Echo__
#define __DSPLibrary__Echo__

#include <iostream>
#include "SimpleDelayLine.h"

class Echo {
public:
    float _amp;
    SimpleDelayLine _delay;
public:
    Echo(float time, float amp, int fs);
    void process (float input, float& output);
};


#endif /* defined(__DSPLibrary__Echo__) */
