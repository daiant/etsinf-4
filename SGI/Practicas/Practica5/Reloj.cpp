#define PROYECTO "ISGI::Reloj 3D"
#define PI 3,14159265358979323846
#include <iostream>
#include <cmath>
#include <freeglut.h>
#include <sstream>
using namespace std;

static const float radio = 5.0; // radio de giro de la cámara
static float angulo = 0.0; // Angulo de travelling inicial de la camara
static float ojo[] = { 0, 0, radio }; // posicion inicial de la camara
static const float velocidad = 24.0 * 3.1415926 / 180; // radianes/segundo
static const float frames = 60; // para cambiar la frecuencia de movimiento cambiar aquí 
static float r_segundos = 0.0, r_minutos = 0.0, r_horas = 0.0;
void onTimer(int valor)
{
	//tiempo transcurrido ultima vez
	static int antes = 0;
	int ahora, tiempo_transcurrido;

	ahora = glutGet(GLUT_ELAPSED_TIME);
	tiempo_transcurrido = ahora - antes;
	r_segundos -= 6 / frames; // cada segundo son 6 grados en sentido antihorario pero a 60fps - > 0.1 grados
	r_minutos -= 6 / frames / 60; // 60 por el minuto que ha de pasar
	r_horas -= (6 / frames / 60 / 60 ) * 12; // el reloj tiene 12 horas flipao




	antes = ahora;

	glutTimerFunc(1000 / frames, onTimer, frames);

	glutPostRedisplay();
}
void marcas() {
	float altura = 1*0.2;
	float radio = 1.7;
	float ancho = 0.1;
	glPushMatrix();
	glColor3f(202.0 / 255, 190.0 / 255, 182.0 / 255);
	for (int i = 0; i < 60; i++) 
	{
		glPushMatrix();
		//glRotatef(-i*6, 0, 0, 1);
		
		
		
		//glScalef(0.2, 0.2, 0.2);
		//glTranslatef(radio * sin(i), radio * cos(i), 0);
		glRotatef(-i * 6, 0, 0, 1);
		if (i % 5 == 0) { altura = 0.3; ancho = 0.15; }
		else { altura = 0.2; ancho = 0.1; }
		glRectf(-ancho*0.2, radio, ancho*0.2, radio - altura);
		glPopMatrix();
	}


	
	glPopMatrix();
}
void esfera()
{
	float radio;

	glBegin(GL_POLYGON);
	glColor3f(245/255.0,240/255.0,219/255.0);
	radio = 1.8;
	for (int i = 0; i < 360; i++)
	{
		glVertex3f(radio * sin(i), radio * cos(i), 0);
	};
	glEnd();
	
	
	glBegin(GL_POLYGON);
	radio = 2;
	
	glColor3f(232.0 / 255, 220.0 / 255, 202.0 / 255);
	//glColor3f(245, 245, 220);

	for (int i = 0; i < 360; i++)
	{
		glVertex3f(radio*sin(i), radio*cos(i), 0);
	};
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(0,0,0);
	//glColor3f(245, 245, 220);
	radio = 0.1;
	for (int i = 0; i < 360; i++)
	{
		glVertex3f(radio * sin(i), radio * cos(i), 0);
	};
	glEnd();
}
void segundero()
{
	glPushMatrix();
	glColor3f(1, 0, 0);
	glScalef(0.2, 0.2, 0.2);

	glRotatef(r_segundos, 0, 0, 1);
	glRectf(-0.25, 0, 0.25, 8);
	glPopMatrix();
}
void minutero()
{
	glPushMatrix();
	glColor3f(0.01, 0.01, 0.01);
	glScalef(0.2, 0.2, 0.2);
	glRotatef(r_minutos, 0, 0, 1);
	glRectf(-0.25, 0, 0.25, 7);
	glPopMatrix();
}
void horas()
{
	glPushMatrix();
	glColor3f(0.01, 0.01, 0.01);
	glScalef(0.2, 0.2, 0.2);
	glRotatef(r_horas,  0, 0, 1);
	glRectf(-0.25, 0, 0.25, 5);
	glPopMatrix();
}
void muestraFPS()
{
	int ahora, tiempo_transcurrido;
	static int antes = 0;
	static int FPS = 0;
	stringstream titulo;

	//Cuenta de llamadas a esta funcion en el ultimo segundo 
	FPS++;
	ahora = glutGet(GLUT_ELAPSED_TIME);
	tiempo_transcurrido = ahora - antes;
	if (tiempo_transcurrido > 1000) { // ha pasado un segundo
		titulo << "FPS: " << FPS;
		glutSetWindowTitle(titulo.str().c_str());
		antes = ahora;
		FPS = 0;
	}
}
void init()
{
	cout << "Version: OpenGL " << glGetString(GL_VERSION) << endl;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(ojo[0], ojo[1], ojo[2], 0, 0, 0, 0, 1, 0);
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.8, 0.8);
	float radio = 0.1;
	for (int i = 0; i < 360; i++)
	{
		glVertex3f(radio * sin(i), radio * cos(i), 0);
	};
	glEnd();
	glColor3f(0, 0, 1);

	segundero();
	minutero();
	horas();
	marcas();
	esfera();
	glPopMatrix();
	glPushMatrix();
	  glTranslatef(0, 0, -2);
	  glColor3f(1, 0, 0); // Color de dibujo a rojo
	//  glutSolidTeapot(0.5); // Dibuja una tetera detras
	glPopMatrix();
	muestraFPS();
	glutSwapBuffers(); // Intercambia buffers
}

void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float razon = (float)w / h;
	gluPerspective(60, razon, 1, 10);
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600,600);
	glutCreateWindow(PROYECTO);
	std::cout << PROYECTO << " RUNNING" << std::endl;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000 / frames, onTimer, frames);
	init();
	glutMainLoop();
}