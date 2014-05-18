//
//  TruncatedSincInterpolator.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "TruncatedSincInterpolator.h"
#include <math.h>

TruncatedSincInterpolator::TruncatedSincInterpolator(int length, double resampleFactor)
{
  _fir = new FIR(length);
  _resampleFactor = resampleFactor;
  calculateCoefs();
}

TruncatedSincInterpolator::~TruncatedSincInterpolator()
{
  delete _fir;
}

void TruncatedSincInterpolator::calculateCoefs()
{
  double *coefs = new double[_fir->_length];
  for (int i=0;i < _fir->_length; i++) {
    double x = (double)M_PI * _resampleFactor * (i - (_fir->_length-1)/2.);
    if (x == 0) {
      coefs[i] = 1;
    } else {
      coefs[i] = sin(x) / x;
    }
    printf ("\nCoef[%i]: %f", i, coefs[i]);
  }
  _fir->setCoefs(coefs);
  delete coefs;
}

void TruncatedSincInterpolator::process (float input, float& output)
{
  _fir->process(input, output);
}
