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
