#include <iostream>
#include <gl\freeglut.h>
#define _USE_MATH_DEFINES // for C++
# define M_PI           3.14159265358979323846
#include <cmath>
#include <math.h>
#include <random>
#include<tuple>
#include <vector>
#include <ctime>
#include <time.h> 
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <sstream>
#pragma warning(disable:4996)


//Fotogramas por segundo
static const int TASAFPS = 60;
//Variable dependiente del tiempo
static float angulo = 0;

using namespace std;
static GLuint anillo, estrella;
double rsphere = 1;
GLdouble posCam[] = { 3, 3, 3};
time_t curr_time = time(NULL);
tm* tm_local = localtime(&curr_time);
int sA0 = 61;
int hA = tm_local->tm_hour;
int mA = tm_local->tm_min;
int sA = tm_local->tm_sec;
static float secondAngle = 360.0f - (sA * 6);
static float minuteAngle = 360.0f - (mA * 6); // -(sA * 6) / 60;
static float hourAngle = 360.0f - ((hA % 12) * 30); // -(mA * 30) / 60 - (sA * 30) / 3600;
void init()
{
	//
	glClearColor(1.0, 1.0, 1.0, 1.0);
	anillo = glGenLists(1);
	glNewList(anillo, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);


	float x = 200;
	float y = 0;
	float pi = M_PI;
	float elementos[180][2];
	float elementos2[180][2];
	float elementos3[180][2];


	for (int i = 0; i <= 179; i = i + 2) {
		//Es m_pi / 6 para los 6 lados
		x = cos(i * pi / 90 + pi / 180);
		y = sin(i * pi / 90 + pi / 180);
		elementos[i][0] = x * 0.99;
		elementos[i][1] = y * 0.99;
		elementos2[i][0] = x;
		elementos2[i][1] = y;
		elementos3[i][0] = x * 0.89;
		elementos3[i][1] = y * 0.89;
		x = 0.89 * cos(i * pi / 90 + pi / 180);
		y = 0.89 * sin(i * pi / 90 + pi / 180);
		elementos[i + 1][0] = x;
		elementos[i + 1][1] = y;
		elementos2[i+1][0] = 0.99 * cos(i * pi / 90 + pi / 180);;
		elementos2[i+1][1] = 0.99 * sin(i * pi / 90 + pi / 180);;
		elementos3[i + 1][0] = 0.88 * cos(i * pi / 90 + pi / 180);;
		elementos3[i + 1][1] = 0.88 * sin(i * pi / 90 + pi / 180);;
	}


	glPushMatrix();
	//glColor3f(0, 0, 0.8);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 182; i++) {
		glVertex2f(elementos[i % 180][0], elementos[i % 180][1]);
	}
	glEnd();
	
	glPopMatrix();


	glPushMatrix();
	glColor3f(0, 0, 0);
	//glColor3f(0, 0, 0.8);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 182; i++) {
		glVertex2f(elementos2[i % 180][0], elementos2[i % 180][1]);
	}
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glColor3f(0, 0, 0);
	//glColor3f(0, 0, 0.8);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 182; i++) {
		glVertex2f(elementos3[i % 180][0], elementos3[i % 180][1]);
	}
	glEnd();
	glPopMatrix();
	glPopAttrib();
	glEndList();

	estrella = glGenLists(1);
	glNewList(estrella, GL_COMPILE);
	glPushAttrib(GL_CURRENT_BIT);
	x = 200;
	y = 0;
	pi = M_PI;
	float elementos4[6][2];

	for (int i = 0; i <= 5; i = i + 2) {
		//Es m_pi / 6 para los 6 lados
		x = cos(i * pi / 3 + pi / 6);
		y = sin(i * pi / 3 + pi / 6);
		elementos4[i][0] = x;
		elementos4[i][1] = y;
		x = 0.7 * cos(i * pi / 3 + pi / 6);
		y = 0.7 * sin(i * pi / 3 + pi / 6);
		elementos4[i + 1][0] = x;
		elementos4[i + 1][1] = y;
	}

	glPushMatrix();
	//glColor3f(0, 0, 0.8);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 8; i++) {
		glVertex2f(elementos4[i % 6][0], elementos4[i % 6][1]);
	}
	glEnd();
	glPopMatrix();

	for (int i = 0; i <= 5; i = i + 2) {
		//Es m_pi / 6 para los 6 lados
		x = cos(i * pi / 3 + pi / 2);
		y = sin(i * pi / 3 + pi / 2);
		elementos4[i][0] = x;
		elementos4[i][1] = y;
		x = 0.7 * cos(i * pi / 3 + pi / 2);
		y = 0.7 * sin(i * pi / 3 + pi / 2);
		elementos4[i + 1][0] = x;
		elementos4[i + 1][1] = y;
	}

	glPushMatrix();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 8; i++) {
		glVertex2f(elementos4[i % 6][0], elementos4[i % 6][1]);
	}
	glEnd();
	glPopMatrix();
	glPopAttrib();

	glEndList();
}


void FPS()
{
	//Contar fotogramas por segundo y escribirlos como titulo de la ventana
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	int ahora = glutGet(GLUT_ELAPSED_TIME);
	static int fotogramas = 0;

	//Cada vez que se llama a FPS se incrementan los fotogramas 
	fotogramas++;

	//Si ha transcurrido mas de un segundo, se escriben los fotogramas y se inicializan a 0
	int ttrans = (ahora - antes);
	if (ttrans >= 1000) {
		stringstream titulo;
		//titulo << "FPS= " << fotogramas;
		//glutSetWindowTitle(titulo.str().c_str());
		fotogramas = 0;
		antes = ahora;
	}
}


void display() {

	//

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//5, 3, 0
	//4.2, 3, 0
	//Posicionar y orientar la camara
	gluLookAt(/*Posicion de la camara */ 4.2, 3, 0,
		/*Punto de interes*/ 0, 0, 0,
		/*Vertical de la camara*/ 0, 1, 0);

	glPushMatrix();
	glColor3f(1, 0.8431, 0);
	glScalef(0.6, 0.6, 0.6);
	glRotatef(-90, 0, 1, 0);
	glRotatef(hourAngle, 0, 1, 0);
	glCallList(anillo);
	glColor3f(0.7098, 0.65098, 0.2588);
	glScalef(0.4, 0.4, 0.65/0.6);
	glutWireCone(0.1, 1, 18, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0.8431, 0);
	glScalef(0.75, 0.75, 0.75);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glRotatef(180, 0, 0, 1);
	glRotatef(minuteAngle, 0, 1, 0);
	glCallList(anillo);
	glColor3f(0.7098, 0.65098, 0.2588);
	glScalef(0.3, 0.3, 0.82 / 0.75);
	glutWireCone(0.1, 1, 18, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0.8431, 0);
	glScalef(0.975, 0.975, 0.975);
	glRotatef(-90, 0, 1, 0);
	glRotatef(secondAngle, 0, 1, 0);
	glCallList(anillo);
	glColor3f(0.7098, 0.65098, 0.2588);
	glScalef(0.15, 0.15, 1 / 0.975);
	glutWireCone(0.1, 1, 18, 1);
	glPopMatrix();

	glPushMatrix();
	//Segundero
	glColor3f(0.06, 0.32, 0.73);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	for (auto i = 0; i < 60; i++) {
		glPushMatrix();

		glRotatef(6 * i, 0, 0, 1);
		glRotatef(-angulo / 7, 0, 1, 0);
		glTranslatef(0.0, 1, 0.0);
		glScalef(0.04, 0.04, 0.04);
		if (i % 15 != 0) {
			glPushMatrix();
			glScalef(0.4, 0.4, 0.4);
			for (int i = 1; i <= 3; i++) {
				glPushMatrix();
				glRotatef(90, 1, 0, 0);
				glRotatef(-angulo / 7, 0, 1, 0);
				glRotatef(i * 60, 0, 1, 0);
				glCallList(estrella);
				glPopMatrix();
			}
			glPopMatrix();
		}
		else {
			glPushMatrix();
			for (int i = 1; i <= 3; i++) {
				glPushMatrix();
				glRotatef(90, 1, 0, 0);
				glRotatef(-angulo / 7, 0, 1, 0);
				glRotatef(i * 60, 0, 1, 0);
				glCallList(estrella);
				glPopMatrix();
			}
			glPopMatrix();
		}

		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	//Minutero
	glColor3f(0.60784, 0.06666, 0.117647);
	glRotatef(90, 0, 1, 0);
	for (auto i = 0; i < 60; i++) {
		glPushMatrix();

		glRotatef(6 * i, 0, 0, 1);
		glRotatef(-angulo / 7, 0, 1, 0);
		glTranslatef(0.0, 0.82, 0.0);
		glScalef(0.04, 0.04, 0.04);
		if (i % 5 != 0) {
			glPushMatrix();
			glScalef(0.4, 0.4, 0.4);
			for (int i = 1; i <= 3; i++) {
				glPushMatrix();
				glRotatef(90, 1, 0, 0);
				glRotatef(-angulo / 7, 0, 1, 0);
				glRotatef(i * 60, 0, 1, 0);
				glCallList(estrella);
				glPopMatrix();
			}
			glPopMatrix();
		}
		else {
			glPushMatrix();
			for (int i = 1; i <= 3; i++) {
				glPushMatrix();
				glRotatef(90, 1, 0, 0);
				glRotatef(-angulo / 7, 0, 1, 0);
				glRotatef(i * 60, 0, 1, 0);
				glCallList(estrella);
				glPopMatrix();
			}
			glPopMatrix();
		}

		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	//Horario
	glColor3f(0.03137, 0.396078, 0.133333);
	glRotatef(90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	for (auto i = 0; i < 12; i++) {
		glPushMatrix();

		glRotatef(30 * i, 0, 0, 1);
		glRotatef(-angulo / 7, 0, 1, 0);
		glTranslatef(0.0, 0.65, 0.0);
		glScalef(0.04, 0.04, 0.04);
		if (i % 3 != 0) {
			glPushMatrix();
			glScalef(0.4, 0.4, 0.4);
			for (int i = 1; i <= 3; i++) {
				glPushMatrix();
				glRotatef(90, 1, 0, 0);
				glRotatef(-angulo / 7, 0, 1, 0);
				glRotatef(i * 60, 0, 1, 0);
				glCallList(estrella);
				glPopMatrix();
			}
			glPopMatrix();
		}
		else {
			glPushMatrix();
			for (int i = 1; i <= 3; i++) {
				glPushMatrix();
				glRotatef(90, 1, 0, 0);
				glRotatef(-angulo / 7, 0, 1, 0);
				glRotatef(i * 60, 0, 1, 0);
				glCallList(estrella);
				glPopMatrix();
			}
			glPopMatrix();
		}

		glPopMatrix();
	}
	glPopMatrix();

	//Comprobación escalado de la cámara
	//glColor3f(0.2, 0.85, 1);
	//glutWireSphere(rsphere, 15, 15);
	
	glutSwapBuffers();

	FPS();

}

void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);

	float ar = (float)w / (float)h;

	// Crear la camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double d = sqrt(posCam[0] * posCam[0] + posCam[1] * posCam[1] + posCam[2] * posCam[2]);
	double fovy = asin(rsphere / d);
	fovy = (fovy * 180) / M_PI;
	gluPerspective(fovy * 2, ar, 1, 10);
}

void onIdle()
{
	/*
	//Animacion sin control de tiempo
	angulo += 0.1;
	glutPostRedisplay();
	*/
	time_t curr_time = time(NULL);
	tm* tm_local = localtime(&curr_time);
	int mA2 = tm_local->tm_min;
	int sA2 = tm_local->tm_sec;
	//Control del tiempo en la animacion
	static const float vueltasXsegundo = 1;
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	int ahora = glutGet(GLUT_ELAPSED_TIME);

	float ttrans = (ahora - antes) / 1000.0f;
	if (sA0 != sA2) {
		angulo += 60;
		sA0 = sA2;
	}
	//angulo += vueltasXsegundo * 360 * ttrans;
	if (mA2 == 0 && sA2 == 0) {
		hourAngle += -30.0 * ttrans; // / 3600.0 * ttrans;
	}
	if (sA2 == 0) {
		minuteAngle += -6 * ttrans; // / 60.0 * ttrans;
	}
	secondAngle += -6 * ttrans;

	antes = ahora;

	glutPostRedisplay();
}

void onTimer(int tiempo)
{
	
	glutTimerFunc(tiempo, onTimer, tiempo);

	onIdle();

}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Reloj 3D");
	std::cout << "Reloj 3D" << std::endl;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	glutTimerFunc(1000 / TASAFPS, onTimer, 1000 / TASAFPS);
	
	glutMainLoop();

}