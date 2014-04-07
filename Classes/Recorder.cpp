//
//  Recorder.cpp
//  DSPLibrary
//
//  Created by Mayank on 11/4/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "Recorder.h"


void Recorder::setLength(const float length, float fs)
{
    _length = length * fs;
    _buffer = new float[_length];
    clearBuffer(); // clear the buffer before we start writing into it
    _readHead = 0;
    _writeHead = 0;
}

void Recorder::clearBuffer()
{
    for (int i = 0; i < _length; i++) { // clear buffer
        _buffer[i] = 0;
    }
}

void Recorder::advanceWriteHead()
{
    _writeHead++;
    if (_writeHead==_length)
    {
        float *oldBuffer = _buffer;
        _length*=2;
        _buffer = new float[_length];
        clearBuffer();
        for (int i=0;i<_length/2;i++)
        {
            _buffer[i]=oldBuffer[i];
        }
        delete oldBuffer;
    }
}

void Recorder::advanceReadHead()
{
    _readHead++;
}

void Recorder::write(float withSample)
{
    _buffer[_writeHead] = withSample;
}

float Recorder::read()
{
    return _buffer[_readHead];
}
