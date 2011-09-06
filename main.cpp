#include <QtGui/QApplication>
#include "mainwindow.h"
#include <iostream>
#include <stdlib.h> //Needed for "exit" function

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
                                        int x, int y) {    //The current mouse coordinates
        switch (key) {
                case 27: //Escape key
                        exit(0); //Exit the program
        }
}

//Initializes 3D rendering
void initRendering() {
        //Makes 3D drawing work when something is in front of something else
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glEnable(GL_COLOR_MATERIAL);
        glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
}

//Called when the window is resized
void handleResize(int w, int h) {
        //Tell OpenGL how to convert from coordinates to pixel values
        glViewport(0, 0, w, h);

        glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective

        //Set the camera perspective
        glLoadIdentity(); //Reset the camera
        gluPerspective(45.0,                  //The camera angle
                                   (double)w / (double)h, //The width-to-height ratio
                                   1.0,                   //The near z clipping coordinate
                                   200.0);                //The far z clipping coordinate
}
float _angle = 30.0f;
float _cameraAngle = 0.0f;

void drawFractal(int num)
{
 switch(num) {
   case 0:
     glRotatef (_angle, 1,2,0);
                glBegin( GL_TRIANGLES );
                glVertex3f( 1.0, 0.0, 0.0 );
                glVertex3f( 0.0, 1.0, 0.0 );
                glVertex3f( 0.0, 0.0, 0.0 );
                glEnd();
        break;
   default:
        glPushMatrix();
        glPushMatrix();
        glScalef(0.5,0.5,1.0);
        drawFractal(num - 1);
        glPopMatrix();
        glTranslatef(0.5,0.0,0.0);
        glScalef(0.5,0.5,1.0);
        drawFractal(num - 1);
        glPopMatrix();
        glTranslatef(0.0,0.5,0.0);
        glScalef(0.5,0.5,0.5);
        drawFractal(num - 1);
        break;
 }
}
//Draws the 3D scene
void drawScene() {
        //Clear information from last draw
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
        glLoadIdentity(); //Reset the drawing perspective
        glRotatef (_cameraAngle,0,1,0);
        glTranslatef (0.0f, 0.0f, -5.0f);//Move forward 5units

        //Add ambient light
        GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color(0.2, 0.2, 0.2)
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

        //Add positioned light
        GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
        GLfloat lightPos0[] = {4.0f, 0.0f, 1.25f, 1.0f}; //Positioned at (4, 0, 8)
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

        glPushMatrix ();//Save transformations
        glTranslatef (0.0f, -1.0f, 0);
        glRotatef (_angle,1,0,0);
        glBegin(GL_QUADS); //Begin quadrilateral coordinates

        //Trapezoid
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.7f, -0.5f, 0.0f);
        glVertex3f(0.7f, -0.5f, 0.0f);
        glColor3f(1.0f, 0.75f, 0.0f);
        glVertex3f(0.4f, 0.5f, 0.0f);
        glVertex3f(-0.4f, 0.5f, 0.0f);

        glVertex3f(0.4f, 0.5f, 0.0f);
        glVertex3f(-0.4f, 0.5f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.7f, -0.5f, 0.5f);
        glVertex3f(0.7f, -0.5f, 0.5f);

        glEnd(); //End quadrilateral coordinates

        glPopMatrix(); //Undo the move to the center of the trapezoid
        glPushMatrix(); //Save the current state of transformations
        glTranslatef(1.0f, 1.0f, 0.0f); //Move to the center of the pentagon
        glRotatef (_angle, 0,1,0);
        glScalef (0.7,0.7,0.7);

        glBegin(GL_TRIANGLES); //Begin triangle coordinates

        //Pentagon frontside
        glNormal3f(0.0f, 0.0f, -0.5f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glVertex3f(0.5f, -0.5f, 0.0f);
        glVertex3f(-0.5f, 0.0f, 0.0f);

        glNormal3f(0.0f, 0.0f, -0.5f);
        glVertex3f(-0.5f, 0.0f, 0.0f);
        glVertex3f(0.5f, -0.5f, 0.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);

        glNormal3f(0.0f, 0.0f, -0.5f);
        glVertex3f(-0.5f, 0.0f, 0.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);

        //Pentagon backside
        glNormal3f(0.0f, 0.0f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, 0.0f, 0.5f);

        glNormal3f(0.0f, 0.0f, 0.5f);
        glVertex3f(-0.5f, 0.0f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, 0.0f, 0.5f);

        glNormal3f(0.0f, 0.0f, 0.5f);
        glVertex3f(-0.5f, 0.0f, 0.5f);
        glVertex3f(0.5f, 0.0f, 0.5f);
        glVertex3f(0.0f, 0.5f, 0.5f);

        glEnd();
        glBegin(GL_QUADS); //Begin quadrilateral coordinates
        //Pentagon rightside
        glNormal3f(0.5f, 0.0f, 0.0f);
        glVertex3f(0.5f, 0.0f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);

        //Pentagon leftside
        glNormal3f(-0.5f, 0.0f, 0.0f);
        glVertex3f(-0.5f, 0.0f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glVertex3f(-0.5f, 0.0f, 0.0f);

        glEnd();


        glPopMatrix(); //Undo the move to the center of the pentagon
        glPushMatrix(); //Save the current state of transformations
        glTranslatef(-1.0f, 1.0f, 0.0f); //Move to the center of the triangle
        glRotatef (_angle,1,0,0);

        glBegin (GL_TRIANGLES);

        //Triangle
        glVertex3f(0.5f, -0.5f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.0f);

        glEnd(); //End triangle coordinates
        glPopMatrix ();

        int num = 5;
        drawFractal(num);

        glutSwapBuffers(); //Send the 3D scene to the screen
}
void update(int value) {
    _angle += 2.0f;
    if (_angle > 360) {
        _angle -= 360;
    }

    glutPostRedisplay(); //Tell GLUT that the scene has changed

    //Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(25, update, 0);
}
int main(int argc, char** argv) {
    //Create QApplication window
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400); //Set the window size

    //Create the window
    glutCreateWindow("Basic Shapes - videotutorialsrock.com");
    initRendering(); //Initialize rendering

    //Set handler functions for drawing, keypresses, and window resizes
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0); //Add a timer
    glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
    return 0; //This line is never reached
    return a.exec();
}
