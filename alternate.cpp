#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include "sgl.h"
using namespace std;

// Function Declarations
void drawScene();
void update(int value);
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);

// Global Variables
float box_len = 4.0f;
float tri_x = 0.0f;
float tri_y = 0.0f;
float theta = 0.0f; 


int main(int argc, char **argv) {

    // Initialize GLUT
    glutInit(&argc, argv);
    init();
    initRendering();

    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    glutMouseFunc(handleMouseclick);
    glutReshapeFunc(handleResize);
    glutTimerFunc(10, update, 0);

    glutMainLoop();
    return 0;
}


//void drawLine(floa)
void drawLine(float x1, float y1, float z1, float x2, float y2, float z2);


// Function to draw   objects on the screen
void drawScene() {

	sglClear(0.0, 0.0, 0.0);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);

	sglModLoadIdentity();
	sglViewLoadIdentity();
//	sglLookAt(10, 10, -20, 0, 0, 0,0,0,1);
	sglModTranslate(0, 0, -10.0f);
	
	sglModPushMatrix();	
	sglModTranslate(tri_x, tri_y, 0.0f);
	sglModRotate(theta, 0.0f, 0.0f, 1.0f);
//	sglModScale(2.0f, 2.0f, 2.0f);	
	

	sglBegin(SGL_TRIANGLES);
	sglColor(0.0, 0.0f, 1.0f);
	sglVertex(0.0f, 1.0f, 0.0f);
	sglColor(0.0f, 1.0f, 0.0f);
	sglVertex(-1.0f, -1.0f, 0.0f);
	sglColor(1.0f, 0.0f, 0.0f);
	sglVertex(1.0f, -1.0f, 0.0f);
	sglEnd();

	sglModPopMatrix();
	
	sglModPushMatrix();	
	sglModTranslate(-1.0f, -1.0f, -4.0f);
	sglBegin(SGL_TRIANGLES);
	sglColor(0.0, 0.0f, 1.0f);
	sglVertex(0.0f, 1.0f, 0.0f);
	sglColor(0.0f, 1.0f, 0.0f);
	sglVertex(-1.0f, -1.0f, 0.0f);
	sglColor(1.0f, 0.0f, 0.0f);
	sglVertex(1.0f, -1.0f, 0.0f);
	sglEnd();
	sglModPopMatrix();
	
	sglModPushMatrix();	

	sglModTranslate(-6.0f, -6.0f, -4.0f);
	sglBegin(SGL_TRIANGLES);
	sglColor(0.0, 0.0f, 1.0f);
	sglVertex(0.0f, 1.0f, 0.0f);
	sglColor(0.0f, 1.0f, 0.0f);
	sglVertex(-1.0f, -1.0f, 0.0f);
	sglColor(1.0f, 0.0f, 0.0f);
	sglVertex(1.0f, -1.0f, 0.0f);
	sglEnd();
	sglModPopMatrix();
	
	sglModPushMatrix();	
	
	sglModTranslate(-10.0f, -10.0f, -4.0f);
	sglColor(0.0f, 1.0f, 1.0f);
	sglBegin(SGL_TRIANGLES);
	sglModScale(2.0,2.0,2.0);
	sglVertex(1.0f, 1.0f, 0.0f);
	sglVertex(-1.0f, -1.0f, 0.0f);
	sglVertex(1.0f, -1.0f, 0.0f);
	sglVertex(1.0f, 1.0f, 0.0f);
	sglVertex(-1.0f, -1.0f, 0.0f);
	sglVertex(-1.0f, 1.0f, 0.0f);
	sglEnd();
	sglModPopMatrix();
	
	sglModPushMatrix();	
	
	sglModTranslate(10.0f, 10.0f, -4.0f);
	sglColor(1.0f, 1.0f, 0.0f);
	sglBegin(SGL_TRIANGLES);
	sglModScale(2.0,2.0,2.0);
	sglVertex(1.0f, 1.0f, 0.0f);
	sglVertex(-1.0f, -1.0f, 0.0f);
	sglVertex(1.0f, -1.0f, 0.0f);
	sglVertex(1.0f, 1.0f, 0.0f);
	sglVertex(-1.0f, -1.0f, 0.0f);
	sglVertex(-1.0f, 1.0f, 0.0f);
	sglEnd();
	sglModPopMatrix();
	
	sglShow();
	
//	glPopMatrix();
//	glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds


void drawLine(float x1, float y1, float z1, float x2, float y2, float z2){
	
	glBegin(GL_LINES);
	sglVertex(x1,y1,z1);
	sglVertex(x2,y2,z2);
	glEnd();
}

void update(int value) {

	glutTimerFunc(10, update, 0);
}

// Initializing some openGL 3D rendering options
void initRendering() {

	sglProjFrustum(-1,1, -1, 1, 1, 100);
//	makeFrustum(45.0f,900 /500 , 0.1f, 200.0f);
	sglViewport(0, 0, 400, 400);
}

// Function called when the window is resized
void handleResize(int w, int h) {

//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();

//	cout<<"Resized"<<endl;
//	makeFrustum(45.0f, (float)w / (float)h, 0.1f, 200.0f);
//	float proj[16];
//
//	glGetFloatv(GL_PROJECTION_MATRIX, proj);
///	printf("sljkdhudgfgf\n");
//	int i;
//	for(i=0;i<16;i++)
//	{
//		printf("%f ", proj[i]);
//		if(i%4==3) printf("\n");
///	}
//	printf("\n");
//	projectionMat.print();
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

	if (key == 27) {
		exit(0);     // escape key is pressed
	}
}

void handleKeypress2(int key, int x, int y) {

    if (key == GLUT_KEY_LEFT)
        tri_x -= 0.1;
    if (key == GLUT_KEY_RIGHT)
        tri_x += 0.1;
    if (key == GLUT_KEY_UP)
        tri_y += 0.1;
    if (key == GLUT_KEY_DOWN)
        tri_y -= 0.1;


}

void handleMouseclick(int button, int state, int x, int y) {

    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
            theta += 15;
        else if (button == GLUT_RIGHT_BUTTON)
            theta -= 15;
    }
}
