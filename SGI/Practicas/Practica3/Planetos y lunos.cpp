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
void display()
{
	/*glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(id);
	glFlush();
*/
	glClear(GL_COLOR_BUFFER_BIT); //Limpia la pantalla
	glMatrixMode(GL_MODELVIEW); // Selecciona la modelview
	glLoadIdentity(); // Carga la matriz identidad

	glScalef(0.2, 0.2, 0.2); //Escalado general

	//Sol
	glutSolidSphere(1.0, 10, 10); // 1 de radio
	
	glPushMatrix(); // Guarda el estado de la transformación

	// primer planeta en coordenadas del sol
	glRotatef(45.0, 0.0, 0.0, 1); // Primero lo rotas
	glTranslatef(3.0, 0, 0.0); // Luego lo trasladas con el sistema de referencia rotado
	glutWireSphere(0.5, 10, 10);
	
	// primera luna en coordenadas del planeta
	glPushMatrix(); // Guarda el estado de la transformación
	glRotatef(100, 0.0, 0.0, 1);
	glTranslatef(1.0, 0, 0);
	glutWireSphere(0.1, 5, 5);
	glPopMatrix(); // Restaura el estado de la transformación para que coja la referencia del planeta

	//segunda luna, coordenadas del planeta
	glPushMatrix(); //guarda el estado de transformación
	glRotatef(20, 0.0, 0, 1);
	glTranslatef(1.0, 0.0, 0.0);
	glutSolidSphere(0.2, 5, 5);
	glPopMatrix(); // Restauramos al planetoide


	glPopMatrix(); //Restauramos al sol
	// Aquí se dibujan más lunas


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
	glutCreateWindow("David Star");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//init();
	glutMainLoop();
}