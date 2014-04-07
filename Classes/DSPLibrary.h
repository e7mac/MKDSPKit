//
//  DSPLibrary.h
//  PediPadProc
//
//  Created by Mayank on 9/13/12.
//  Copyright (c) 2012 Mayank, Kurt. All rights reserved.
//

#ifndef PediPadProc_DSPLibrary_h
#define PediPadProc_DSPLibrary_h


#include <iostream>
#include <math.h>
#include "Biquad.h"
#include "SoftClip.h"
#include "GranularLine.h"
#define PI 3.14159265358979

//struct Grain
//{
//    int grainLength;
//    int elapsed;
//    int readHead;
//    bool isActive;
//    float currentNumGrainsAmplitude;
//};
//
////  interpolating delay line
//struct GranularLine {
//    int length; // size of the buffer in samples
//    int writeHead, rate;
//    int maxNumGrains = 50;
//    int numGrains = maxNumGrains;
//    Grain *grains;
//    float *circularBuffer;
//    float *cosValues;
//    float avgDelay = 0.5; // in seconds
//    float spread = 0.5; // in percentage of buffer length
//    float maxSpread = 0.5; // tweak this later
//    int srate;
//    
//    GranularLine(void) { }
//    
//    void resetGrain(int i)
//    {
//        float lowerBound = fmaxf((avgDelay - 2 * spread * maxSpread * 0.5), 0);// + 0.01 * srate / length);
//        float upperBound = fminf((avgDelay + 2 * spread * maxSpread * 0.5), 1);
//        
//        int delay;
//        if (upperBound == lowerBound)
//            delay = avgDelay * length;
//        else
//            delay = (lowerBound + fmodf((float)rand()/RAND_MAX, upperBound-lowerBound)) * length;
//        
//        grains[i].readHead = (writeHead - delay + length)%length;
//        grains[i].grainLength = (int)((50 + rand()%100) * srate * 0.001);
//        
//        grains[i].elapsed = 0;
//        if (i <= numGrains)
//            grains[i].isActive = 1;
//        else
//            grains[i].isActive = 0;
//        grains[i].currentNumGrainsAmplitude = 1/sqrtf(numGrains) * grains[i].isActive;
//    }
//    
//    void setLength(const float withLength, float withFs) {
//        length = withLength * withFs;
//        circularBuffer = new float[length];
//        clearBuffer(); // clear the buffer before we start writing into it
//        grains = new Grain[numGrains];
//        for (int i=0;i<numGrains;i++)
//        {
//            resetGrain(i);
//        }
//        writeHead = 0;
//        setRate(1.0);
//        
//        populateWindow(); // create window buffer
//    }
//    
//    void clearBuffer() {
//        for (int i = 0; i < length; i++) { // clear buffer
//            circularBuffer[(i + length) % length] = 0;
//        }
//    }
//    
//    void advanceWriteHead() {
//        writeHead = (writeHead + rate)%length;
//    }
//    
//    
//    void write(float withSample) {
//        circularBuffer[writeHead] = withSample;
//    }
//    
//    float readGrain(int i) {
//        float window = getWindow((float)grains[i].elapsed/grains[i].grainLength);
//        
//        float sample = window * circularBuffer[(grains[i].readHead+grains[i].elapsed++)%length];
//        if (grains[i].elapsed>=grains[i].grainLength)
//        {
//            resetGrain(i);
//        }
//        return sample*grains[i].currentNumGrainsAmplitude;
//    }
//    
//    float getWindow(float x)
//    {
//        int index = x*length;
//        return cosValues[index];
//    }
//    
//    void populateWindow()
//    {
//        cosValues = new float[length];
//        for (int i=0;i<length;i++)
//            cosValues[i] = 0.5-0.5*cosf(2*PI*i/length);
//    }
//    
//    
//    void setRate(float withRate) {
//        rate = withRate;
//    }
//};
//
//
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  soft clipPIng memoryless nonlinearity
//class SoftClip {
//    
//protected:
//    float n;
//    
//public:
//    SoftClip() {
//        setN(2.5); // approximates hyperbolic tangent function
//    }
//    
//    void setN(float withN) { n = withN; }
//    
//    void process (float input, float& output) {
//        output = input / pow(1 + pow(fabs(input), n), 1/n);
//        //optimized for pedipadproc
//        //        output = input / 1 + fabsf(input);
//    }
//};


//------------------------------------------------------------------------------
//  biquad filter section
//struct Biquad {
//    double	b0, b1, b2, a1, a2, z1, z2;
//    
//    Biquad() {
//        this->b0=1.0;
//        this->b1=0.0;
//        this->b2=0.0;
//        this->a1=0.0;
//        this->a2=0.0;
//        reset();
//    }
//    void setCoefs(double* coefs) { // set filter coefficients [b0 b1 b2 a1 a2]
//        this->b0=*(coefs);
//        this->b1=*(coefs+1);
//        this->b2=*(coefs+2);
//        this->a1=*(coefs+3);
//        this->a2=*(coefs+4);
//    }
//    void reset() { // reset filter state
//        z1=0;
//        z2=0;
//    }
//    void process (float input, float& output) { // process input sample, direct form II transposed
//        output = z1 + input*b0;
//        z1 = z2 + input*b1 - output*a1;
//        z2 = input*b2 - output*a2;
//    }
//};

//-------------------------------------------------------------------------------------------------------
// Peak detector
struct PeakDetector {
	double	b0, a1, levelEstimate;
	
	PeakDetector() {
		// default to pass-through
		this->a1 = 0; // relese coeffs
		this->b0 = 1;
		reset();
	}
	
	void setTau(double tau, double fs) {
		a1 = exp( -1.0 / ( tau * fs ) );
		b0 = 1 - a1;
	}
	
	void reset() { // reset filter state
		levelEstimate = 0;
	}
	
	void process (double input, double& output) {
        levelEstimate += b0 * ( fabs( input ) - levelEstimate );
        output = levelEstimate;
	}
    
	void process (float input, float& output) {
        levelEstimate += b0 * ( fabs( input ) - levelEstimate );
        output = levelEstimate;
    }
};

#define dB(x) 20.0*((x) > 0.00001 ? log10(x) : log10(0.00001))

#define dB2lin(x) powf (10.0,(x) / 20.0 )

struct Compressor {
    float threshold,logThreshold,ratio,raisedTo;
    PeakDetector levelEstimator;
    Compressor()
    {
        
    }
    Compressor(float wthreshold,float wratio, int srate)
    {
        threshold = wthreshold;
        ratio = wratio;
        raisedTo = 1/(ratio-1);
        levelEstimator.setTau(0.05, srate);
        logThreshold = dB(threshold);
    }
    void setupCompressor(float wthreshold,float wratio, int srate)
    {
        threshold = wthreshold;
        ratio = wratio;
        raisedTo = 1/(ratio-1);
        levelEstimator.setTau(0.05, srate);
        logThreshold = dB(threshold);
    }
    
    
    void process(float input, float&output)
    {
        float levelEstimate;
        levelEstimator.process(input, levelEstimate);
        float logLevel = dB(levelEstimate);
        if (logLevel < logThreshold)
        {
            output = input;
        }
        else
        {
            float dbGain = (logLevel - logThreshold) / (1/ratio -1);
            output = input * dB2lin(dbGain);
        }
        
    }
    
};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void bilinearTranform(double acoefs[], double dcoefs[], double withFs);
void designParametric(double* dcoefs, double center, double gain, double qval, double withFs);
void designFirstOrderLowpass(double* dcoefs, double cutoff, double withFs);
void designFirstOrderHighpass(double* dcoefs, double cutoff, double withFs);
#endif
