#include <iostream>
#include <freeglut.h>
#include <cmath>
static GLint id;
static const GLfloat triangulo1[8] = { 1.0, 0.7, 1.0, 0.7, 1.0, 0.7 };
static const GLfloat triangulo2[8] = { 1.0, 0.7, 1.0, 0.7, 1.0, 0.7 };
//estrella de kauron DIOS
void init()
{
	float PI = 3.1415926;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	id = glGenLists(1);
	glNewList(id, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(0.0, 0.0, 0.8);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 4; i++) {
		float angulo = (1 + (i * 4) % 12) * PI / 6; // Versión inteligente, de kauron, abajo la mía
		glVertex3f(cos(angulo), sin(angulo), 0.0);
		glVertex3f(cos(angulo) * 0.7, sin(angulo) * 0.7, 0.0);
	}
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	float alpha = 2 * PI / 6;
	for (int i = 0; i < 4; i++) {
		float angulo = (3 + (i * 4) % 12) * PI / 6;
		glVertex3f(1.0 * cos(angulo), 1.0 * sin(angulo), 0.0);
		glVertex3f(0.7 * cos(angulo), 0.7 * sin(angulo), 0.0);
	}
	glEnd();
	glEndList();
}
void display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT); //Limpia la pantalla
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//Primera Estrella
	glPushMatrix();
	glTranslatef(-0.5, 0.5, 0); 
	glScalef(0.5, 0.5, 0.5);
	glRotatef(15, 0, 0 , 1);
	glCallList(id);
	
	glRotatef(30, 0, 0, 1);
	glScalef(0.4, 0.4, 0.4);
	glCallList(id);
	glPopMatrix();

	//Segunda 
	glPushMatrix();
	glTranslatef(0.5, 0.5, 0);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(-15, 0, 0, 1);
	glCallList(id);

	glRotatef(-30, 0, 0, 1);
	glScalef(0.4, 0.4, 0.4);
	glCallList(id);
	glPopMatrix();

	//Tercera
	glPushMatrix();
	glTranslatef(0.5, -0.5, 0);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(15, 0, 0, 1);
	glCallList(id);

	glRotatef(30, 0, 0, 1);
	glScalef(0.4, 0.4, 0.4);
	glCallList(id);
	glPopMatrix();

	//Cuarta
	glPushMatrix();
	glTranslatef(-0.5, -0.5, 0);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(-15, 0, 0, 1);
	glCallList(id);

	glRotatef(-30, 0, 0, 1);
	glScalef(0.4, 0.4, 0.4);
	glCallList(id);
	glPopMatrix();

	glFlush();
}
void reshape(GLint w, GLint h)
{
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Estrellas varias");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}