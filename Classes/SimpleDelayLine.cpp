//
//  SimpleDelayLine.cpp
//  GrainProc
//
//  Created by Mayank on 9/24/13.
//  Copyright (c) 2013 Mayank, Kurt. All rights reserved.
//

#include "SimpleDelayLine.h"

void SimpleDelayLine::setLength(const float withLength, float withFs) {
    length = withLength * withFs;
    circularBuffer = new float[length];
    clearBuffer(); // clear the buffer before we start writing into it
    readHead = length*0.5;
    writeHead = 0;
}

void SimpleDelayLine::clearBuffer() {
    for (int i = 0; i < length; i++) { // clear buffer
        circularBuffer[(i + length) % length] = 0;
    }
}

void SimpleDelayLine::advanceWriteHead() {
    writeHead = (writeHead+1)%length;
}

void SimpleDelayLine::advanceReadHead() {
    readHead = (readHead+1)%length;
}

void SimpleDelayLine::write(float withSample) {
    int x = writeHead;
    circularBuffer[x] = withSample;
}

float SimpleDelayLine::read() {
    int x = readHead;
    return circularBuffer[x];
}
