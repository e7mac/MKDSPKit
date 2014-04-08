//
//  ParametricFilter.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__ParametricFilter__
#define __DSPLibrary__ParametricFilter__

#include <iostream>
#include "Biquad.h"

class ParametricFilter {
public:
    double _coefs[6];
    Biquad _eq;
public:
    ParametricFilter(int center, int gain, int q, int fs);
    void reset();
    void process (float input, float& output);
};


#endif /* defined(__DSPLibrary__ParametricFilter__) */
