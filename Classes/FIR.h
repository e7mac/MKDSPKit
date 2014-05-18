//
//  Biquad.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__FIR__
#define __DSPLibrary__FIR__

#include <iostream>

class FIR {
public:
  double *_b;
  double *_z;
  int _length;
  int _writePosition;
public:
    FIR(int length);
    ~FIR();
    void setCoefs(double* coefs);
    void reset();
    void process (float input, float& output);
};


#endif /* defined(__DSPLibrary__FIR__) */
