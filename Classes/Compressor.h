//
//  Compressor.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__Compressor__
#define __DSPLibrary__Compressor__

#include <iostream>
#include <math.h>
#include "LevelEstimator.h"

#define dB(x) 20.0*((x) > 0.00001 ? log10(x) : log10(0.00001))

#define dB2lin(x) powf (10.0,(x) / 20.0 )

class Compressor {
protected:
    float _threshold,_logThreshold,_ratio,_raisedTo;
    LevelEstimator _levelEstimator;
public:
    Compressor(){};
    Compressor(float threshold,float ratio, int srate);
    void setupCompressor(float threshold,float ratio, int srate);
    void process(float input, float&output);
};


#endif /* defined(__DSPLibrary__Compressor__) */
