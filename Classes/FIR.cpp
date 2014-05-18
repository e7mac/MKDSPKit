//
//  Biquad.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "FIR.h"

FIR::FIR(int length)
{
  _b = new double[length];
  _z = new double[length];
  _length = length;
  for (int i=0;i<length;i++ ) {
    _b[i] = 0;
  }
  _writePosition = 0;
}

FIR::~FIR()
{
  delete[] _b;
  delete[] _z;
}

void FIR::setCoefs(double* coefs)
{
  for (int i=0;i<_length;i++ ) {
    _b[i] = coefs[i];
  }
}

void FIR::reset()
{ // reset filter state
  for (int i=0;i<_length;i++ ) {
    _z[i] = 0;
  }
}
void FIR::process (float input, float& output)
{
  _z[_writePosition] = input;
  output = 0;
  for (int i=0;i<_length;i++ ) {
    output += _z[(i + _writePosition) % _length]*_b[i];
  }
  _writePosition = (_writePosition+1)%_length;
}
