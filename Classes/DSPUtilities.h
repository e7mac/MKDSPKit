//
//  Utilities.h
//  DSPLibrary
//
//  Created by Mayank on 9/11/12.
//  Copyright (c) 2012 Mayank Sanganeria. All rights reserved.
//

#ifndef __DSPLibrary__Utilities__
#define __DSPLibrary__Utilities__

#include <iostream>

class DSPUtilities {
public:
    static void bilinearTransform(double acoefs[], double dcoefs[], double withFs);
    static void designParametric(double* dcoefs, double center, double gain, double qval, double withFs);
    static void designFirstOrderLowpass(double* dcoefs, double cutoff, double withFs);
    static void designFirstOrderHighpass(double* dcoefs, double cutoff, double withFs);
};


#endif /* defined(__DSPLibrary__Utilities__) */