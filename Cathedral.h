#ifndef Cathedral
#define Cathedral

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "CSCIx229.h"

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void tree(int treeDepth, double treeRadius, double treeHeight, double rotateAzimuth, double rotateElevation);

void sphere(double x, double y, double z, double xScale, double yScale, double zScale);

void cube(double x, double y, double z, double xScale, double yScale, double zScale, double rotateY, double rotateZ, unsigned int texture);

void pyramid(double x, double y, double z, double xScale, double yScale, double zScale, double rotateAngle, unsigned int texture);

void tower(double x, double y, double z, double xScale, double yScaleCube, double yScalePyramid, double zScale, double rotateAngle, unsigned int cubeTexture, unsigned int pyramidTexture);

void archCustom(double x, double y, double z, double xScale, double yScale, double zScale, double rotateAngle, double depth, double pillarHeight, double connectionLength, unsigned int *textures);

void adjustList(double x, double y, double z, double xScale, double yScale, double zScale, double rotateAngle, GLuint displayList);

void door(double x, double y, double z, double xScale, double yScale, double zScale, double rotateAngle, double pillarHeight, unsigned int texture);

void aboveArch(double x, double y, double z, double xScale, double yScale, double zScale, double rotateAngle, double pillarHeight, double aboveHeight, double pillarWidth, unsigned int *textures);

void drawAisleCompartment(double startZ, double insideX, unsigned int *archTextures, unsigned int doorTexture);

void drawStainedGlass(unsigned int stainedGlassTexture, unsigned int stainedGlassTexture2);

#ifdef __cplusplus
}
#endif

#endif
