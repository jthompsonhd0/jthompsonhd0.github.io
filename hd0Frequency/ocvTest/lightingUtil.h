//
//  lightingUtil.h
//  OpenGL Tutorial2
//
//  Created by Justin Thompson on 8/8/14.
//  Copyright (c) 2014 Justin Thompson. All rights reserved.
//

#ifndef OpenGL_Tutorial2_lightingUtil_h
#define OpenGL_Tutorial2_lightingUtil_h

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <opencv/cv.h>
#include "math.h"

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };



#endif
