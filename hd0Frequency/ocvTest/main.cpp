/****************************************************************

 Frequency


  Created by Justin Thompson on 6/29/14.
  Copyright (c) 2014 Justin Thompson. All rights reserved.

****************************************************************/

#include <iostream>
#include <time.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <opencv/cv.h>
#include "math.h"
#include "keyboardUtil.h"
#include "lightingUtil.h"

using namespace std;
using namespace cv;


/*********************************
 * GLOBALS
 *********************************/

//Data Matrices
Mat TimeM;
Mat ReSpec;
Mat ImSpec;
Mat cMapJet;
Mat cMapAutumn;
Mat cMapWinter;

//Playback Control
int loopCount = 0;
bool firstLoop = true;
float g_Delay = 0.1;
int plotType = 0;

//Fourier Transform Controls
int nFT = 22000;                //length of transform
int nOverlap = 1100;            //number to overlap for STFT
int nDraw = 512;                //number of pts to draw from transform

//Size Control
float sinTheta = 0.5;

//Colormap Control
int g_cMap = 1;


//Display Window Specs
const int winWidth = 640;
const int winHeight = 480;
const char * winTitle = "Frequency";

//Camera / Movement Control
PositionVector objPosition;
CameraVector camView;
float movingSpeed = 2.1;
float lookingSpeed = 21;
float tiltSpeed = 11;

//Support Vars: used to make smooth motion independent of frame rate
float timeOld;
float timeCurrent;
float dT;

//Keyboard Control
bool KEYS[256] = {false};

//Drawing
bool g_axes = false; //Useful. Press 'A' to toggle Note: (x,y,z) in (r,g,b)

//Mouse
int m_currentX;
int m_currentY;
int m_oldX;
int m_oldY;
int m_dX;
int m_dY;
bool m_buttonDown = false;

/*********************************
 * OpenGL API FUNCTIONS
 *
 *  Must be declared in main.cpp
 *  as per OpenGL API
 *********************************/
void preProcessEvents(){
    
    //Update Globals
    timeCurrent = (float)(glutGet(GLUT_ELAPSED_TIME) ) / 1000; //ms --> seconds
    dT = timeCurrent - timeOld;
    timeOld = timeCurrent;
    
    
    //from keyboardUtil.h
    handleKeyboard();
    

    //Mouse

    camView.du += (float)m_dX;
    camView.tl += (float)m_dY;
    
}

int secnds = 0;
void drawPoints(){


    
    
    if(loopCount < floor((double)(TimeM.rows - nFT)/(double)nOverlap)){
        clock_t clockT;
        clockT = clock();

        if(loopCount*nOverlap % 44000 == 0){
            cout << secnds << " seconds have passed." << endl;
            secnds++;
        }
        
        Mat partToDFT = TimeM.rowRange(loopCount*nOverlap,loopCount*nOverlap + nFT);
        Mat ftPart;
        dft(partToDFT, ftPart, DFT_COMPLEX_OUTPUT);
        
        double FTstepSize = floor((double)nFT/(double)nDraw);
        int cMapStepSize = (int)cMapJet.rows/(int)nDraw;
        
        //FT index
        int FTidx = 0;
        //Colormap Index
        int cIdx = 0;
        

        
        float radius;
        
        //Go through first half of FT
        for (int i = 0; i < nDraw/2; i++){
            
            //Calculate FT index
            FTidx = (int)FTstepSize*i;
            

            
            //Calculate colormap index
            cIdx = 2*(int)cMapStepSize*i;
            
            //Get magnitude
            float Mag = sqrt(pow(ftPart.at<complex<float>>(FTidx).real(),2) + pow(ftPart.at<complex<float>>(FTidx).imag(),2));
            radius = sinTheta*atan(Mag) + 0.01;
            
            //TESTING scaling logarithmically by magnitude
            // z = re^(i*theta) so plot z_ = log(r)e^(i*theta)
            
            
            //Supporting vars for drawing log(magnitude)
            float X;
            float Y;
            
            switch(plotType){
                case 0:
                    //Draw FT value before Nyquist
                    glColor3d(cMapJet.at<float>(cIdx,0), cMapJet.at<float>(cIdx,1), cMapJet.at<float>(cIdx,2));
                    glPushMatrix();
                    glTranslated(ftPart.at<complex<float>>(FTidx).real(), ftPart.at<complex<float>>(FTidx).imag(), 0.0);
                    glutSolidSphere(radius, 20, 20);
                    glPopMatrix();
            
                    //Draw complex conj of FT value w/ same color
                    glColor3d(cMapJet.at<float>(cIdx,0), cMapJet.at<float>(cIdx,1), cMapJet.at<float>(cIdx,2));
                    glPushMatrix();
                    glTranslated(ftPart.at<complex<float>>(FTidx).real(), -ftPart.at<complex<float>>(FTidx).imag(), 0.0);
                    glutSolidSphere(radius, 20, 20);
                    glPopMatrix();
                    break;
                case 1:
                    //Draw log magnitude with same color scheme
                    //Normalize vector and scale by log(||z||)
                    X = log(Mag+1)*ftPart.at<complex<float>>(FTidx).real()/Mag;
                    Y = log(Mag+1)*ftPart.at<complex<float>>(FTidx).imag()/Mag;
                    //Draw FT value before Nyquist
                    glColor3d(cMapJet.at<float>(cIdx,0), cMapJet.at<float>(cIdx,1), cMapJet.at<float>(cIdx,2));
                    glPushMatrix();
                    glTranslated(X, Y, 0.0);
                    glutSolidSphere(radius, 20, 20);
                    glPopMatrix();
                    
                    //Draw complex conj of FT value w/ same color
                    glColor3d(cMapJet.at<float>(cIdx,0), cMapJet.at<float>(cIdx,1), cMapJet.at<float>(cIdx,2));
                    glPushMatrix();
                    glTranslated(X, -Y, 0.0);
                    glutSolidSphere(radius, 20, 20);
                    glPopMatrix();
                    break;
            }
            
        }
        
        
        while (((float)clock() - (float)clockT)/CLOCKS_PER_SEC < g_Delay){};
        loopCount++;
    }
    else{
    
        cout << "Starting over." << endl;
        loopCount = 0;
    }
    
    
}

void display(){
    
    preProcessEvents();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(objPosition.lr, objPosition.du, objPosition.io);
    glRotatef(camView.du, 1, 0, 0);
    glRotatef(camView.lr, 0, 1, 0);
    glRotatef(camView.tl, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    
    
    //*************DRAWING*************
    
    //Draw Axes
    if(g_axes){
        // save previous matrix
        glPushMatrix();
        // draw our axes
        glLineWidth(2.0);
        glBegin(GL_LINES);
        // draw line for x axis
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
        // draw line for y axis
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
        // draw line for Z axis
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 1.0);
        glEnd();
        // load the previous matrix
        glPopMatrix();
    }
    
    //Draw Points
    drawPoints();
    
    //*************DRAWING*************

    
    glutSwapBuffers();
}


static void reshape(int w, int h){
    if ( h == 0 ){
        h = 1;
    }
    const float ar = (float) w / (float) h;
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2, 1000.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void keyboardDown(unsigned char key, int x, int y){
    KEYS[key] = true;
}

void keyboardUp(unsigned char key, int x, int y){
    KEYS[key] = false;
}

void keyboardSpecialDown(int key, int x, int y){
    
    keyboardSpecialDownUtil(key);

}

void keyboardSpecialUp(int key, int x, int y){
    
    keyboardSpecialUpUtil(key);
    
}

void mouseButton(int button, int state, int x, int y){
    
    if(button == GLUT_LEFT_BUTTON){
        m_buttonDown = !m_buttonDown;

        m_dX = 0;
        m_dY = 0;

        m_oldX = x;
        m_oldY = y;
    }
    

}

void mouseMotion(int x, int y){
    
    m_currentX = x;
    m_currentY = y;
    
    if(m_buttonDown){
        
        m_dX = m_currentX - m_oldX;
        m_dY = m_currentY - m_oldY;
    
        m_oldX = m_currentX;
        m_oldY = m_currentY;
    }
}

int main(int argc, char ** argv)
{
    //Time in mono
    FileStorage TFS("../../Data/Time.xml", FileStorage::READ);
    TFS["Time"] >> TimeM;
    TFS.release();
    
//    cout << "TimeM is " << TimeM.rows << " by " << TimeM.cols << endl;
//    Mat partToDFT = TimeM.rowRange(0, 9); //should take first 10 entries
//    cout << "partToDFT is " << partToDFT.rows << " by " << partToDFT.cols << endl;
//    Mat dftMat;
//    dft(partToDFT, dftMat, DFT_COMPLEX_OUTPUT);
//    cout << "dftMat is " << dftMat.rows << " by " << dftMat.cols << endl;
//    cout << "dftMat(0) is " << dftMat.at<complex<float>>(0) << endl;
//    complex<float> dftPoint = dftMat.at<complex<float>>(1);
//    cout << "dftPoint = " << dftPoint.real() << " + " << dftPoint.imag() << "i" << endl;
    
    //Real Part of Spectrogram
    FileStorage reSFS("../../Data/reSpec.xml", FileStorage::READ);
    reSFS["reSpec"] >> ReSpec;
    reSFS.release();
    
    //Imaginary Part of Spectrogram
    FileStorage imSFS("../../Data/imSpec.xml", FileStorage::READ);
    imSFS["imSpec"] >> ImSpec;
    imSFS.release();

    //Colormaps
    FileStorage cmJFS("../../Data/cMapJet.xml", FileStorage::READ);
    cmJFS["cMapJet"] >> cMapJet;
    cmJFS.release();
    
    cout << "cMapJet is " << cMapJet.rows << " by " << cMapJet.cols << endl;
    
    FileStorage cmAFS("../../Data/cMapAutumn.xml", FileStorage::READ);
    cmAFS["cMapAutumn"] >> cMapAutumn;
    cmAFS.release();
    
    FileStorage cmWFS("../../Data/cMapWinter.xml", FileStorage::READ);
    cmWFS["cMapWinter"] >> cMapWinter;
    cmWFS.release();
    
    //start glut
    glutInit(&argc, argv);
    
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(winWidth, winHeight);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    
    //create window
    glutCreateWindow(winTitle);
    
    
    //setup glut callback functions
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    
    glClearColor(0,0,0,0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    
    //Keyboard
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(keyboardSpecialDown);
    glutSpecialUpFunc(keyboardSpecialUp);
    
    //Mouse
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);

    
    //enter main loop
    glutMainLoop();
    
    return 0;
}

    
    








