//
//  ADSR.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "ADSR.h"
#include <math.h>

ADSR::ADSR()
{
  _fs = 44100;
  reset();
}
void ADSR::setAttackTime(double a)
{
  _a = a;
  _aSlope = 1/(_fs*_a);
}
void ADSR::setDecayTime(double d)
{
  _d = d;
  _dSlope = (1-_s)/(_d*_fs);
}
void ADSR::setSustainLevel(double s)
{
  _s = s;
}
void ADSR::setReleaseTime(double r)
{
  _r = r;
  _rFactor = exp(-3/(_r*_fs));
}
void ADSR::reset()
{
  _mode = 0;
  _envelope = 0;
}
void ADSR::noteOn()
{
  _mode = 1;
}
void ADSR::noteOff()
{
  _mode = 4;
}
void ADSR::process (float input, float& output)
{
  switch (_mode) {
    case 1://a
    {
      if (_envelope < 1) {
        _envelope += _aSlope;
      } else {
        _mode++;
      }
    }
      break;
    case 2://d
    {
      if (_envelope > _s) {
        _envelope -= _dSlope;
      } else {
        _mode++;
      }
    }
      break;
    case 3://s
    {
      //pass
    }
      break;
    case 4://r
    {
      if (_envelope > 0) {
        _envelope *= _rFactor;
      } else {
        reset();
      }
    }
      break;
    case 0:
    default:
      break;
  }
  output = input *_envelope;
}
