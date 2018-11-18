/*
* Submitted by Akhil Varma Alluri
*/
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#define PI 3.14159
#define max_ctlpts 14

using namespace std;

bool WireFrame= false;

float xp[max_ctlpts],yp[max_ctlpts],zp[max_ctlpts];
float p,q; //for x&y mouse pts
float t;
float i=0;
bool flag=false;

int cpts = 0; //count control points
float xpos =0;
float ypos =0;
float zpos =0;
float newAngle =0;
//float n=0;

float z =-3.0;

//bool val = 0;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


float Wwidth,Wheight;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
     double Ratio;

     Wwidth = (float)width;
     Wheight = (float)height;

     Ratio= (double)width /(double)height;

    glViewport(0,0,(GLsizei) width,(GLsizei) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	gluPerspective (45.0f,Ratio,0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

 }

//implementing formula

float fact(float num)
{

    if(num==1 || num==0)
    {
        return 1;
    }
    else
    {
        return (num*fact(num-1));
    }
}

//binomial coefficient logic

float bin_coeff(float n,float i)
{
    float val;
    val= fact(n) / (fact(i)*fact(n-i));
    return val;
}

//display function

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,10.0,0.0,0.0,0.0,0.0,1.0,100.0);

    glRotatef(newAngle,0.0,1.0,0.0);  //used for rotation around y axis

    if(WireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME



 glPointSize(5);
 glBegin(GL_POINTS);

//logic for togging points on and off

 if(flag==false)
 {
     for(int i=0; i<cpts;i++)
     {
         glVertex3f(xp[i],yp[i],zp[i]);
     }
 }
 else if(flag==true)
 {
     for(int i=0;i<cpts;i++)
     {

     }
 }
glEnd();

//logic for bezier curve implementation

 glPointSize(2);
 glColor3f(1.0,1.0,1.0);

 if(cpts>2)
 {
    for(int j=3;j<=cpts;j++)
    {
     for(t=0;t<=1;t=t+0.005)
     {
         for(int i=0;i<j;i++)
         {
             xpos += bin_coeff(j-1,i)*pow(t,i)*pow(1-t,j-1-i)*xp[i];
             ypos += bin_coeff(j-1,i)*pow(t,i)*pow(1-t,j-1-i)*yp[i];
             zpos += bin_coeff(j-1,i)*pow(t,i)*pow(1-t,j-1-i)*zp[i];

         }
         glBegin(GL_POINTS);
         glVertex3f(xpos,ypos,zpos);
         glEnd();
         xpos=0;
         ypos=0;
         zpos=0;
     }
  }
 }


glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 : //esc
        case 32 : //space bar
            cpts=0;
            glutPostRedisplay();
            break;
        case 'q':  //exit
            exit(0);
            break;

	  case 'w':
		WireFrame =!WireFrame;
	       break;
    }
}

//logic for turning the diagram with a certain angle
void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
      case GLUT_KEY_RIGHT:
            {
                newAngle +=10;
            }
            break;

         case GLUT_KEY_LEFT:
            {
                newAngle -=10;
            }
            break;
   }
  glutPostRedisplay();
}


static void idle(void)
{
    // Use parametric equation with t increment for xpos and ypos
    // Don't need a loop
     glutPostRedisplay();
}

//logic for mouse button registration

void mouse(int btn, int state, int x, int y){

    float scale = 54*(Wwidth/Wheight);

     printf(" original %d %d %d \n", x,y,z);
    switch(btn){

        case GLUT_LEFT_BUTTON:

        if(state==GLUT_DOWN){
                    if(cpts<15)
                    {
                    p = (x -(Wwidth/2))/scale; // Get the mouse x and y coordinate, and translate based on origin.
                    q = ((Wheight/2) - y)/scale;

                    xp[cpts] = p;
                    yp[cpts] = q;
                    zp[cpts] = z;
                    z+=0.2;
                    cpts++;
                    }
                }
            break;

        case GLUT_RIGHT_BUTTON:
            {
                if(state==GLUT_DOWN){
                    if(flag==false){
                    flag=true;
                    }

                    else
                    {
                        flag=false;
                    }
              }
                }
             break;
}
  glutPostRedisplay();
};



static void init(void)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClearColor(0.5f, 0.5f, 1.0f, 0.0f);                 // assign a color you like

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(800,600);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Project Assignment 3");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);
   glutSpecialFunc(Specialkeys);

    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
