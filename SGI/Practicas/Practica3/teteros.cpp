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
	glColor3f(0.0, 0.0, 0.3);
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
	glPopAttrib();
	glEndList();
}

void tetera() 
{
	glPushMatrix(); // Guardamos el estado 
	glutWireTeapot(1.0);

	//Creamos las bolinchas 
	glPushMatrix(); 
	glTranslatef(1.7, 1, 0);
	glScalef(0.1, 0.1, 0.1);
	glutWireSphere(1, 10, 10);
	glPopMatrix(); // estado de la tetera 
	//Bolincha menuda
	glPushMatrix();
	glTranslatef(1.9, 1.4, 0); 
	glScalef(0.06, 0.06, 0.06); 
	glutWireSphere(1, 10, 10);
	glPopMatrix();// estado a tetera

	glPopMatrix(); //Estado superior a tetera
}
void tetera_y_bandeja() {

	glPushMatrix(); 

	//Bandeja
	glPushMatrix(); 
	glTranslatef(0, -0.1, 0); // Lo bajamos un poco
	glScalef(3, 0.2, 2.4); // para aplanarlo
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.8, 0);
	tetera();
	glPopMatrix();

	glPopMatrix();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(255, 255, 255, 0);
	glRotatef(30, 1, 0, 0); // General
	
	// El de la derecha
	glPushMatrix(); 
	glTranslatef(0.4, 0.5, 0);
	glRotatef(180, 0, 1, 0);
	glScalef(0.15, 0.15, 0.15); 
	glColor3f(1, 0, 0);
	tetera_y_bandeja();
	glPopMatrix();

	glPushMatrix(); 
	glTranslatef(-0.5, -0.2, 0);
	glScalef(0.2, 0.2, 0.2);
	tetera_y_bandeja();
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
	glutInitWindowSize(500, 500);
	glutCreateWindow("David Star");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//init();
	glutMainLoop();
}