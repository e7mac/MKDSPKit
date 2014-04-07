//
//  SinOsc.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__SinOsc__
#define __DSPLibrary__SinOsc__

#include <iostream>
#include <math.h>

class SinOsc {
    
protected:
    double _sampleRate, _phase, _centerFrequency, _frequency, _amplitude, _range;
    
public:
    SinOsc();
    void setSampleRate(double sampleRate);
    void reset();
    void setCenterFrequency(float newFrequency);
    void setFrequency(float input);// set the instantaneous frequency based on an 
    void setAmplitude(float amplitude);
    void setRange(double range);
    void process (float& output);

};


#endif /* defined(__DSPLibrary__SinOsc__) */
