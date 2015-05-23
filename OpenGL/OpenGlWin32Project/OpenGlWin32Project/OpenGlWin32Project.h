#pragma once

#include "resource.h"
#include <gl/GL.h>


int InitGL(GLvoid);

GLvoid ReSizeGLScene(GLsizei width, GLsizei height);

void Render();

void DrawRobot(float xPos, float yPos, float zPos);


