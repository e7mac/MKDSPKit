//
//  FFT.h
//  DSPLibrary
//
//  Created by Mayank on 11/4/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__FFT__
#define __DSPLibrary__FFT__

#include <iostream>
#include <Accelerate/Accelerate.h>

class FFT {
private:
    int _N;
    int _logN;
    FFTSetup _fftSetup;
    float *_x;
    float *_y;
    // We need complex buffers in two different formats!
    DSPComplex *_tempComplex;
    DSPSplitComplex _tempSplitComplex;
    // For polar coordinates
    float *_intermediateMag;
    float *_intermediatePhase;
    float *_mag;
    float *_phase;
    void setN(int withN);
public:
    FFT(int nPointLength);

    void setSignal();
    
    void forwardFFT();
    void inverseFFT();
};



#endif /* defined(__DSPLibrary__FFT__) */
