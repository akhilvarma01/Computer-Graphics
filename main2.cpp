/* Name - AKHIL VARMA ALLURI
*/
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
//#include <GL/freeglut.h>

using namespace std;

static int slices = 50; static int stacks = 50; // defined second and third coordinates of sphere

double xsphere = -3.5;
double ysphere= 0.0;
double zsphere = -1.0;                  //given coordinates mentioned in assignment
double radius = 1.3;
double scaleSphere = 1.0;

double xcube = 4.0;
double ycube = 0.0;
double zcube = -2.0;
double scaleCube = 1.0;

double xtea = 0.0 ;
double ytea =0.0;
double ztea = -3.0;
double scaleTeapot = 1.0;


bool sval =0, cval =0, tval =0;        //boolean value flags to check the key pressed.

double rotSphere = 0.0;
double rotCube = 0.0;
double rotTea = 0.0;

bool WireFrame= false;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


/* GLUT callback Handlers */

static void resize(int width, int height)
{
     double Ratio;

   if(width<=height)
     {
         glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
      }
    else
      {
        glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);
      }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective (50.0f,1,0.1f, 100.0f);
 }

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLdouble size = 0.5;

    gluLookAt(0,5,10,0.0,0.0,0.0,0.0,1.0,0.0);

    if(WireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPushMatrix();           //Cube.
        glColor3f(0,1,0);
        glTranslatef(xcube,ycube,zcube);
        glRotatef(rotCube,0,1,0);                       //functions for translate , rotate and scale for all the three figures.
        glScalef(scaleCube,scaleCube,scaleCube);
        glutSolidCube(2.0);

    glPopMatrix();

        glPushMatrix();       //Sphere.
        glColor3f(0,0,1);
        glTranslated(xsphere,ysphere,zsphere);
        glRotated(rotSphere,0,1,0);
        glScalef(scaleSphere,scaleSphere,scaleSphere);
        glutSolidSphere(radius,slices,stacks);

    glPopMatrix();

        glPushMatrix ();    //Teapot.
        glColor3f(1,0,0);
        glTranslated(xtea,ytea,ztea);
        glRotated(rotTea,0,1,0);
        glScalef(scaleTeapot,scaleTeapot,scaleTeapot);
        glutSolidTeapot ( 1.5 );

        //glColor3f(1,0,0);
    glPopMatrix ();

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{

    switch (key)
    {
        case 27 :

        case 'q':
            exit(0);
    break;

        case 'c' : //
        cval = true;
        sval = false;                   // boolean values declared for each figure respectively
        tval = false;

    break;

        case 's' : //
        sval = true;
        tval = false;
        cval = false;

    break;
        case 't': //
        tval = true;
        sval = false;
        cval = false;

    break;

      case 'w':
        WireFrame =!WireFrame;
        break;
    }
}

void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP: // When upkey is pressed, figure zooms.
       if(cval){
       scaleCube += 0.5;
       }else if(sval){
       scaleSphere += 0.5;
       }else if(tval){
       scaleTeapot += 0.5;
       }

    break;
    case GLUT_KEY_DOWN:  // When downkey is pressed, figure compresses.
         if(cval){
         scaleCube -= 0.5;
         }else if(sval){
         scaleSphere -= 0.5;
         }else if(tval){
         scaleTeapot -= 0.5;
         }

     break;
    case GLUT_KEY_LEFT: // When leftkey is pressed , figure increments 5 degrees.
         if(cval){
         rotCube = rotCube+5;
         }else if(sval){
         rotSphere = rotSphere+5;
         }else if(tval){
         rotTea = rotTea+5;
         }

     break;
      case GLUT_KEY_RIGHT:  // When right key is pressed , figure decrements 5 degrees.
         if(cval){
        rotCube = rotCube-5;
         }else if(sval){
        rotSphere = rotSphere-5;
         }else if(tval){
        rotTea=rotTea-5;
         }

     break;
}

  glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

static void init(void)
{

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
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);

    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
