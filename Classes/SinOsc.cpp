//
//  SinOsc.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "SinOsc.h"

SinOsc::SinOsc()
{
    reset();
}

void SinOsc::setSampleRate(double sampleRate)
{
    _sampleRate = sampleRate;
}

void SinOsc::reset()
{
    _phase = 0.0;
}

void SinOsc::setCenterFrequency(float frequency)
{
    _centerFrequency = frequency;
}

void SinOsc::setFrequency(float input)
{ // set the instantaneous frequency based on an input
    _frequency = _centerFrequency * powf(2.0, input * _range / 12.0);
}

void SinOsc::setAmplitude(float amplitude)
{
    _amplitude = amplitude;
}

void SinOsc::setRange(double range)
{
    _range = range;
}

void SinOsc::process (float& output)
{
    double phaseIncrement =  _frequency / _sampleRate;
    _phase = fmod((_phase + phaseIncrement), (1.0));
    output = sinf(_phase * 2.0 * M_PI) * _amplitude;
}
