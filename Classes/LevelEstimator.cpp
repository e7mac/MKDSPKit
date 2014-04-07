//
//  LevelEstimator.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "LevelEstimator.h"

LevelEstimator::LevelEstimator()
{
    // default to pass-through
    _a1 = 0; // relese coeffs
    _b0 = 1;
    reset();
}

void LevelEstimator::setTau(double tau, double fs)
{
    _a1 = exp( -1.0 / ( tau * fs ) );
    _b0 = 1 - _a1;
}

void LevelEstimator::reset()
{ // reset filter state
    _levelEstimate = 0;
}

void LevelEstimator::process (double input, double& output)
{
    _levelEstimate += _b0 * ( fabs( input ) - _levelEstimate );
    output = _levelEstimate;
}

void LevelEstimator::process (float input, float& output)
{
    _levelEstimate += _b0 * ( fabs( input ) - _levelEstimate );
    output = _levelEstimate;
}
