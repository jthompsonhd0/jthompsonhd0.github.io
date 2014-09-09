//
//  keyboardUtil.h
//  OpenGL Tutorial2
//
//  Created by Justin Thompson on 8/8/14.
//  Copyright (c) 2014 Justin Thompson. All rights reserved.
//

#ifndef OpenGL_Tutorial2_keyboardUtil_h
#define OpenGL_Tutorial2_keyboardUtil_h

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <opencv/cv.h>
#include "math.h"


using namespace std;
using namespace cv;

//The following 2 structs are set to show the
//default axes orientation
struct PositionVector {
    float lr = 0.191;
    float du = 0;
    float io = -44.5;
};

struct CameraVector {
    float lr = 0;
    float du = 0;
    float tl = 0;
};

//From main.cpp
extern float movingSpeed;
extern float lookingSpeed;
extern float tiltSpeed;
extern float dT;
extern bool KEYS[256];
extern PositionVector objPosition;
extern CameraVector camView;
extern bool g_axes;
extern int loopCount;
extern int nFT;
extern int nOverlap;
extern int nDraw;
extern int g_cMap;
extern float sinTheta;
extern float g_Delay;
extern int plotType;
extern int secnds;
extern Mat cMap;
extern Mat cMapJet;
extern Mat cMapAutumn;
extern Mat cMapWinter;

void keyboardSpecialUpUtil(int Key){
 
    switch(Key){

        case GLUT_KEY_UP:
            KEYS[200] = false;
            break;
            
        case GLUT_KEY_DOWN:
            KEYS[201] = false;
            break;
            
        case GLUT_KEY_LEFT:
            KEYS[202] = false;
            break;
            
        case GLUT_KEY_RIGHT:
            KEYS[203] = false;
            break;
            
        case GLUT_KEY_HOME:
            KEYS[204] = false;
            break;
            
        case GLUT_KEY_END:
            KEYS[205] = false;
            break;
            
        case GLUT_KEY_PAGE_UP:
            KEYS[206] = false;
            break;
            
        case GLUT_KEY_PAGE_DOWN:
            KEYS[207] = false;
            break;

        default:
            break;
            
    }
}

void keyboardSpecialDownUtil(int Key){
    
    switch(Key){
            
        case GLUT_KEY_UP:
            KEYS[200] = true;
            break;
            
        case GLUT_KEY_DOWN:
            KEYS[201] = true;
            break;
            
        case GLUT_KEY_LEFT:
            KEYS[202] = true;
            break;
            
        case GLUT_KEY_RIGHT:
            KEYS[203] = true;
            break;
            
        case GLUT_KEY_HOME:
            KEYS[204] = true;
            break;
            
        case GLUT_KEY_END:
            KEYS[205] = true;
            break;
            
        case GLUT_KEY_PAGE_UP:
            KEYS[206] = true;
            break;
            
        case GLUT_KEY_PAGE_DOWN:
            KEYS[207] = true;
            break;
            
        default:
            break;
            
    }
}

void handleKeyboard(){
    

    if(KEYS[27]){
        //esc to quit
        exit(0);
    }
    
    //Fourier Transform Controls
    if(KEYS['t']){//Increase length of FT
        nFT *= 2;
        cout << "nFT = " << nFT << endl;
    }
    if(KEYS['g']){//Decrease length of FT
        nFT /= 2;
        cout << "nFT = " << nFT << endl;
    }
    if(KEYS['y']){//Increase length of Overlap
        nOverlap += 1;
        cout << "Overlap = " << nOverlap << endl;
    }
    if(KEYS['h']){//Decrease length of Overlap
        nOverlap -= 1;
        cout << "Overlap = " << nOverlap << endl;
    }
    if(KEYS['u']){//Increase number of points to draw
        //Max points to draw 1024 for now
        if(nDraw < 1024) nDraw *= 2;
        cout << "Drawing " << nDraw << " points" << endl;
    }
    if(KEYS['j']){//Decrease number of points to draw
        //Don't go below 2
        if(nDraw > 2) nDraw /= 2;
        cout << "Drawing " << nDraw << " points" << endl;
    }
    if(KEYS['o']){
        
        plotType = (plotType + 1) % 2;
        
        switch (plotType) {
            case 0:
                cout << "Plotting true location in complex plane" << endl;
                break;
                
            case 1:
                cout << "Plotting z = log(r)*e^(i*theta)" << endl;
                break;
            default:
                break;
        }
        
        
    }
    if(KEYS['p']){
        
        int IN;
        do {
        
            
            cout << "Current FT length:              " << nFT << endl;
            cout << "Current overlap length:         " << nOverlap << endl;
            cout << "Current number of points drawn: " << nDraw << endl;
            cout << "Current loop count:             " << loopCount << endl;
            cout << endl << endl;
            cout << "**********Change Parameters**********" << endl;
            cout << "0. to return to animation" << endl;
            cout << "1. to change FT length" << endl;
            cout << "2. to change overlap length" << endl;
            cout << "3. to change points to draw" << endl;
            cout << "4. to change loopCount (change time)" << endl;
        
            cin >> IN;
        
            switch (IN) {
                case 1:
                    cout << "Enter new length: " << endl;
                    cin >> IN;
                    nFT = IN;
                    break;
                case 2:
                    cout << "Enter new length: " << endl;
                    cin >> IN;
                    nOverlap = IN;
                    break;
                case 3:
                    cout << "Enter new number of points: " << endl;
                    cin >> IN;
                    nDraw = IN;
                    break;
                case 4:
                    cout << "Enter new value for loopCount: " << endl;
                    cin >> IN;
                    loopCount = IN;
                    break;
                default:
                    break;
            }
        
        
        
        } while(IN != 0);
        
        loopCount = IN*44000;
    }
    if(KEYS['-']){
        sinTheta *= 0.9;
    }
    if(KEYS['=']){
        sinTheta *= 1.1;
    }
    
    //Draw Axes
    if(KEYS['A']){
        g_axes = !g_axes;
    }
    
    //Special Keys
    if(KEYS[200]){//UP ARROW
        //Move towards object
        objPosition.io += movingSpeed*dT;
        
    }
    if(KEYS[201]){//DOWN ARROW
        //Move away from object
        objPosition.io -= movingSpeed*dT;
    }
    if(KEYS[202]){//LEFT ARROW
        //Move objects left
        objPosition.lr += movingSpeed*dT;
    }
    if(KEYS[203]){//RIGHT ARROW
        //Move objects right
        objPosition.lr -= movingSpeed*dT;
    }
    if(KEYS[204]){//HOME KEY
        cout << "Setting axes for Frequency" << endl;
        objPosition.lr = 0;
        objPosition.du = 0;
        objPosition.io = -5.805;
        
        camView.lr = 6.2369;
        camView.du = -1.0;
        camView.tl = 0;
    }
    if(KEYS[205]){//END KEY
        cout << "Starting over" << endl;
        loopCount = 0;
        secnds = 0;
    }
    if(KEYS[206]){//PAGE UP KEY
        cout << "Speeding up" << endl;
        g_Delay *= 0.9;
    }
    if(KEYS[207]){//PAGE DOWN KEY
        cout << "Slowing down" << endl;
        g_Delay *= 1.1;
    }
    
    
    
    //Control Object location and view---------
    if (KEYS['r']){
        //move object up/down
        objPosition.du -= movingSpeed*dT;
    }
    if (KEYS['f']){
        //move object up/down
        objPosition.du += movingSpeed*dT;
    }
    if (KEYS['a']){
        //
        camView.lr -= lookingSpeed*dT;
    }
    if (KEYS['d']){
        //
        camView.lr += lookingSpeed*dT;
    }
    if (KEYS['q']){
        //rotate cw about z axis
        camView.tl -= tiltSpeed*dT;
    }
    if (KEYS['e']){
        //rotate ccw about z axis
        camView.tl += tiltSpeed*dT;
        
    }
    if (KEYS['w']){
        //tilt view down up
        camView.du -= lookingSpeed*dT;
        
    }
    if (KEYS['s']){
        //tilt view down up
        camView.du += lookingSpeed*dT;
        
    }
     
    
    //Speed controls--------------------------------
    if (KEYS['1']){
        //decrease moving speed by 10%
        movingSpeed *= 0.95;
    }
    if (KEYS['2']){
        //increase moving speed by 10%
        movingSpeed *= 1.05;
    }
    if (KEYS['3']){
        //decrease looking speed by 10%
        lookingSpeed *= 0.95;
        tiltSpeed *= 0.95;
    }
    if (KEYS['4']){
        //increase looking speed by 10%
        lookingSpeed *= 1.05;
        tiltSpeed *= 1.05;
    }
    
    
    
    //printing---------------------------------------------------
    if (KEYS['P']){
        cout << "objPostition.lr = " << objPosition.lr << endl;
        cout << "objPostition.du = " << objPosition.du << endl;
        cout << "objPostition.io = " << objPosition.io << endl;
        cout << "camView.lr = " << camView.lr << endl;
        cout << "camView.du = " << camView.du << endl;
        cout << "camView.tl = " << camView.tl << endl;

    }
    
}




#endif
