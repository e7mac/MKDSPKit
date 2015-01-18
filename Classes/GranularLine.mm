

//
//  GranularLine.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "GranularLine.h"


void GranularLine::resetGrain(int i)
{
    float lowerBound = fmaxf((avgDelay - 2 * spread * maxSpread * 0.5), 0);// + 0.01 * srate / length);
    float upperBound = fminf((avgDelay + 2 * spread * maxSpread * 0.5), 1);
    
    int delay;
    if (upperBound == lowerBound)
        delay = avgDelay * length;
    else
        delay = (lowerBound + fmodf((float)rand()/RAND_MAX, upperBound-lowerBound)) * length;
    
    grains[i].readHead = (writeHead - delay + length)%length;
    grains[i].grainLength = (int)((avgGrainLengthInMS/2 + rand()%(int)(1.5*avgGrainLengthInMS)) * srate * 0.001);
    
    grains[i].elapsed = 0;
    if (i <= numGrains)
        grains[i].isActive = 1;
    else
        grains[i].isActive = 0;
    grains[i].currentNumGrainsAmplitude = 1/sqrtf(numGrains) * grains[i].isActive;
}

void GranularLine::setLength(const float withLength, float withFs) {
    length = withLength * withFs;
    circularBuffer = new float[length];
    clearBuffer(); // clear the buffer before we start writing into it
    grains = new Grain[numGrains];
    for (int i=0;i<numGrains;i++)
    {
        grains[i].direction = 1;
        resetGrain(i);
    }
    writeHead = 0;
    setRate(1.0);
    
    populateWindow(); // create window buffer
}

void GranularLine::setBackwardDirectionFraction(float fraction)
{
  for (int i=0;i<numGrains;i++) {
    BOOL backward = arc4random_uniform(1) < fraction;
    grains[i].direction = backward ? -1 : 1;
  }
}

void GranularLine::clearBuffer() {
    for (int i = 0; i < length; i++) { // clear buffer
        circularBuffer[(i + length) % length] = 0;
    }
}

void GranularLine::advanceWriteHead() {
    writeHead = (writeHead + rate)%length;
}

void GranularLine::advanceWriteHead(int numSamples) {
  writeHead = (writeHead + numSamples*rate)%length;
}

void GranularLine::write(float withSample) {
  circularBuffer[writeHead] = withSample;
}

void GranularLine::write(float *firstSample, int numSamples) {
  // todo: handle rates
  int samplesFromStart = 0;
  int samplesTillEnd = length - writeHead;
  if (numSamples <= samplesTillEnd) {
    samplesTillEnd = numSamples;
  } else {
    samplesFromStart = numSamples - samplesTillEnd;
  }
  memcpy(&circularBuffer[writeHead], firstSample, samplesTillEnd * sizeof(float));
  if (samplesFromStart > 0) {
    memcpy(&circularBuffer[0], &firstSample[samplesTillEnd], samplesFromStart * sizeof(float));
  }
}

float GranularLine::readGrain(int i) {
    float window = getWindow((float)grains[i].elapsed/grains[i].grainLength);
    grains[i].elapsed += readSpeed;
    int bufferPosition = (int)(grains[i].readHead+grains[i].direction*grains[i].elapsed)%length;
    if (bufferPosition < 0) {
      bufferPosition += length;
    }
    float sample = 0;
    sample = window * circularBuffer[bufferPosition];
    if (grains[i].elapsed>=grains[i].grainLength) {
        resetGrain(i);
    }
    return gain*sample*grains[i].currentNumGrainsAmplitude;
}

float GranularLine::readGrain(int grainNum, int numSamples, float* destination) {
  // handle rates
  float windowFraction = (float)grains[grainNum].elapsed/grains[grainNum].grainLength;
  float window = getWindow(windowFraction);
  grains[grainNum].elapsed += readSpeed;
  int bufferPosition = (int)(grains[grainNum].readHead+grains[grainNum].elapsed)%length;
  float sample = window * circularBuffer[bufferPosition];
  if (grains[grainNum].elapsed>=grains[grainNum].grainLength) {
    resetGrain(grainNum);
  }
  memcpy(destination, &circularBuffer[bufferPosition], numSamples*sizeof(float));
  return gain*sample*grains[grainNum].currentNumGrainsAmplitude;
}


float GranularLine::getWindow(float x)
{
    if (x>1 || isnan(x))
        return 0.0;
    int index = x*length;
    return cosValues[index];
}

void GranularLine::populateWindow()
{
    cosValues = new float[length];
    for (int i=0;i<length;i++)
        cosValues[i] = 0.5-0.5*cosf(2*M_PI*i/length);
}


void GranularLine::setRate(float withRate) {
    rate = withRate;
}
