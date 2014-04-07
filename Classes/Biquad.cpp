//
//  Biquad.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "Biquad.h"

Biquad::Biquad()
{
    _b0=1.0;
    _b1=0.0;
    _b2=0.0;
    _a1=0.0;
    _a2=0.0;
    reset();
}
void Biquad::setCoefs(double* coefs)
{ // set filter coefficients [b0 b1 b2 a1 a2]
    _b0=*(coefs);
    _b1=*(coefs+1);
    _b2=*(coefs+2);
    _a1=*(coefs+3);
    _a2=*(coefs+4);
}

void Biquad::reset()
{ // reset filter state
    _z1=0;
    _z2=0;
}
void Biquad::process (float input, float& output)
{ // process input sample, direct form II transposed
    output = _z1 + input*_b0;
    _z1 = _z2 + input*_b1 - output*_a1;
    _z2 = input*_b2 - output*_a2;
}
