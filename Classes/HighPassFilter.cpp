//
//  HighPassFilter.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "HighPassFilter.h"
#include "DSPUtilities.h"

HighPassFilter::HighPassFilter(int cutoff, int fs)
{
    DSPUtilities::designFirstOrderHighpass(_coefs, cutoff, fs);
    _eq.setCoefs(_coefs);
}
void HighPassFilter::reset()
{
}
void HighPassFilter::process (float input, float& output)
{
    _eq.process(input, output);
}
