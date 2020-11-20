/***********************************************
ISGI::Hola Mundo
Carlos Sendra Gisbert 2020
Esqueleto basico de un programa en OpenGL
Dependencias :
+GLUT
* **************************************************/
#define TITULO "Primer programa en OpenGL"
#include <iostream> //Biblioteca de entrada / salida 
#include <freeglut.h> // Biblioteca Gráfica
void display()
// Funcion de atencion al dibujo
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	glClearColor(0.0, 0.0, 0.3, 1.0);
}
void reshape(GLint w, GLint h)
// Funcion de atencion al redimensionamiento
{
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 400);
	
	glutInitWindowPosition(50,600);
	glutCreateWindow(TITULO);
	std::cout << TITULO << " running" << std::endl; // Mensaje por consola
	glutDisplayFunc(display); // Alta de la funcion de atencion a display

	glutReshapeFunc(reshape); // Alta de la funcion de atencion a reshape
	glutMainLoop(); // Puesta en marcha del programa
}