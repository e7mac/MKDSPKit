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
    int N;
    int logN;
    FFTSetup fftSetup;
    float *x;
    float *y;
    // We need complex buffers in two different formats!
    DSPComplex *tempComplex;
    DSPSplitComplex tempSplitComplex;
    
    // For polar coordinates
    float *intermediateMag;
    float *intermediatePhase;
    
    float *mag;
    float *phase;
    
    
    void setN(int withN);
public:
    FFT(int nPointLength);

    void setSignal();
    
    void forwardFFT();
    void inverseFFT();
};



#endif /* defined(__DSPLibrary__FFT__) */
