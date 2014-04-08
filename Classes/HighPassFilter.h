//
//  HighPassFilter.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__HighPassFilter__
#define __DSPLibrary__HighPassFilter__

#include <iostream>
#include "Biquad.h"

class HighPassFilter {
public:
    double _coefs[6];
    Biquad _eq;
public:
    HighPassFilter();
    HighPassFilter(int cutoff, int fs);
    void reset();
    void process (float input, float& output);
};


#endif /* defined(__DSPLibrary__HighPassFilter__) */
