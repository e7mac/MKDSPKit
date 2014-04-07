//
//  PeakDetector.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "PeakDetector.h"
#include <math.h>

PeakDetector::PeakDetector() {
    // default to pass-through
    _a1 = 0; // relese coeffs
    _b0 = 1;
    reset();
}

void PeakDetector::setTau(double tau, double fs) {
    _a1 = exp( -1.0 / ( tau * fs ) );
    _b0 = 1 - _a1;
}

void PeakDetector::reset() { // reset filter state
    _levelEstimate = 0;
}

void PeakDetector::process (double input, double& output) {
    _levelEstimate += _b0 * ( fabs( input ) - _levelEstimate );
    output = _levelEstimate;
}

void PeakDetector::process (float input, float& output) {
    _levelEstimate += _b0 * ( fabs( input ) - _levelEstimate );
    output = _levelEstimate;
}
