//
//  Compressor.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "Compressor.h"

Compressor::Compressor(float threshold,float ratio, int srate)
{
    _threshold = threshold;
    _ratio = ratio;
    _raisedTo = 1/(_ratio-1);
    _levelEstimator.setTau(0.05, srate);
    _logThreshold = dB(_threshold);
}

void Compressor::setupCompressor(float threshold,float ratio, int srate)
{
    _threshold = threshold;
    _ratio = ratio;
    _raisedTo = 1/(_ratio-1);
    _levelEstimator.setTau(0.05, srate);
    _logThreshold = dB(_threshold);
}

void Compressor::process(float input, float&output)
{
    float levelEstimate;
    _levelEstimator.process(input, levelEstimate);
    float logLevel = dB(levelEstimate);
    if (logLevel < _logThreshold) {
        output = input;
    } else {
        float dbGain = (logLevel - _logThreshold) / (1/_ratio -1);
        output = input * dB2lin(dbGain);
    }
}

