#include<iostream>
#include"sgl.h"
#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>

void draw_cube();
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
float t_x, t_y, t_z;
float angle = 0.0;
int main(int argc , char *argv[])
{
	t_x = 0;
	t_y = 40;
	t_z = 0;
	glutInit( &argc, argv );
	init();
	sglProjOrtho(-100,100, -100, 100, 1, 100);
	sglViewport(0, 0, 400, 400);
	sglStack.push(viewMatrix);
	glutDisplayFunc(draw_cube);
	glutIdleFunc(draw_cube);
	glutKeyboardFunc(handleKeypress1);

	glutSpecialFunc(handleKeypress2);
	glutMainLoop();

}
void drawTriangle() {

    	sglModTranslate(t_x, t_y, t_z);
    sglBegin(GL_TRIANGLES);
    sglColor(0.0f, 0.0f, 1.0f);
    sglVertex(0.0f, 10.0f, 0.0f);
    sglColor(0.0f, 1.0f, 0.0f);
    sglVertex(-10.0f, -10.0f, 0.0f);
    sglColor(1.0f, 0.0f, 0.0f);
    sglVertex(10.0f, -10.0f, 0.0f);
    sglEnd();
}


void draw_cube()
{
	sglClear(0.0, 0.0, 1.0);
	sglModLoadIdentity();
	sglViewLoadIdentity();
	sglLookAt(20, 10, 20, 0, 0, 0,0,0,1);
	sglModTranslate(0.0f, 0.0f, -10.0f);
	sglModRotate(angle, 1.0 ,1.0,1.0);

	drawTriangle();

	sglShow();
	angle += 0.075;

}
void handleKeypress2(int key, int x, int y) {

	if (key == GLUT_KEY_LEFT)
		t_y -= 10.0;
	if (key == GLUT_KEY_RIGHT)
		t_y += 10.0;
	if (key == GLUT_KEY_UP)
		t_x -= 10.0;
	if (key == GLUT_KEY_DOWN)
		t_x += 10.0;
}
void handleKeypress1(unsigned char key, int x, int y) {

	if (key == 27) {
		exit(0);     // escape key is pressed
	}
}

