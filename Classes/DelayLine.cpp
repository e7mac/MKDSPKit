//
//  DelayLine.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "DelayLine.h"

void DelayLine::setLength(const float length, float fs)
{
    _length = length * fs;
    _circularBuffer = new float[_length];
    clearBuffer(); // clear the buffer before we start writing into it
    _readHead = _length*0.5;
    _writeHead = 0;
}

void DelayLine::clearBuffer()
{
    for (int i = 0; i < _length; i++) { // clear buffer
        _circularBuffer[(i + _length) % _length] = 0;
    }
}

void DelayLine::advanceWriteHead()
{
    _writeHead = (_writeHead+1)%_length;
}

void DelayLine::advanceReadHead()
{
    _readHead = (_readHead+1)%_length;
}

void DelayLine::write(float withSample)
{
    int x = _writeHead;
    _circularBuffer[x] = withSample;
}

float DelayLine::read()
{
    int x = _readHead;
    return _circularBuffer[x];
}
