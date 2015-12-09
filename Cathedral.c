#include "Cathedral.h"

// used as reference: http://mhzn.net/index.php/8-c-opengl/2-first-post
void tree(int treeDepth, double treeRadius, double treeHeight, double rotateAzimuth, double rotateElevation)
{
    if(treeRadius <= 1)
        treeRadius = 0.5;
    if(treeHeight <= 0)
        treeHeight = 5;
    if(treeHeight < 10*treeRadius)
        treeHeight = 10*treeRadius;
    if(rotateElevation <= 0)
        rotateElevation = 70;
    double az = 0.0;

    glBegin(GL_QUAD_STRIP);
    for(az = 0.0; az <= 360.0; az+=40)
    {
        glNormal3d(treeRadius*Sin(az),0,treeRadius*Cos(az));
        glVertex3d(treeRadius*Sin(az),0,treeRadius*Cos(az));
        glNormal3d(treeRadius*Sin(az),treeHeight,treeRadius*Cos(az));
        glVertex3d(treeRadius*Sin(az),treeHeight,treeRadius*Cos(az));
    }
    glEnd();

    if(treeDepth > 0)
    {
        int numBranches = rand() % 3 + 2;
        int angleSplit = 360/numBranches;
        int angle = rand() % 30 + 40;
        int t;
        for(t=0; t<numBranches;t++)
        {
            int heightRange = treeHeight/2;
            int heightDifference = rand() % heightRange;
            glPushMatrix();
            glTranslated(0,treeHeight,0);
            glRotated(90-rotateElevation, Cos(rotateAzimuth+60+t*angleSplit),0,Sin(rotateAzimuth+60+t*angleSplit));
            tree(treeDepth-1, treeRadius-1,treeHeight-heightDifference, rotateAzimuth+20,angle);
            glPopMatrix();
        }
    }
}

/*  Make a cube of unit length. Rotate, scale, and translate based on
    designated parameters. */
void cube(double x, double y, double z, double xScale, double yScale, double zScale, double rotateX, double rotateY, unsigned int texture)
{
    float gray[] = {0.1,0.1,0.1,1.0};

    glPushMatrix();
    glTranslated(x, y,z);
    glRotated(rotateY, 0,1,0);
    glRotated(rotateX, 1,0,0);
    glScaled(xScale, yScale, zScale);

    glColor3f(0.892,0.872,0.784);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,gray);

    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glNormal3d(-1.0,0.0,0.0);
    glTexCoord2f(0.0,yScale/6);
    glVertex3d(-0.5, 1.0, -0.5);
    glTexCoord2f(zScale/5,yScale/6);
    glVertex3d(-0.5, 1.0, 0.5);
    glTexCoord2f(zScale/5,0.0);
    glVertex3d(-0.5, 0.0, 0.5);
    glTexCoord2f(0.0,0.0);
    glVertex3d(-0.5, 0.0, -0.5);
    glEnd();


    glBegin(GL_QUADS);
    glNormal3d(1.0,0.0,0.0);
    glTexCoord2f(0.0,yScale/6);
    glVertex3d(0.5, 1.0, -0.5);
    glTexCoord2f(zScale/5,yScale/6);
    glVertex3d(0.5, 1.0, 0.5);
    glTexCoord2f(zScale/5,0.0);
    glVertex3d(0.5, 0.0, 0.5);
    glTexCoord2f(0.0,0.0);
    glVertex3d(0.5, 0.0, -0.5);
    glEnd();


    glBegin(GL_QUADS);
    glNormal3d(0.0,0.0,-1.0);
    glTexCoord2f(0.0,yScale/6);
    glVertex3d(-0.5, 1.0, -0.5);
    glTexCoord2f(xScale/5,yScale/6);
    glVertex3d(0.5, 1.0, -0.5);
    glTexCoord2f(xScale/5,0.0);
    glVertex3d(0.5, 0.0, -0.5);
    glTexCoord2f(0.0,0.0);
    glVertex3d(-0.5, 0.0, -0.5);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3d(0.0,0.0,1.0);
    glTexCoord2f(0.0,yScale/6);
    glVertex3d(-0.5, 1.0, 0.5);
    glTexCoord2f(xScale/5,yScale/6);
    glVertex3d(0.5, 1.0, 0.5);
    glTexCoord2f(xScale/5,0.0);
    glVertex3d(0.5, 0.0, 0.5);
    glTexCoord2f(0.0,0.0);
    glVertex3d(-0.5, 0.0, 0.5);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3d(0.0,1.0,0.0);
    glTexCoord2f(0.0,0.0);
    glVertex3d(-0.5, 1.0, -0.5);
    glTexCoord2f(xScale/5,0.0);
    glVertex3d(0.5, 1.0, -0.5);
    glTexCoord2f(xScale/5,zScale/6);
    glVertex3d(0.5, 1.0, 0.5);
    glTexCoord2f(0.0,zScale/6);
    glVertex3d(-0.5, 1.0, 0.5);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3d(0.0,-1.0,0.0);
    glTexCoord2f(0.0,0.0);
    glVertex3d(-0.5, 0.0, -0.5);
    glTexCoord2f(xScale/5,0.0);
    glVertex3d(0.5, 0.0, -0.5);
    glTexCoord2f(xScale/5,zScale/6);
    glVertex3d(0.5, 0.0, 0.5);
    glTexCoord2f(0.0,zScale/6);
    glVertex3d(-0.5, 0.0, 0.5);
    glEnd();

    glPopMatrix();
}

/*  Make a cube of unit length. Rotate, scale, and translate based on
    designated parameters. */
void pyramid(double x, double y, double z, double xScale, double yScale, double zScale, double rotateAngle, unsigned int texture)
{
    float gray[] = {0.1,0.1,0.1,1.0};

    glPushMatrix();
    glTranslated(x, y , z);
    glRotated(rotateAngle, 0,1,0);
    glScaled(xScale, yScale, zScale);

    glColor3f(0.892,0.872,0.784);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,gray);

    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_TRIANGLES);
    glNormal3d(0.0,0.5,-0.25);
    glTexCoord2f(xScale/10,yScale/6);
    glVertex3d(0.0,1.0,0.0);
    glNormal3d(0.0,0.5,-0.25);
    glTexCoord2f(0.0,0.0);
    glVertex3d(-0.5, 0.0, -0.5);
    glNormal3d(0.0,0.5,-0.25);
    glTexCoord2f(xScale/5,0.0);
    glVertex3d(0.5, 0.0, -0.5);


    glNormal3d(0.25,0.5,0.0);
    glTexCoord2f(zScale/10,yScale/6);
    glVertex3d(0.0,1.0,0.0);
    glNormal3d(0.25,0.5,0.0);
    glTexCoord2f(0.0,0.0);
    glVertex3d(0.5, 0.0, -0.5);
    glNormal3d(0.25,0.5,0.0);
    glTexCoord2f(zScale/5,0.0);
    glVertex3d(0.5, 0.0, 0.5);


    glNormal3d(0.0,0.5,0.25);
    glTexCoord2f(xScale/10,yScale/6);
    glVertex3d(0.0,1.0,0.0);
    glNormal3d(0.0,0.5,0.25);
    glTexCoord2f(0.0,0.0);
    glVertex3d(0.5, 0.0, 0.5);
    glNormal3d(0.0,0.5,0.25);
    glTexCoord2f(xScale/5,0.0);
    glVertex3d(-0.5, 0.0, 0.5);


    glNormal3d(-0.25,0.5,0.0);
    glTexCoord2f(zScale/10,yScale/6);
    glVertex3d(0.0,1.0,0.0);
    glNormal3d(-0.25,0.5,0.0);
    glTexCoord2f(0.0,0.0);
    glVertex3d(-0.5, 0.0, 0.5);
    glNormal3d(-0.25,0.5,0.0);
    glTexCoord2f(zScale/5,0.0);
    glVertex3d(-0.5, 0.0, -0.5);
    glEnd();

    glPopMatrix();
}

void tower(double x, double y, double z, double xScale, double yScaleCube, double yScalePyramid, double zScale, double rotateAngle, unsigned int cubeTexture, unsigned int pyramidTexture)
{
    cube(x,y,z, xScale,yScaleCube,zScale, 0,rotateAngle, cubeTexture);
    pyramid(x,y+yScaleCube,z, xScale,yScalePyramid,zScale, rotateAngle, pyramidTexture);
}

/*  Draw a sphere */
void sphere(double x, double y, double z, double xScale, double yScale, double zScale)
{
    double az;
    double el;

    glPushMatrix();
    glTranslated(x, y, z);
    glScaled(xScale, yScale, zScale);
    for(el = -90.0; el < 90; el+=0.5)
    {
        glBegin(GL_QUAD_STRIP);
        for(az = 0.0; az <= 360.0; az+=0.5)
        {
            glNormal3d(Sin(az)*Cos(el),Sin(el),Cos(az)*Cos(el));
            glVertex3d(Sin(az)*Cos(el),Sin(el),Cos(az)*Cos(el));
            glNormal3d(Sin(az)*Cos(el+0.5),Sin(el+0.5),Cos(az)*Cos(el+0.5));
            glVertex3d(Sin(az)*Cos(el+0.5),Sin(el+0.5),Cos(az)*Cos(el+0.5));
        }
        glEnd();
    }

    glPopMatrix();
}


/*  Draws the tops and bottoms of the arches for an arch that is between z
    and (z+width) and has legs that are height high.
*/
void arch(double z, double width, double height, double connectionLength, double wallTextureHeight, double wallTextureWidth, double roofTextureHeight, double roofTextureWidth, double xScale, unsigned int *textures)
{
    glBindTexture(GL_TEXTURE_2D, textures[1]);

    double roofTexWidthRatio = roofTextureWidth/width;
    double connectionTextureWidth = roofTexWidthRatio * connectionLength;
    double y = 0;
    glBegin(GL_QUAD_STRIP);
    //arch top
    double i;
    for(i=-25; i <= 25; i+=0.5)
    {
        if(i <= 0)
        {
            y = sqrt(2500 - pow(i-25,2)) - 7.5 + height;
            glNormal3d(i-25,y,0);
        }
        else
        {
            y = sqrt(2500 - pow(i+25,2)) - 7.5 + height;
            glNormal3d(i+25,y,0);
        }
        if(i==0)
        {
            glNormal3d(0,1,0);
        }
        glTexCoord2f(roofTextureWidth,roofTextureHeight*(25-fabs(i))/25);
        glVertex3d(i,y,z);
        glTexCoord2f(0.0,roofTextureHeight*(25-fabs(i))/25);
        glVertex3d(i,y,(z+width));
    }
    glEnd();

    //archConnection
    glBegin(GL_QUAD_STRIP);
    for(i=-25; i <= 25; i+=0.5)
    {
        double len = (25-fabs(i))*connectionLength/25;
        if(i <= 0)
        {
            y = sqrt(2500 - pow(i-25,2)) - 7.5 + height;
            glNormal3d(i-25,y,0);
        }
        else
        {
            y = sqrt(2500 - pow(i+25,2)) - 7.5 + height;
            glNormal3d(i+25,y,0);
        }
        if(i==0)
        {
            glNormal3d(0,1,0);
        }
        glTexCoord2f(0.0,roofTextureHeight*(25-fabs(i))/25);
        glVertex3d(i,y,(z+width));
        glTexCoord2f(connectionTextureWidth*(25-fabs(i))/25,roofTextureHeight*(25-fabs(i))/25);
        glVertex3d(i,y,z+width+len);
    }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures[0]);

    //arch wall
    glBegin(GL_QUADS);

    //top
    glNormal3d(-1.0,0.0,0.0);
    glTexCoord2f(wallTextureWidth,0.0);
    glVertex3d(-25.0, (sqrt(2500 - pow(50,2)) - 7.5 + height), z);
    glTexCoord2f(0.0,0.0);
    glVertex3d(-25.0, (sqrt(2500 - pow(50,2)) - 7.5 + height), (z+width));
    glTexCoord2f(0.0,wallTextureHeight/2.0);
    glVertex3d(-25.0, (sqrt(2500 - pow(50,2)) - 7.5 + height)/2.0, (z+width));
    glTexCoord2f(wallTextureWidth,wallTextureHeight/2.0);
    glVertex3d(-25.0, (sqrt(2500 - pow(50,2)) - 7.5 + height)/2.0, z);
    glEnd();

    //opposing arch wall
    glBegin(GL_QUADS);

    //top
    glNormal3d(1.0,0.0,0.0);
    glTexCoord2f(wallTextureWidth,0.0);
    glVertex3d(25.0, (sqrt(2500 - pow(50,2)) - 7.5 + height), z);
    glTexCoord2f(0.0,0.0);
    glVertex3d(25.0, (sqrt(2500 - pow(50,2)) - 7.5 + height), (z+width));
    glTexCoord2f(0.0,wallTextureHeight/2.0);
    glVertex3d(25.0, (sqrt(2500 - pow(50,2)) - 7.5 + height)/2.0, (z+width));
    glTexCoord2f(wallTextureWidth,wallTextureHeight/2.0);
    glVertex3d(25.0, (sqrt(2500 - pow(50,2)) - 7.5 + height)/2.0, z);
    glEnd();
}

/*  Draws a custom arch and translates, rotates, and scales it.
    Inputs:
    x,y,z - translation coordinates.
    xScale,yScale,Zscale - scale values.
    rotateAngle - Angle to rotate arch around y axis.
    depth - the depth of the arch
    pillarHeight - the height of the vertical pillars of the arch
*/
void archCustom(double x, double y, double z, double xScale, double yScale, double zScale, double rotateAngle, double depth, double pillarHeight, double connectionLength, unsigned int *textures)
{
    float gray[] = {0.1,0.1,0.1,1.0};

    glPushMatrix();
    glTranslated(x, y , z);
    glRotated(rotateAngle, 0,1,0);
    glScaled(xScale, yScale, zScale);
    glColor3f(0.892,0.872,0.784);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,gray);
    // draw arch
    arch(-depth/2, depth, pillarHeight, connectionLength, yScale*pillarHeight/9, zScale*depth/6, 0.5, zScale*depth/220, xScale, textures);
    glPopMatrix();

}

void adjustList(double x, double y, double z, double xScale, double yScale, double zScale, double rotateAngle, GLuint displayList)
{
    glPushMatrix();
    glTranslated(x, y, z);
    glRotated(rotateAngle, 0,1,0);
    glScaled(xScale, yScale, zScale);

    glCallList(displayList);

    glPopMatrix();
}

void door(double x, double y, double z, double xScale, double yScale, double zScale, double rotateAngle, double pillarHeight, unsigned int texture)
{
    float gray[] = {0.5,0.5,0.5,1.0};


    glPushMatrix();
    glTranslated(x, y, z);
    glRotated(rotateAngle, 0,1,0);
    glScaled(xScale, yScale, zScale);

    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,gray);

    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUAD_STRIP);
    //arch top
    double i;
    for(i=-25; i <= 25; i+=0.5)
    {
        if(i <= 0)
        {
            y = sqrt(2500 - pow(i-25,2)) - 7.5 + pillarHeight;
            glNormal3d(0,0,1);
        }
        else
        {
            y = sqrt(2500 - pow(i+25,2)) - 7.5 + pillarHeight;
            glNormal3d(0,0,1);
        }
        double relativeHeight = y/(sqrt(2500 - pow(25,2)) - 7.5 + pillarHeight);
        glTexCoord2f((i+25)/50,0.0);
        glVertex3d(i,0,0);
        glTexCoord2f((i+25)/50,relativeHeight);
        glVertex3d(i,y,0);
    }
    glEnd();

    glPopMatrix();
}

void aboveArch(double x, double y, double z, double xScale, double yScale, double zScale, double rotateAngle, double pillarHeight, double aboveHeight, double pillarWidth, unsigned int *textures)
{
    float gray[] = {0.1,0.1,0.1,1.0};

    double wallTextureHeight = yScale*(sqrt(2500 - pow(25,2)) - 7.5 + pillarHeight+aboveHeight)/9;
    double wallTextureWidth = xScale*(2*pillarWidth+50)/6;
    double pillarRelativeSize = pillarWidth/(2*pillarWidth+50);
    double overArchRelativeSize = 50/(2*pillarWidth+50);

    glPushMatrix();
    glTranslated(x, y, z);
    glRotated(rotateAngle, 0,1,0);
    glScaled(xScale, yScale, zScale);

    glColor3f(0.892,0.872,0.784);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,gray);

    glBindTexture(GL_TEXTURE_2D, textures[0]);

    glBegin(GL_QUAD_STRIP);
    //arch top
    double i;
    for(i=-25; i <= 25; i+=0.5)
    {
        if(i <= 0)
        {
            y = sqrt(2500 - pow(i-25,2)) - 7.5 + pillarHeight;
            glNormal3d(0,0,1);
        }
        else
        {
            y = sqrt(2500 - pow(i+25,2)) - 7.5 + pillarHeight;
            glNormal3d(0,0,1);
        }
        double relativeHeight = 1-(y/(sqrt(2500 - pow(25,2)) - 7.5 + pillarHeight+aboveHeight));
        glTexCoord2f(overArchRelativeSize*wallTextureWidth*(i+25)/50,relativeHeight*wallTextureHeight);
        glVertex3d(i,y,0);
        glTexCoord2f(overArchRelativeSize*wallTextureWidth*(i+25)/50,0.0);
        glVertex3d(i,sqrt(2500 - pow(25,2)) - 7.5 + pillarHeight+aboveHeight,0);
    }
    glEnd();

    glBegin(GL_QUADS);
    glNormal3d(0,0,1);
    glTexCoord2f(pillarRelativeSize*wallTextureWidth,wallTextureHeight);
    glVertex3d(25,0,0);
    glTexCoord2f(pillarRelativeSize*wallTextureWidth,0.0);
    glVertex3d(25,sqrt(2500 - pow(25,2)) - 7.5 + pillarHeight+aboveHeight,0);
    glTexCoord2f(0.0,0.0);
    glVertex3d(25+pillarWidth,sqrt(2500 - pow(25,2)) - 7.5 + pillarHeight+aboveHeight,0);
    glTexCoord2f(0.0,wallTextureHeight);
    glVertex3d(25+pillarWidth,0,0);

    glTexCoord2f(pillarRelativeSize*wallTextureWidth,wallTextureHeight);
    glNormal3d(0,0,1);
    glVertex3d(-25,0,0);
    glTexCoord2f(pillarRelativeSize*wallTextureWidth,0.0);
    glVertex3d(-25,sqrt(2500 - pow(25,2)) - 7.5 + pillarHeight+aboveHeight,0);
    glTexCoord2f(0.0,0.0);
    glVertex3d(-(25+pillarWidth),sqrt(2500 - pow(25,2)) - 7.5 + pillarHeight+aboveHeight,0);
    glTexCoord2f(0.0,wallTextureHeight);
    glVertex3d(-(25+pillarWidth),0,0);
    glEnd();

    glPopMatrix();
}

void drawStainedGlass(unsigned int stainedGlassTexture, unsigned int stainedGlassTexture2)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1,1,1,0.7);
    int i;
    for(i=-795; i<=825; i+=220)
    {
        door(150, 241.5, i+50, 2,1,1, 90, 91.5, stainedGlassTexture);
        door(150, 241.5, i+160, 2,1,1, 90, 91.5, stainedGlassTexture);
        door(-150, 241.5, i+50, 2,1,1, -90, 91.5, stainedGlassTexture);
        door(-150, 241.5, i+160, 2,1,1, -90, 91.5, stainedGlassTexture);
        if(i == 85)
        {
            i = 385;
        }
    }

    door(0, 275, -850, 5,2,1, 0, 80, stainedGlassTexture2);
    door(0, 275, -950, 5,2,1, 180, 80, stainedGlassTexture2);
}

void drawAisleCompartment(double startZ, double insideX, unsigned int *archTextures, unsigned int doorTexture)
{
    archCustom(insideX+110,-105,startZ, 4,2,1, 0, 10,102.5, 100, archTextures);
    archCustom(insideX+5,-105,startZ+105, 4,2,1, 90, 10,102.5, 100, archTextures);
    archCustom(insideX+215,-105,startZ+105, 4,2,1, 270, 10,102.5, 100, archTextures);
    archCustom(insideX+110,-105,startZ+210, 4,2,1, 180, 10,102.5, 100, archTextures);
    glColor4f(0.289,0.152,0.0859,1.0);
    door(insideX+220, -10, startZ+105, 4,2,1, 90, 55, doorTexture);
    aboveArch(insideX, -10, startZ+105, 4,2,1, 90, 55,35, 2.5, archTextures);
    aboveArch(insideX+220, -10, startZ+105, 4,2,1, 90, 55,2, 2.5, archTextures);
    aboveArch(insideX, 233, startZ+50, 2,1,1, 90, 100,35, 2.5, archTextures);
    aboveArch(insideX, 233, startZ+160, 2,1,1, 90, 100,35, 2.5, archTextures);
    insideX = -1*insideX;
    archCustom(insideX-110,-105,startZ+210, 4,2,1, 180, 10,102.5, 100, archTextures);
    archCustom(insideX-215,-105,startZ+105, 4,2,1, 90, 10,102.5, 100, archTextures);
    archCustom(insideX-5,-105,startZ+105, 4,2,1, 270, 10,102.5, 100, archTextures);
    archCustom(insideX-110,-105,startZ, 4,2,1, 0, 10,102.5, 100, archTextures);
    glColor4f(0.289,0.152,0.0859,1.0);
    door(insideX-220, -10, startZ+105, 4,2,1, 270, 55, doorTexture);
    aboveArch(insideX, -10, startZ+105, 4,2,1, 270, 55,35, 2.5, archTextures);
    aboveArch(insideX-220, -10, startZ+105, 4,2,1, 270, 55,2, 2.5, archTextures);
    aboveArch(insideX, 233, startZ+50, 2,1,1, 270, 100,35, 2.5, archTextures);
    aboveArch(insideX, 233, startZ+160, 2,1,1, 270, 100,35, 2.5, archTextures);
}
