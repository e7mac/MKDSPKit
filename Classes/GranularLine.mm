

//
//  GranularLine.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "GranularLine.h"
#import <Accelerate/Accelerate.h>

#define WINDOW_LENGTH 2048

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
    // ensure grains don't wrap around audio buffer
    if (grains[i].readHead + grains[i].grainLength > length) {
      grains[i].readHead -= grains[i].grainLength;
    }
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
  backwardDensity = fraction;
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
    int direction =  (arc4random_uniform(100)/100. > readSpeedDirectionPercentage) ? 1 : -1;
    float variation = arc4random_uniform(readSpeedVariation*44100)/44100.;
    grains[i].elapsed += readSpeed * (1 + direction*variation);
    int bufferPosition = (int)(grains[i].readHead+grains[i].direction*grains[i].elapsed)%length;
    if (bufferPosition < 0) {
      bufferPosition += length;
    }
    float sample = 0;
    sample = window * circularBuffer[bufferPosition];
    if (grains[i].elapsed>=grains[i].grainLength) {
        resetGrain(i);
    }
//  return gain*sample*grains[i].currentNumGrainsAmplitude;
  return sample*grains[i].currentNumGrainsAmplitude;
}

void GranularLine::readGrain(int grainNum, int numSamples, float* destination) {
  float output[numSamples];
//  for (int i=0;i<numSamples;i++) {
////    output[i] = readGrain(grainNum);
//    
//    //in function implementation
//    // scalar
//    grains[grainNum].elapsed += readSpeed;
//    int bufferPosition = (int)(grains[grainNum].readHead+grains[grainNum].direction*grains[grainNum].elapsed)%length;
//    if (bufferPosition < 0) {
//      bufferPosition += length;
//    }
//    if (grains[grainNum].elapsed>=grains[grainNum].grainLength) {
//      resetGrain(grainNum);
//    }
//    float sample = circularBuffer[bufferPosition];
//    
//    
//    
//    //apply window
////    float window = getWindow((float)grains[grainNum].elapsed/grains[grainNum].grainLength);
////    sample *= window;
//    output[i] = sample*grains[grainNum].currentNumGrainsAmplitude;
//  }
  int processedSamples = 0;
  while (processedSamples < numSamples) {
    int remainingSamples = (numSamples - processedSamples);
    int bufferPosition = grains[grainNum].readHead+grains[grainNum].elapsed;
    int samplesToCopy = 0;
    float startFraction = 0;
    float endFraction = 0;
    startFraction = grains[grainNum].elapsed / grains[grainNum].grainLength;
    if (remainingSamples * readSpeed  == (grains[grainNum].grainLength - grains[grainNum].elapsed)) {
      samplesToCopy = remainingSamples;
      endFraction = (samplesToCopy * readSpeed + grains[grainNum].elapsed) / grains[grainNum].grainLength;
      resetGrain(grainNum);
    } else if (remainingSamples * readSpeed < grains[grainNum].grainLength - grains[grainNum].elapsed) {
      samplesToCopy = remainingSamples;
      endFraction = (samplesToCopy * readSpeed + grains[grainNum].elapsed) / grains[grainNum].grainLength;
      grains[grainNum].elapsed += samplesToCopy * readSpeed;
    } else if (remainingSamples * readSpeed > grains[grainNum].grainLength - grains[grainNum].elapsed) {
      int remainingSamplesInGrain = (grains[grainNum].grainLength - grains[grainNum].elapsed) / readSpeed;
      samplesToCopy = remainingSamplesInGrain;
      endFraction = (samplesToCopy * readSpeed + grains[grainNum].elapsed) / grains[grainNum].grainLength;
      resetGrain(grainNum);
    }
    //get output buffer based on readspeed
    float indexBuffer[samplesToCopy];
    float start = bufferPosition;
    float increment = readSpeed;
    
    vDSP_vramp(&start, &increment, indexBuffer, 1, samplesToCopy);
    float audioBufferLength = length;
    vDSP_vsdiv(indexBuffer, 1, &audioBufferLength, indexBuffer, 1, samplesToCopy);
    vDSP_vfrac(indexBuffer, 1, indexBuffer, 1, samplesToCopy);
    vDSP_vsmul(indexBuffer, 1, &audioBufferLength, indexBuffer, 1, samplesToCopy);
    vDSP_vlint(circularBuffer, indexBuffer, 1, &output[processedSamples], 1, samplesToCopy, length);
    
    //window multiply
    float window[samplesToCopy];
    getWindow(&window[0], startFraction, endFraction, samplesToCopy);
    vDSP_vmul(window, 1, &output[processedSamples], 1, &output[processedSamples], 1, samplesToCopy);
    processedSamples += samplesToCopy;
  }
  float grainAmplitude =  gain * grains[grainNum].currentNumGrainsAmplitude;
  vDSP_vsmul(output, 1, &grainAmplitude, destination, 1, numSamples);
  return;
}

void GranularLine::getWindow(float *destination, float startFraction, float endFraction, int count)
{
  if (startFraction < 0 || isnan(startFraction)) {
    startFraction = 0;
  }
  if (endFraction > 1 || isnan(endFraction)) {
    endFraction = 1;
  }
  float startIndex = startFraction * (WINDOW_LENGTH);
  float endIndex = endFraction * (WINDOW_LENGTH);
  float indexDiff = endIndex - startIndex;
  float indexIncrement = indexDiff / (count);
  float interpolationVector[count];
  vDSP_vramp(&startIndex, &indexIncrement, interpolationVector, 1, count);
  vDSP_vlint(cosValues, interpolationVector, 1, destination, 1, count, WINDOW_LENGTH);
}



float GranularLine::getWindow(float x)
{
    if (x>1 || isnan(x))
        return 0.0;
    int index = x*WINDOW_LENGTH;
    return cosValues[index];
}

void GranularLine::populateWindow()
{
    cosValues = new float[WINDOW_LENGTH];
    for (int i=0;i<WINDOW_LENGTH;i++)
        cosValues[i] = 0.5-0.5*cosf(2*M_PI*i/WINDOW_LENGTH);
}


void GranularLine::setRate(float withRate) {
    rate = withRate;
}
