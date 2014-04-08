//
//  ParametricFilter.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "ParametricFilter.h"
#include "DSPUtilities.h"

ParametricFilter::ParametricFilter(int center, int gain, int q, int fs)
{
    DSPUtilities::designParametric(_coefs, center, gain, q, fs);
    _eq.setCoefs(_coefs);
}
void ParametricFilter::reset()
{
}
void ParametricFilter::process (float input, float& output)
{
    _eq.process(input, output);
}
