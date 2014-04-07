//
//  PeakDetector.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__PeakDetector__
#define __DSPLibrary__PeakDetector__

#include <iostream>

class PeakDetector {
public:
    double	_b0, _a1, _levelEstimate;
public:
    PeakDetector();
	void setTau(double tau, double fs);
    void reset();
	void process (float input, float& output);
	void process (double input, double& output);
};


#endif /* defined(__DSPLibrary__PeakDetector__) */
