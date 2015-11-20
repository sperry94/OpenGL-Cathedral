//SETH PERRY

//class examples used as references/resources
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

//library from class
#include "CSCIx229.h"
#include "Cathedral.h"

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//Azimuth
int th=0;
//Elevation
int ph=0;

//Projection variables
int mode = 1;
int fov=55;
double asp=1;
double dim=860.0;

//first person location
double xOffset = 0;
double yOffset = 0;
double zOffset = -600;

unsigned int insideArchTextures[2];
unsigned int outsideArchTextures[2];
unsigned int skyTextures[2];
unsigned int altarTexture;
unsigned int woodTexture;
unsigned int stainedGlassTexture;
unsigned int groundTexture;
unsigned int tileTexture;


int numTrees = 100;
double treeLocations[100][2];

GLuint treeList;
GLuint cathedralList;
GLuint towerList;
GLuint pewList;
GLuint naveAisleList;
GLuint pew;
GLuint floorList;

void checkOffsets()
{
    if(xOffset > 2000)
        xOffset = 2000;
    else if(xOffset < -2000)
        xOffset = -2000;
    if(zOffset > 2000)
        zOffset = 2000;
    else if(zOffset < -2000)
        zOffset = -2000;
}

//Used to assign actions to keyboard presses.
void key(unsigned char ch,int x,int y)
{
    //change the mode of viewing the scene
    if(ch == '1')
    {
        mode = 0;
        dim = 860;
        th = 0;
        ph = 0;
    }
    //change the mode of viewing the scene
    else if(ch == '2')
    {
        mode = 1;
        dim = 800;
        th = 0;
        ph = 0;
        xOffset = 0;
        yOffset = 0;
        zOffset = -1500;
    }
    //reset angle using 4
    if(ch == '4')
    {
        th=0;
        ph=0;
    }
    //reset zoom using 5
    else if(ch == '5')
        dim=860;
    //reset first person location using 6
    else if(ch == '6')
    {
        xOffset = 0;
        yOffset = 0;
        zOffset = -1500;
    }
    //exit using esc
    else if(ch == 27)
        exit(0);
    //zoom out
    else if(ch == '[')
        dim += 30;
    //zoom in
    else if(ch == ']')
        dim -= 30;
    //FIRST PERSON NAVIGATION WITH WASD
    else if(ch == 'w' || ch == 'W')
    {
        xOffset -= 20*Sin(th);
        zOffset += 20*Cos(th);
        checkOffsets();
    }
    else if(ch == 's' || ch == 'S')
    {
        xOffset += 20*Sin(th);
        zOffset -= 20*Cos(th);
        checkOffsets();
    }
    else if(ch == 'a' || ch == 'A')
    {
        xOffset -= 20*Sin(th-90);
        zOffset += 20*Cos(th-90);
        checkOffsets();
    }
    else if(ch == 'd' || ch == 'D')
    {
        xOffset += 20*Sin(th-90);
        zOffset -= 20*Cos(th-90);
        checkOffsets();
    }
    //ensures dimension is never too small to fit arch.
    if(dim < 0)
        dim = 0;

    Project(fov, asp, dim);

    //Tells GLUT to redisplay.
    glutPostRedisplay();
}

//Used to assign actions to arrow key presses.
void special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT)
        th -= 5;
    else if(key == GLUT_KEY_RIGHT)
        th += 5;
    else if(key == GLUT_KEY_UP)
        ph += 5;
    else if(key == GLUT_KEY_DOWN)
        ph -= 5;

    //ensures th and ph are always between 0 and 360
    th %= 360;
    ph %= 360;

    Project(fov,asp,dim);

    //tell GLUT to redisplay.
    glutPostRedisplay();
}

// Code for reshape from ex7
//Handles window resizing.
void reshape(int width,int height)
{
    //  Ratio of the width to the height of the window
    asp = (height>0) ? (double)width/height : 1;
    //  Set the viewport to the entire window
    glViewport(0,0, width,height);
    //  Set projection
    Project(fov,asp,dim);
}

void determineTreeLocations()
{
    int numTreesPerQuadrant = numTrees/4;
    int t;
    for(t=0;t<numTreesPerQuadrant;t++)
    {
        treeLocations[t][0] = rand() % 4000 - 3000;
        treeLocations[t][1] = rand() % 1600 - 3000;
    }
    for(t=numTreesPerQuadrant;t<2*numTreesPerQuadrant;t++)
    {
        treeLocations[t][0] = rand() % 2000 - 3000;
        treeLocations[t][1] = rand() % 4400 - 1400;
    }
    for(t=2*numTreesPerQuadrant;t<3*numTreesPerQuadrant;t++)
    {
        treeLocations[t][0] = rand() % 4000 - 1000;
        treeLocations[t][1] = rand() % 1800 + 1500;
    }
    for(t=3*numTreesPerQuadrant;t<numTrees;t++)
    {
        treeLocations[t][0] = rand() % 2000 + 1000;
        treeLocations[t][1] = rand() % 4200 - 3000;
    }
}

void idle()
{}

//Used to display the scene.
void display()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    float Ambient[]   = {0.3 ,0.3 ,0.3 ,1.0};
    float Diffuse[]   = {1.0 ,1.0 ,1.0 ,1.0};

    if(mode == 0)
    {
        //Set up perspective projection
        double Ex = 5*dim*Sin(th)*Cos(ph);
        double Ey = 5*dim*Sin(ph);
        double Ez = -5*dim*Cos(th)*Cos(ph);
        gluLookAt(Ex,Ey,Ez ,0,0,0, 0,Cos(ph),0);
    }
    else
    {
        //Set up first person projection
        double Cx = -5*dim*Sin(th)*Cos(ph) + xOffset;
        double Cy = 5*dim*Sin(ph) + yOffset;
        double Cz = 5*dim*Cos(th)*Cos(ph) + zOffset;
        gluLookAt(xOffset,yOffset,zOffset ,Cx,Cy,Cz, 0,Cos(ph),0);
    }

    //Enable depth test.
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_NORMALIZE);

    //float light0Position[] = {5*dim, dim/2, -5*dim, 1.0};
    float light0Position[] = {0, 0, 0, 1.0};

    //make sphere at position of light
    glColor4f(1,1,1,1);
    sphere(light0Position[0], light0Position[1], light0Position[2], 10,10,10);

    //enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    sky(5*dim,skyTextures);

    //enable lighting
    glEnable(GL_LIGHTING);

    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    //set light to be at position
    glLightfv(GL_LIGHT0,GL_POSITION,light0Position);

    //enable light 0
    glEnable(GL_LIGHT0);

    //set ambient and diffuse components of light 0
    glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);

    //make arches
    glCallList(cathedralList);

    glCallList(pewList);

    glCallList(towerList);

    glCallList(treeList);

    glCallList(floorList);

    glColor4f(0.0,0.75,0.0,1.0);

    glBindTexture(GL_TEXTURE_2D, groundTexture);

    //grass
    glBegin(GL_QUADS);
    glNormal3d(0.0,1.0,0.0);
    glTexCoord2f(0.0,0.0);
    glVertex3f(-5*dim,-10.0,-5*dim);
    glNormal3d(0.0,1.0,0.0);
    glTexCoord2f(0.0,5*dim/4);
    glVertex3f(-5*dim,-10.0,5*dim);
    glNormal3d(0.0,1.0,0.0);
    glTexCoord2f(5*dim/4,5*dim/4);
    glVertex3f(5*dim,-10.0,5*dim);
    glNormal3d(0.0,1.0,0.0);
    glTexCoord2f(5*dim/4,0.0);
    glVertex3f(5*dim,-10.0,-5*dim);
    glEnd();

    drawStainedGlass(stainedGlassTexture);

    glDisable(GL_TEXTURE_2D);

    //Print projection type in bottom left corner
    glColor3f(1,1,1);
    glWindowPos2i(5,5);
    if(mode == 0)
    {
        Print("Projection Type: Perspective");
        glWindowPos2i(5,25);
        Print("Dimension: %.0f", dim);
    }
    else
    {
        Print("Projection Type: First Person");
        glWindowPos2i(5,25);
        Print("User Location: { %.3f, %.3f, %.3f }", xOffset, yOffset, zOffset);
    }

    //check for errors
    ErrCheck("display");

    //Render scene
    glFlush();
    glutSwapBuffers();
}

void loadTextures()
{
    //load textures
    //wall texture for arches.
    outsideArchTextures[0] = LoadTexBMP("textures/wallTexture.bmp");
    //roof texture for arches.
    outsideArchTextures[1] = LoadTexBMP("textures/roofTexture.bmp");
    insideArchTextures[0] = outsideArchTextures[0];
    insideArchTextures[1] = LoadTexBMP("textures/cathedralCeiling.bmp");
    //texture for ground
    groundTexture = LoadTexBMP("textures/groundTexture.bmp");
    //texture for skybox
    skyTextures[0] = LoadTexBMP("textures/skyTop.bmp");
    skyTextures[1] = LoadTexBMP("textures/skySide.bmp");
    altarTexture = LoadTexBMP("textures/marbleTexture.bmp");
    woodTexture = LoadTexBMP("textures/woodTexture.bmp");
    stainedGlassTexture = LoadTexBMP("textures/stainedGlassTexture.bmp");
    tileTexture = LoadTexBMP("textures/tileTexture.bmp");
}

void generateDisplayLists()
{
    treeList = glGenLists(1);
    glNewList(treeList, GL_COMPILE);
    int t;
    for(t=0; t< numTrees; t++)
    {
        int depth = rand() % 3 + 4;
        int angle = rand() % 30 + 30;
        glPushMatrix();
        glTranslated(treeLocations[t][0],-10,treeLocations[t][1]);
        tree(depth, 5,100, 0,angle);
        glPopMatrix();
    }
    glEndList();

    cathedralList = glGenLists(1);
    glNewList(cathedralList, GL_COMPILE);
    //main cathedral
    archCustom(370,-9.9,450, 6,6,1, 270, 440,75, 150, insideArchTextures);
    archCustom(-370,-9.9,450, 6,6,1, 90, 440,75, 150, insideArchTextures);
    archCustom(0,440,-300, 6,6,1, 0, 1200,0, 150, insideArchTextures);
    archCustom(0,440,825, 6,6,1, 180, 450,0, 150, insideArchTextures);

    //roof of cathedral
    archCustom(370,440,450, 6.01,6.5,1, 270, 440,0, 150, outsideArchTextures);
    archCustom(-370,440,450, 6.01,6.5,1, 90, 440,0, 150, outsideArchTextures);
    archCustom(0,440,-300, 6.01,6.5,1, 0, 1200,0, 150, outsideArchTextures);
    archCustom(0,440,825, 6.01,6.5,1, 180, 450,0, 150, outsideArchTextures);

    //TO DO: FIX OVERLAP UNDERNEATH
    //front aisles

    cube(260,204.47,-250, 1099.5,1,227.75, 15,90, outsideArchTextures[1]);
    cube(-260,204.47,-250, 1099.5,1,227.75, 15,-90, outsideArchTextures[1]);

    cube(260,204.47,820, 439.5,1,227.75, 15,90, outsideArchTextures[1]);
    cube(-260,204.47,820, 439.5,1,227.75, 15,-90, outsideArchTextures[1]);

    drawAisleCompartment(-795,150, insideArchTextures, woodTexture);
    drawAisleCompartment(-575,150, insideArchTextures, woodTexture);
    drawAisleCompartment(-355,150, insideArchTextures, woodTexture);
    drawAisleCompartment(-135,150, insideArchTextures, woodTexture);
    drawAisleCompartment(85,150, insideArchTextures, woodTexture);

    //back aisles

    drawAisleCompartment(605,150, insideArchTextures, woodTexture);
    drawAisleCompartment(820,150, insideArchTextures, woodTexture);

    //doors on crossing
    aboveArch(-260, -10, 300, 4,2,1, 180, 55,35, 2.5, insideArchTextures);
    aboveArch(-480, -10, 300, 4,2,1, 180, 55,35, 2.5, insideArchTextures);
    door(-480, -10, 300, 4,2,1, 180, 55, woodTexture);

    aboveArch(260, -10, 300, 4,2,1, 180, 55,35, 2.5, insideArchTextures);
    aboveArch(480, -10, 300, 4,2,1, 180, 55,35, 2.5, insideArchTextures);
    door(480, -10, 300, 4,2,1, 180, 55, woodTexture);

    aboveArch(-260, -10, 600, 4,2,1, 0, 55,35, 2.5, insideArchTextures);
    aboveArch(-480, -10, 600, 4,2,1, 0, 55,35, 2.5, insideArchTextures);
    door(-480, -10, 600, 4,2,1, 0, 55, woodTexture);

    aboveArch(260, -10, 600, 4,2,1, 0, 55,35, 2.5, insideArchTextures);
    aboveArch(480, -10, 600, 4,2,1, 0, 55,35, 2.5, insideArchTextures);
    door(480, -10, 600, 4,2,1, 0, 55, woodTexture);

    //altar
    cube(0,-10.1,830, 300,2.5,450, 0,0, woodTexture);
    cube(0,-7.5,700, 50,10,20, 0,0, altarTexture);
    cube(0,2.5,700, 60,2.5,30, 0,0, altarTexture);

    glEndList();

    naveAisleList= glGenLists(1);
    glNewList(naveAisleList, GL_COMPILE);

    glEndList();

    towerList = glGenLists(1);
    glNewList(towerList, GL_COMPILE);
    //front towers
    tower(0,-10.1,-950, 300,675,400,100, 0, insideArchTextures[0],outsideArchTextures[1]);
    tower(260.1,-10.1,-875, 220,500,475,150, 0, insideArchTextures[0],outsideArchTextures[1]);
    tower(-260.1,-10.1,-875, 220,500,475,150, 0, insideArchTextures[0],outsideArchTextures[1]);
    //back towers
    tower(0,-10,1180, 300,675,400,250, 0, insideArchTextures[0],outsideArchTextures[1]);
    tower(260.1,-10.1,1180, 220,675,300,300, 0, insideArchTextures[0],outsideArchTextures[1]);
    tower(-260.1,-10.1,1180, 220,675,300,300, 0, insideArchTextures[0],outsideArchTextures[1]);
    //left tower
    tower(640,-10.1,450, 350,675,300,100, 90, insideArchTextures[0],outsideArchTextures[1]);
    //right tower
    tower(-640,-10.1,450, 350,675,300,100, 90, insideArchTextures[0],outsideArchTextures[1]);
    glEndList();

    pew = LoadOBJ("pew.obj");

    pewList = glGenLists(1);
    glNewList(pewList, GL_COMPILE);
    glColor4f(0.289,0.160,0.082,1);
    int pewX;
    int pewZ;
    for(pewX=35; pewX <=110; pewX += 25)
    {
        for(pewZ=-300; pewZ <= 240; pewZ +=15)
        {
            adjustList(pewX,-10,pewZ, 2,2,2, 180,pew);
            adjustList(-1*pewX,-10,pewZ, 2,2,2, 180,pew);
        }
    }
    glEndList();

    floorList = glGenLists(1);
    glNewList(floorList, GL_COMPILE);
    glColor4f(0.868,0.805,0.699,1);
    glBindTexture(GL_TEXTURE_2D, tileTexture);
    glBegin(GL_QUADS);
    glNormal3d(0,1,0);
    glTexCoord2f(0.0,0.0);
    glVertex3d(-370.0,-9.9,-900.0);
    glTexCoord2f(0.0,193.5);
    glVertex3d(-370.0,-9.9,1035.0);
    glTexCoord2f(74.0,193.5);
    glVertex3d(370.0,-9.9,1035.0);
    glTexCoord2f(74.0,0.0);
    glVertex3d(370.0,-9.9,-900.0);

    glNormal3d(0,1,0);
    glTexCoord2f(0.0,0.0);
    glVertex3d(-600.0,-9.9,300.0);
    glTexCoord2f(0.0,30.0);
    glVertex3d(-600.0,-9.9,600.0);
    glTexCoord2f(120.0, 30.0);
    glVertex3d(600.0,-9.9,600.0);
    glTexCoord2f(120.0, 0.0);
    glVertex3d(600.0,-9.9,300.0);
    glEnd();
    glEndList();
}

int main(int argc,char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Textures Assignment (Seth Perry)");
    //sets the function that handles window reshaping to reshape.
    glutReshapeFunc(reshape);
    //sets the display function to display
    glutDisplayFunc(display);
    //set the idle function to idle
    glutIdleFunc(idle);
    //sets the special key function to special
    glutSpecialFunc(special);
    //sets the keyboard function to key
    glutKeyboardFunc(key);

    loadTextures();

    determineTreeLocations();

    generateDisplayLists();

    pew=LoadOBJ("pew.obj");

    //check for errors
    ErrCheck("init");
    //gives control to GLUT so user input can be managed.
    glutMainLoop();
    return 0;
}
