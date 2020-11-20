#define PROYECTO "ISGI::S5E02::Control del tiempo"

#include <iostream>
#include <cmath>
#include <freeglut.h>
#include <sstream>
using namespace std;

static const float radio = 5.0; // radio de giro de la cámara
static float angulo = 0.0; // Angulo de travelling inicial de la camara
static float ojo[] = { 0, 0, radio }; // posicion inicial de la camara
static const float velocidad = 24.0 * 3.1415926 / 180; // radianes/segundo
static const int frames = 40;
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
	if (tiempo_transcurrido > 1000){ // ha pasado un segundo
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

	glColor3f(0, 0, 1);
	glutSolidTeapot(1.0);
	glPushMatrix();
	glTranslatef(0, 0, -2);
	glColor3f(1, 0, 0); // Color de dibujo a rojo
	glutSolidTeapot(0.5); // Dibuja una tetera detras
	glPopMatrix();
	muestraFPS();
	glutSwapBuffers(); // Intercambia buffers
}

void reshape(GLint w, GLint h)
{
	glViewport(0, 0,w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float razon = (float)w / h;
	gluPerspective(60, razon, 1, 10);
}

void onTimer(int valor) 
{
	//tiempo transcurrido ultima vez
	static int antes = 0;
	int ahora, tiempo_transcurrido; 
	
	ahora = glutGet(GLUT_ELAPSED_TIME);
	tiempo_transcurrido = ahora - antes;
	// angulo = angulo anterior + velocidad * tiempo
	angulo += velocidad * (float)tiempo_transcurrido / 1000.0;
	ojo[0] = radio * sin(angulo);
	ojo[1] = radio * cos(angulo);
	
	antes = ahora; 

	glutTimerFunc(1000 / frames, onTimer, frames);

	glutPostRedisplay();
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutCreateWindow(PROYECTO);
	std::cout << PROYECTO << " RUNNING" << std::endl;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000 / frames, onTimer, frames);
	init();
	glutMainLoop();
}