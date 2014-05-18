//
//  TruncatedSincInterpolator.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__TruncatedSincInterpolator__
#define __DSPLibrary__TruncatedSincInterpolator__

#include <iostream>
#include "FIR.h"

class TruncatedSincInterpolator {
public:
  FIR *_fir;
  double _resampleFactor;
public:
  TruncatedSincInterpolator(int length, double resampleFactor);
  ~TruncatedSincInterpolator();
  void calculateCoefs();
  void reset();
  void process (float input, float& output);
};


#endif /* defined(__DSPLibrary__TruncatedSincInterpolator__) */
