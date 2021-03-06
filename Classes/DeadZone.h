//
//  DeadZone.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__DeadZone__
#define __DSPLibrary__DeadZone__

#include <iostream>
#include <math.h>

//  dead zone memoryless nonlinearity
class DeadZone
{
protected:
    double _alpha, _beta;
    
public:
    DeadZone();
    void setAlpha(double alpha);
    void setBeta (double beta);
    void process (double input, double& output);
};


#endif /* defined(__DSPLibrary__DeadZone__) */
