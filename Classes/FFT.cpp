//
//  FFT.cpp
//  DSPLibrary
//
//  Created by Mayank on 11/4/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "FFT.h"
#include <Accelerate/Accelerate.h>

FFT::FFT(int nPointLength)
{
    setN(nPointLength);
}

void FFT::setN(int withN)
{
    N = withN;
    logN = log2f(N);
    fftSetup = vDSP_create_fftsetup(logN, kFFTRadix2);

    //input output buffers
    x = new float[N];
    y = new float[N];

    // We need complex buffers in two different formats!
    tempComplex = new DSPComplex[N/2];
    
    tempSplitComplex.realp = new float[N/2];
    tempSplitComplex.imagp = new float[N/2];
    
    // For polar coordinates
    intermediateMag = new float[N/2];
    intermediatePhase = new float[N/2];
    
    mag = new float[N/2 + 1];
    phase = new float[N/2 + 1];

}

void FFT::setSignal()
{
//    // Initialize the input buffer with a sinusoid
//    int BIN = 3;
//    for (int k = 0; k < N; k++)
//        x[k] = cos(2*M_PI*BIN*k/N);
    for (int k = 0; k < N; k++)
        x[k] = 1;
    x[0] = 1;
}

void FFT::forwardFFT()
{
    // ----------------------------------------------------------------
    // Forward FFT
    
    // Scramble-pack the real data into complex buffer in just the way that's
    // required by the real-to-complex FFT function that follows.
    vDSP_ctoz((DSPComplex*)x, 2, &tempSplitComplex, 1, N/2);
    
    // Do real->complex forward FFT
    vDSP_fft_zrip(fftSetup, &tempSplitComplex, 1, logN, kFFTDirection_Forward);
    
    // Print the complex spectrum. Note that since it's the FFT of a real signal,
    // the spectrum is conjugate symmetric, that is the negative frequency components
    // are complex conjugates of the positive frequencies. The real->complex FFT
    // therefore only gives us the positive half of the spectrum from bin 0 ("DC")
    // to bin N/2 (Nyquist frequency, i.e. half the sample rate). Typically with
    // audio code, you don't need to worry much about the DC and Nyquist values, as
    // they'll be very close to zero if you're doing everything else correctly.
    //
    // Bins 0 and N/2 both necessarily have zero phase, so in the packed format
    // only the real values are output, and these are stuffed into the real/imag components
    // of the first complex value (even though they are both in fact real values). Try
    // replacing BIN above with N/2 to see how sinusoid at Nyquist appears in the spectrum.
    printf("\nSpectrum:\n");
    for (int k = 0; k < N/2; k++)
    {
        printf("%3d\t%6.2f\t%6.2f\n", k, tempSplitComplex.realp[k], tempSplitComplex.imagp[k]);
    }
    
    // ----------------------------------------------------------------
    // Convert from complex/rectangular (real, imaginary) coordinates
    // to polar (magnitude and phase) coordinates.
    
    // Compute magnitude and phase. Can also be done using vDSP_polar.
    // Note that when printing out the values below, we ignore bin zero, as the
    // real/complex values for bin zero in tempSplitComplex actually both correspond
    // to real spectrum values for bins 0 (DC) and N/2 (Nyquist) respectively.
    vDSP_zvabs(&tempSplitComplex, 1, intermediateMag, 1, N/2);
    vDSP_zvphas(&tempSplitComplex, 1, intermediatePhase, 1, N/2);

    
    mag[0] = intermediateMag[0];
    phase[0] = 0;
    for (int k = 1; k < N/2; k++)
    {
        mag[k] = intermediateMag[k];
        phase[k] = intermediatePhase[k];
    }
    mag[N/2] = intermediatePhase[0];
    phase[N/2] = 0;
    
    printf("\nMag / Phase:\n");
    for (int k = 1; k < N/2; k++)
    {
        printf("%3d\t%6.2f\t%6.2f\n", k, intermediateMag[k], intermediatePhase[k]);
    }

    printf("\nMag / Phase:\n");
    for (int k = 1; k < N/2; k++)
    {
        printf("%3d\t%6.2f\t%6.2f\n", k, mag[k], phase[k]);
    }
    
    // ----------------------------------------------------------------
    // Convert from polar coordinates back to rectangular coordinates.
    
    tempSplitComplex.realp = intermediateMag;
    tempSplitComplex.imagp = intermediatePhase;
    
    vDSP_ztoc(&tempSplitComplex, 1, tempComplex, 2, N/2);
    vDSP_rect((float*)tempComplex, 2, (float*)tempComplex, 2, N/2);
    vDSP_ctoz(tempComplex, 2, &tempSplitComplex, 1, N/2);
}

void FFT::inverseFFT()
{
    // ----------------------------------------------------------------
    // Do Inverse FFT
    
    // Do complex->real inverse FFT.
    vDSP_fft_zrip(fftSetup, &tempSplitComplex, 1, logN, kFFTDirection_Inverse);
    
    // This leaves result in packed format. Here we unpack it into a real vector.
    vDSP_ztoc(&tempSplitComplex, 1, (DSPComplex*)y, 2, N/2);
    
    // Neither the forward nor inverse FFT does any scaling. Here we compensate for that.
    float scale = 0.5/N;
    vDSP_vsmul(y, 1, &scale, y, 1, N);
    // Assuming it's all correct, the input x and output y vectors will have identical values
    printf("\nInput & output:\n");
    for (int k = 0; k < N; k++)
    {
        printf("%3d\t%6.2f\t%6.2f\n", k, x[k], y[k]);
    }
}