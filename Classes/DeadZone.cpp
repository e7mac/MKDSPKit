//
//  DeadZone.cpp
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#include "DeadZone.h"

DeadZone::DeadZone()
{
    _alpha = 0;
    _beta = 0;
}

void DeadZone::setAlpha(double alpha)
{
    _alpha = alpha;
}
void DeadZone::setBeta (double beta)
{
    _beta  = beta;
}

void DeadZone::process (double input, double& output)
{
    if (input < -_alpha) {
        output = -_alpha * tan(_beta) + (input + _alpha) * ((1 - _alpha * tan(_beta)) / (1 - _alpha));
    }
    if (input > _alpha) {
        output = _alpha * tan(_beta) + (input - _alpha) * ((1 - _alpha * tan(_beta)) / (1 - _alpha));
    }
    if (fabs(input) <= _alpha) {
        output = input * tan(_beta);
    }
}
