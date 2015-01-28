//
//  GranularLine.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__GranularLine__
#define __DSPLibrary__GranularLine__

#include <iostream>
#include <math.h>

struct Grain
{
    int grainLength;
    float elapsed;
    int readHead;
    bool isActive;
    float currentNumGrainsAmplitude;
    int direction;
};

class GranularLine
{
public:
    int length; // size of the buffer in samples
    int writeHead, rate;
    float readHead;
    int maxNumGrains = 50;
    int numGrains = maxNumGrains;
    Grain *grains;
    float *circularBuffer;
    float *cosValues;
    float avgDelay = 0.5; // in seconds
    float spread = 0.5; // in percentage of buffer length
    float maxSpread = 0.5; // tweak this later
    int srate;
    float readSpeed = 1;
    float gain = 1;
    float avgGrainLengthInMS = 100;
    float backwardDensity = 0;
  
    float readSpeedVariation = 0;
    float readSpeedDirectionPercentage = 0.5;
public:
    void resetGrain(int i);
    void setLength(const float withLength, float withFs);
    void clearBuffer();
    void advanceWriteHead();
    void advanceWriteHead(int numSamples);
    void write(float withSample);
    void write(float *firstSample, int numSamples);
    float readGrain(int i);
    float readGrain(int grainNum, int numSamples, float* destination);
    float getWindow(float x);
    void populateWindow();
    void setRate(float withRate);
  void setBackwardDirectionFraction(float fraction);
};


#endif /* defined(__DSPLibrary__GranularLine__) */
