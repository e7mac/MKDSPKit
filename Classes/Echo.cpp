//
//  Echo.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "Echo.h"


Echo::Echo(float time, float amp, int fs)
{
    _amp = amp;
    _delay.setLength(time, fs);
}
void Echo::process (float input, float& output)
{
    _delay.write(input);
    _delay.advanceWriteHead();
    output = input + _amp * _delay.read();
    _delay.advanceReadHead();
}
