//
//  PitchClassEstimator.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__PitchClassEstimator__
#define __DSPLibrary__PitchClassEstimator__

#include <iostream>
#include "SimpleDelayLine.h"

class PitchClassEstimator {
private:
    float *previousSpectrum;
    bool bufferIsFull();
    void process();
    void window();
    void zeroPad();
    void fft();
    void magfft();
    void bin();
    void maxOfBin();
public:
    SimpleDelayLine delayLine;
    PitchClassEstimator(int bufferTime, int sampleRate);
    void write(float sample);

    float pitchEstimate;
};


#endif /* defined(__DSPLibrary__PitchClassEstimator__) */
