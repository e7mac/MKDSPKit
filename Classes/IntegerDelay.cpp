//
//  SimpleDelayLine.cpp
//  GrainProc
//
//  Created by Mayank on 9/24/13.
//  Copyright (c) 2013 Mayank, Kurt. All rights reserved.
//

#include "IntegerDelay.h"

IntegerDelay::IntegerDelay(int withLength) {
  length = withLength;           // remember the length
  delayLine = new float[length]; // instantiate delay line
  for (int i=0;i<length;i++) {
    delayLine[i] = 0;            // fill delay line with zeros
  }
  writeHead = 0;
}

void IntegerDelay::writeInput(float withSample) {
  delayLine[writeHead] = withSample;
  writeHead++;
  if (writeHead>length-1) {
    writeHead = 0;
  }
}

float IntegerDelay::readOutput() {
  if (writeHead<length-1) {
    return delayLine[writeHead+1];
  } else {
    return delayLine[0];
  }
}
