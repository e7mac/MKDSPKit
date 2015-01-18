//
//  SimpleDelayLine.h
//  GrainProc
//
//  Created by Mayank on 9/24/13.
//  Copyright (c) 2013 Mayank, Kurt. All rights reserved.
//

#ifndef __GrainProc__SimpleDelayLine__
#define __GrainProc__SimpleDelayLine__

#include <iostream>

class SimpleDelayLine {
public:
    
    int length;
    int readHead, writeHead;
    float *circularBuffer;
    
    void setLength(const float withLength, float withFs);
    void clearBuffer();
    void advanceWriteHead();
    void advanceWriteHead(int numPositions);
    void advanceReadHead();
    void write(float withSample);
    void write(float *startSample, int numSamples);
    float read();
};


#endif /* defined(__GrainProc__SimpleDelayLine__) */
