//
//  dmd2.cpp
//  ocvTest
//
//  Created by Justin Thompson on 6/29/14.
//  Copyright (c) 2014 Justin Thompson. All rights reserved.
//

#include "dmd2.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;
using namespace cv;


dmd2::dmd2(Mat const dataIn,
           int numFeatures,
           int scale_modes,
           int numStacks,
           double dt){
    
    //Working variables
    Mat X;
    Mat Y;
    Mat Atilde;
    Mat W;
    
    if (numStacks > 1){
        
        cout << "Stacking algorithm not finished yet." << endl;
        cout << "make sure you're setting numStacks to 1." << endl;
        //you have to finish this
    }
    else{
        
        
    }
    
    
}

void dmd2::computeDmd(Mat const dataIn,
                int numFeatures,
                int scale_modes,
                int numStacks,
                      double dt){







};