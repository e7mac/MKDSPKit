//
//  DelayLine.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__DelayLine__
#define __DSPLibrary__DelayLine__

#include <iostream>

class DelayLine {
private:
    int _length;
    int _readHead, _writeHead;
    float *_circularBuffer;
public:
    void setLength(const float length, float fs);
    void clearBuffer();
    void advanceWriteHead();
    void advanceReadHead();
    void write(float withSample);
    float read();
};


#endif /* defined(__DSPLibrary__DelayLine__) */
