//
//  SimpleDelayLine.h
//  GrainProc
//
//  Created by Mayank on 9/24/13.
//  Copyright (c) 2013 Mayank, Kurt. All rights reserved.
//

#ifndef __GrainProc__IntegerDelay__
#define __GrainProc__IntegerDelay__

#include <iostream>

class IntegerDelay {
public:
  float *delayLine;
  int length;
  int writeHead;
  void setLength(int withLength);
  void writeInput(float withSample);
  float readOutput();
};


#endif /* defined(__GrainProc__SimpleDelayLine__) */
