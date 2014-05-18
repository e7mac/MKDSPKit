//
//  PitchShift.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "PitchShift.h"


PitchShift::PitchShift(float speed, int bufferTimeLength, int fs)
{
    _speed = speed;
    _delay.setLength(bufferTimeLength, fs);
    _timeCounter = 0;
}

void PitchShift::process (float input, float& output)
{
    _delay.write(input);
    _delay.advanceWriteHead();
    _timeCounter+=_speed;
    while (_timeCounter>1) {
        _timeCounter--;
        _delay.advanceReadHead();
    }
    output = _delay.read();
}
