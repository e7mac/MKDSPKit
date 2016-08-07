//
//  LowPassFilter.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "LowPassFilter.h"
#include "DSPUtilities.h"

LowPassFilter::LowPassFilter(int cutoff, int fs)
{
  setCutoff(cutoff, fs);
}

void LowPassFilter::reset()
{
}
void LowPassFilter::process (float input, float& output)
{
    _eq.process(input, output);
}

void LowPassFilter::setCutoff(int cutoff, int fs)
{
    DSPUtilities::designFirstOrderLowpass(_coefs, cutoff, fs);
    _eq.setCoefs(_coefs);
}