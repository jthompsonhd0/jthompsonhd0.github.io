//
//  dmd2.h
//  ocvTest
//
//  Created by Justin Thompson on 6/29/14.
//  Copyright (c) 2014 Justin Thompson. All rights reserved.
//

#ifndef __ocvTest__dmd2__
#define __ocvTest__dmd2__

#include <iostream>
#include <math.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#define MAX_FEATURES 1000000000

using namespace std;
using namespace cv;


class dmd2{

    //Output Data
    Mat Phi;
    Mat mu;
    Mat lambda;
    Mat diagS;
    Mat X0;

    
public:
    
    //constructor / destructor
    dmd2(Mat const dataIn,
         int numFeatures = MAX_FEATURES,
         int scale_modes = 1,
         int numStacks   = 1,
         double dt       = 1.0);
    
    ~dmd2(void){};
    
    
    //Compute dmd
    void computeDmd(Mat const dataIn,
                    int numFeatures = MAX_FEATURES,
                    int scale_modes = 1,
                    int numStacks   = 1,
                    double dt       = 1.0);

    
    
    
    
    
    
};










#endif /* defined(__ocvTest__dmd2__) */
