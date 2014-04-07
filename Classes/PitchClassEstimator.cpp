//
//  PitchClassEstimator.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "PitchClassEstimator.h"
#include <Accelerate/Accelerate.h>

PitchClassEstimator::PitchClassEstimator(int bufferTime, int sampleRate)
{
    delayLine.setLength(bufferTime, sampleRate);
}

void PitchClassEstimator::write(float sample)
{
    delayLine.write(sample);
    delayLine.advanceWriteHead();
    if (bufferIsFull()) {
        process();
    }
}

bool PitchClassEstimator::bufferIsFull()
{
    int diff = delayLine.writeHead - delayLine.readHead;
    bool full = (diff == delayLine.length);
    return full;
}

void PitchClassEstimator::process()
{
    //do pitch estimation
    
    //1.window
    window();
    //2.zero phase zero pad
    zeroPad();
    //3.fft
    fft();
    //4.mag fft
    magfft();
    //5.bin it
    bin();
    //6.look for max bin and set pitchEstimate
    maxOfBin();
    pitchEstimate = 100;
    
    //reset delayline - unnecessary?
}


void PitchClassEstimator::window()
{
    //rectangular window - no change to buffer
}

void PitchClassEstimator::zeroPad()
{
    int length = delayLine.length;
    int zeropadfactor = 16;
    int const zeropaddedlength = zeropadfactor*length;
    float *intermediateBuffer = new float[zeropaddedlength];
    //TODO : EFFICIENCY !!!!!!
    for (int i=0;i<zeropaddedlength;i++) {
        intermediateBuffer[i] = 0;
    }
    for (int i=(zeropadfactor - 1)*zeropaddedlength / 2;i<(zeropadfactor + 1)*zeropaddedlength / 2;i++) {
        intermediateBuffer[i] = delayLine.read();
        delayLine.advanceReadHead();
    }
}
void PitchClassEstimator::fft()
{
    
}
void PitchClassEstimator::magfft()
{
    
}

void PitchClassEstimator::bin()
{
    
}
void PitchClassEstimator::maxOfBin()
{
    
}