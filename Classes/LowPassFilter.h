//
//  LowPassFilter.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__LowPassFilter__
#define __DSPLibrary__LowPassFilter__

#include <iostream>
#include "Biquad.h"

class LowPassFilter {
public:
    double _coefs[6];
    Biquad _eq;
public:
    LowPassFilter();
    LowPassFilter(int cutoff, int fs);
    void reset();
    void process (float input, float& output);
};


#endif /* defined(__DSPLibrary__LowPassFilter__) */
