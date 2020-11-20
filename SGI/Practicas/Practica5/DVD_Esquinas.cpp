#define PROYECTO "Estrella 3D"
#include <iostream> // Biblioteca de entrada salida
#include <cmath> // Biblioteca matem�tica de C
#include <freeglut.h> // Biblioteca grafica
static float posicionx(0.0), posiciony(0.0);
static GLuint cuadrado;
static const GLfloat semilado(0.1);
static GLfloat semiancho, semialto;

void onIdle() 
{
	//Vector velocidad del cuadrado en unidades/frame en ambas direcciones
	static float upperframe[] = { 0.0001, 0.0001 };

	// posicion = posicion anterior + velocidad * (1 frame)
	posicionx += upperframe[0]; 
	posiciony += upperframe[1];

	//La ventana mide alto * ancho
	//Detección de colisiones
	if (posicionx + semilado >= semiancho || posicionx - semilado <= -semiancho) upperframe[0] *= -1;
	if (posiciony + semilado >= semialto || posiciony - semilado <= -semialto) upperframe[1] *= -1;

	// Puede que al variar el marco, la posición actual quede fuera de la ventana
	// y el cuadro puede desaparecer
	// Hacemos un hardwire y lo reseteamos al centro
	if (abs(posicionx) > semiancho || abs(posiciony) > semialto) {
		posicionx = 0.0;
		posiciony = 0.0;
	};
	glutPostRedisplay();
}
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0, 0, 0);

	cuadrado = glGenLists(1);
	glNewList(cuadrado, GL_COMPILE);
	glBegin(GL_POLYGON);
		glVertex3f(-semilado, -semilado, 0.0);
		glVertex3f(semilado, -semilado, 0.0);
		glVertex3f(semilado, semilado, 0.0);
		glVertex3f(-semilado, semilado, 0.0);
	glEnd();
	glEndList();
}
void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	
	glTranslatef(posicionx, posiciony, 0);
	glCallList(cuadrado);

	//glFlush();
	glutSwapBuffers();
}
void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
	static const GLfloat ANCHO(2.0), ALTO(2.0);

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float razon = (float)w / h;
	if (w < h) {
		semiancho = ANCHO / 2;
		semialto = ALTO / 2 / razon;
	}
	else {
		semiancho = ANCHO * razon / 2;
		semialto = ALTO / 2; 
	}
	glOrtho(-semiancho, semiancho, -semialto, semialto, 0, 10);
}
void main(int argc, char** argv)
// Programa principal
{
	glutInit(&argc, argv); // Inicializacion de GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Alta de buffers a usar
	glutInitWindowSize(400, 400); // Tamanyo inicial de la ventana
	glutCreateWindow(PROYECTO); // Creacion de la ventana con su titulo
	//scout << PROYECTO << " running" << endl; // Mensaje por consola
	glutDisplayFunc(display); // Alta de la funcion de atencion a display
	glutReshapeFunc(reshape); // Alta de la funcion de atencion a reshape
	glutIdleFunc(onIdle); // Alta de la funcion de atencion a idle
	init(); // Inicializacion propia
	glutMainLoop();
}