//
//  ADSR.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__ADSR__
#define __DSPLibrary__ADSR__

#include <iostream>

class ADSR {
public:
  double	_a, _d, _s, _r, _envelope, _fs, _aSlope, _dSlope, _rFactor;
  double	*_aEnvelope, *_dEnvelope, *_rEnvelope;
  int	_aEnvelopeCount, *_dEnvelopeCount, *_rEnvelopeCount;
  int _mode;
  
public:
  ADSR();
  void setAttackTime(double a);
  void setDecayTime(double d);
  void setSustainLevel(double s);
  void setReleaseTime(double r);
  void reset();
  void noteOn();
  void noteOff();
  void process (float input, float& output);
  void process (float *input, float *output, int numSamples);
};


#endif /* defined(__DSPLibrary__ADSR__) */
