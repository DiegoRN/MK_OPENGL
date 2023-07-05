/*
PROYECTO PRÁCTICA 9
Videojuego de simulación de conducción
Diego Ramos Nebot
*/

#include <iostream>
#include <gl\freeglut.h>
#include <Utilidades.h>
#include <sstream>
#include <cmath>
#include <math.h>
#include <mmsystem.h>
#include <chrono>
#include <ctime>
#include <thread>
#define _USE_MATH_DEFINES // for C++

using namespace std;

//! Atencion al menu de popup

static const int TASAFPS = 60;
static enum { RECTO, IZQUIERDA, DERECHA} girando;
bool alambrico = false;
bool nieblaON = false;
bool hudON = true;
bool nightON = false;
int personaje = 0;
static float angulo = 0;
static float alpha = 90;
bool turno = true;
bool mostrarLakitu = true;
bool hiloLanzado = false;
bool dentroHilo = false;
bool primero = true;
bool item = false;
bool music = true;
bool musicPlaying = false;
bool isRed = false;
bool isGreen = false;
bool finRecorrido = false;
bool reset = false;
int puntuacion = 0;
int maximaPuntuacion = 0;
int setas = 0;
float ttrans = 0;
static int antes = 0;
int ahora = 0;
double lightRange = 0.3;
GLdouble posCamOriginal[] = { 0, 1, 0 };
GLdouble direccionOriginal[] = { 5, 0, 0 };
GLdouble posCam[] = { 0, 1, 0};
GLdouble direccion[] = { 5, 0, 0 };
static GLubyte objeto[1];
//Es la A de la función
int amplitud = -8;
//Es la T de la función
int periodo = 200;
double anchura = 4;
static GLfloat velocidad[3] = {0,0,0};
static GLuint carretera, logo, fondo, valla, publi1, publi2, cocheM1, cocheM2, cocheL1, cocheL2, cocheP1,
cocheP2, cocheB1, cocheB2, roster, window, cube, seta, box, audio1, audio2, brujula, goal, lakitu, pizarra;

void onMenu(int opcion) {
	if (opcion == 0) if(!mostrarLakitu) reset = true;

	glutPostRedisplay;
}

void init() {

	glClearColor(1, 1, 1, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	//Texturas
	glGenTextures(1, &carretera);
	glBindTexture(GL_TEXTURE_2D, carretera);
	loadImageFile((char *)"road.jpg");

	glGenTextures(1, &logo);
	glBindTexture(GL_TEXTURE_2D, logo);
	loadImageFile((char*)"TITULO.png");

	glGenTextures(1, &valla);
	glBindTexture(GL_TEXTURE_2D, valla);
	loadImageFile((char*)"fence.png");

	glGenTextures(1, &publi1);
	glBindTexture(GL_TEXTURE_2D, publi1);
	loadImageFile((char*)"anuncio1.jpg");

	glGenTextures(1, &publi2);
	glBindTexture(GL_TEXTURE_2D, publi2);
	loadImageFile((char*)"anuncio2.jpg");

	glGenTextures(1, &fondo);
	glBindTexture(GL_TEXTURE_2D, fondo);
	loadImageFile((char*)"espacio.jpg");

	glGenTextures(1, &cocheM1);
	glBindTexture(GL_TEXTURE_2D, cocheM1);
	loadImageFile((char*)"cocheM1.png");

	glGenTextures(1, &cocheM2);
	glBindTexture(GL_TEXTURE_2D, cocheM2);
	loadImageFile((char*)"cocheM2.png");
	
	glGenTextures(1, &cocheL1);
	glBindTexture(GL_TEXTURE_2D, cocheL1);
	loadImageFile((char*)"cocheL1.png");

	glGenTextures(1, &cocheL2);
	glBindTexture(GL_TEXTURE_2D, cocheL2);
	loadImageFile((char*)"cocheL2.png");
	
	glGenTextures(1, &cocheP1);
	glBindTexture(GL_TEXTURE_2D, cocheP1);
	loadImageFile((char*)"cocheP1.png");

	glGenTextures(1, &cocheP2);
	glBindTexture(GL_TEXTURE_2D, cocheP2);
	loadImageFile((char*)"cocheP2.png");

	glGenTextures(1, &cocheB1);
	glBindTexture(GL_TEXTURE_2D, cocheB1);
	loadImageFile((char*)"cocheB1.png");

	glGenTextures(1, &cocheB2);
	glBindTexture(GL_TEXTURE_2D, cocheB2);
	loadImageFile((char*)"cocheB2.png");

	glGenTextures(1, &roster);
	glBindTexture(GL_TEXTURE_2D, roster);
	loadImageFile((char*)"roster2.png");

	glGenTextures(1, &window);
	glBindTexture(GL_TEXTURE_2D, window);
	loadImageFile((char*)"window.png");

	glGenTextures(1, &cube);
	glBindTexture(GL_TEXTURE_2D, cube);
	loadImageFile((char*)"cube.png");

	glGenTextures(1, &seta);
	glBindTexture(GL_TEXTURE_2D, seta);
	loadImageFile((char*)"seta.png");

	glGenTextures(1, &box);
	glBindTexture(GL_TEXTURE_2D, box);
	loadImageFile((char*)"box.png");

	glGenTextures(1, &audio1);
	glBindTexture(GL_TEXTURE_2D, audio1);
	loadImageFile((char*)"audio1.png");

	glGenTextures(1, &audio2);
	glBindTexture(GL_TEXTURE_2D, audio2);
	loadImageFile((char*)"audio2.png");

	glGenTextures(1, &brujula);
	glBindTexture(GL_TEXTURE_2D, brujula);
	loadImageFile((char*)"brujula.png");

	glGenTextures(1, &goal);
	glBindTexture(GL_TEXTURE_2D, goal);
	loadImageFile((char*)"goal.jpg");

	glGenTextures(1, &lakitu);
	glBindTexture(GL_TEXTURE_2D, lakitu);
	loadImageFile((char*)"lakitu.png");

	glGenTextures(1, &pizarra);
	glBindTexture(GL_TEXTURE_2D, pizarra);
	loadImageFile((char*)"pizarra.png");

	// LIGHT 0
	glEnable(GL_LIGHT0); //puntual uniforme (luz de minero)
	GLfloat A[] = { 0.05,0.05,0.05, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, A);
	GLfloat color_difuso[3] = { 0.35,0.35,0.35 };
	GLfloat color_especular[3] = { 0.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color_difuso);
	glLightfv(GL_LIGHT0, GL_SPECULAR, color_especular);

	// LIGHT 1
	glEnable(GL_LIGHT1); //puntual uniforme (luz de minero)
	GLfloat B[] = { 0.2,0.2,0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, B);
	GLfloat color_difuso2[3] = { 1,1,1 };
	GLfloat color_especular2[3] = { 0.3,0.3,0.3 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, color_difuso2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, color_especular2);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2);

	// LIGHT 2
	glEnable(GL_LIGHT2); //puntual uniforme (luz de minero)
	GLfloat C[] = { 0,0,0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, C);
	GLfloat color_difuso3[3] = { 1,1,1 };
	GLfloat color_especular3[3] = { 1,1,1 };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, color_difuso3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, color_especular3);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1.5);

	// LIGHT 3
	glEnable(GL_LIGHT3); //puntual uniforme (luz de minero)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, C);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, color_difuso3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, color_especular);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 20);

	// LIGHT 4
	glEnable(GL_LIGHT4); //puntual uniforme (luz de minero)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, C);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, color_difuso3);
	glLightfv(GL_LIGHT4, GL_SPECULAR, color_especular);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 20);

	// LIGHT 5
	glEnable(GL_LIGHT5); //puntual uniforme (luz de minero)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, C);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, color_difuso3);
	glLightfv(GL_LIGHT5, GL_SPECULAR, color_especular);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 20);

	//Material
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,B);
	GLfloat color_difuso_material[3] = { 0.8,0.8,0.8 };
	GLfloat color_emisivo[3] = { 0,0,0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, color_emisivo);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color_difuso_material);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color_especular2);
	glMaterialf(GL_FRONT, GL_SHININESS, 3);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);

	glutCreateMenu(onMenu);
	glutAddMenuEntry("RESTART", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

float modulo(GLfloat speed) {
	return sqrt(speed * speed);
}

void reproducirMusica() { 
	//std::cout << std::this_thread::get_id << "\n";
	dentroHilo = true;
	int finCancion = glutGet(GLUT_ELAPSED_TIME);
	while (glutGet(GLUT_ELAPSED_TIME) - finCancion < 173000 && music && !reset) {
		//std::cout << glutGet(GLUT_ELAPSED_TIME) - finCancion << "\n";
	}
	//std::this_thread::sleep_for(std::chrono::seconds(173));
	if (musicPlaying) { 
		musicPlaying = false; 
		hiloLanzado = false;
	}
	dentroHilo = false;
}

void hiloAcabado() {
	dentroHilo = true;
	std::this_thread::sleep_for(std::chrono::milliseconds(750));
	lightRange -= 0.1;
	isRed = true;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	lightRange -= 0.1;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	lightRange -= 0.1;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	isRed = false;
	isGreen = true;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	mostrarLakitu = false;
	antes = glutGet(GLUT_ELAPSED_TIME);
	musicPlaying = false;
	hiloLanzado = false;
	dentroHilo = false;
}
void DibujarCubo(float x, float y, float z){
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, cube);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPushMatrix();
	glTranslatef(x + 0.25, y + 0.25, z + 0.25);
	glRotatef(angulo / 5, 0, 1, 0);
	glRotatef(angulo / 7.5, 0, 0, 1);
	glRotatef(angulo / 10, 1, 0, 0);
	glTranslatef(-(x + 0.25), -(y + 0.25), -(z + 0.25));
	GLfloat c0[3] = {x, y, z};
	GLfloat c1[3] = { x, y + 0.5, z };
	GLfloat c2[3] = { x, y + 0.5, z + 0.5 };
	GLfloat c3[3] = { x, y, z + 0.5 };
	GLfloat c4[3] = { x + 0.5, y, z };
	GLfloat c5[3] = { x + 0.5, y + 0.5, z };
	GLfloat c6[3] = { x + 0.5, y + 0.5, z + 0.5 };
	GLfloat c7[3] = { x + 0.5, y, z + 0.5 };
	quadtex(c2, c1, c5, c6, 0.0, 1.0, 0.0, 1.0, 1, 1);
	quadtex(c6, c5, c4, c7, 0.0, 1.0, 0.0, 1.0, 1, 1);
	quadtex(c7, c4, c0, c3, 0.0, 1.0, 0.0, 1.0, 1, 1);
	quadtex(c0, c4, c5, c1, 0.0, 1.0, 0.0, 1.0, 1, 1);
	quadtex(c3, c7, c6, c2, 0.0, 1.0, 0.0, 1.0, 1, 1);
	quadtex(c3, c0, c1, c2, 0.0, 1.0, 0.0, 1.0, 1, 1);
	glPopMatrix();
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glPopAttrib();
}
void DibujarPalos(float x, float y, float z) {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLfloat PLATA[4] = { 0.75, 0.75, 0.75, 1};
	if (!alambrico) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, PLATA);
		glMaterialfv(GL_FRONT, GL_SPECULAR, PLATA);
		if (!nightON)glColor3f(0.75, 0.75, 0.75);
	}
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(x, y, z);
	glutSolidCylinder(0.1, 2.5, 4, 4);
	glTranslatef(0.0, anchura / 1.05, 0);
	glutSolidCylinder(0.1, 2.5, 4, 4);
	glPopMatrix();
	glPopAttrib();

	GLfloat l0[3] = { x, 2.5, -y + 0.1};
	GLfloat l1[3] = { x, 3.5, -y + 0.1};
	GLfloat l2[3] = { x, 3.5, -y - anchura + 0.1 };
	GLfloat l3[3] = { x, 2.5, -y - anchura + 0.1 };
	

	if (posCam[0] > 926 && posCam[0] <= 1026) {
		glBindTexture(GL_TEXTURE_2D, logo);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		quadtex(l0, l1, l2, l3, 0.0, 1.0, 0.0, 1.0, 1, 1);
	}
	else {
		if (turno) {
			glBindTexture(GL_TEXTURE_2D, publi1);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, publi2);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		quadtex(l3, l0, l1, l2, 0.0, 1.0, 0.0, 1.0, 1, 1);
	}
	
}

void display()
{
	stringstream titulo;
	//<< "| Distancia recorrida: " << round(posCam[0] * 100.0)/100.0 
	
	if(!finRecorrido)ahora = glutGet(GLUT_ELAPSED_TIME); ttrans = (ahora - antes) / 1000.f;
	titulo << "Práctica 9 - Videojuego | " << "Velocidad = " << velocidad[0] << " m/s " << "| Máxima puntuación: " << maximaPuntuacion;
	glutSetWindowTitle(titulo.str().c_str());
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//light 1
	GLfloat PL2[] = { 0, 0.2, 0, 1}; // puntual justo en la camara
	glLightfv(GL_LIGHT1, GL_POSITION, PL2);
	GLfloat dir_central[] = { 0, -0.3, -0.7};
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir_central);

	//Posicionar y orientar la camara
	gluLookAt(/*Posicion de la camara */ posCam[0], 1, posCam[2],
		/*Punto de interes*/ direccion[0] + posCam[0], 1, direccion[2] + posCam[2],
		/*Vertical de la camara*/ 0, 1, 0);

	ejes();
	if (music) {
		if (!musicPlaying) {
			waveOutSetVolume(0, 286331153);
			if (mostrarLakitu) { 
				if (dentroHilo) { 
					PlaySound(TEXT("traffic.wav"), NULL, SND_ASYNC);
					musicPlaying = true;
				}
			}
			else{ 
				PlaySound(TEXT("track.wav"), NULL, SND_ASYNC);
				if (!hiloLanzado) {
					hiloLanzado = true;
					std::thread th2(reproducirMusica);
					th2.detach();
				}
				musicPlaying = true;
			}
		} 
	}
	else { PlaySound(NULL, 0, 0); musicPlaying = false; }
	if (nightON) {
		glEnable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glColorMaterial(GL_FRONT, GL_DIFFUSE);
	}
	else {
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
	}

	if (alambrico) {
		if (nightON) { 
			glClearColor(0, 0, 0, 1);
			glPushAttrib(GL_CURRENT_BIT);
			glColor3f(1, 1, 1);
		}
		else{ 
			glClearColor(1, 1, 1, 1);
			glPushAttrib(GL_CURRENT_BIT);
			glColor3f(0, 0, 0);
		}
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		glClearColor(0, 0, 0, 1);
		glEnable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}

	// Niebla
	if (nieblaON) {
		glEnable(GL_FOG);
		GLfloat CYAN[4] = { 0, 0.5, 1, 1 };
		glFogfv(GL_FOG_COLOR, CYAN);
		glFogf(GL_FOG_DENSITY, 0.02);
	}
	else { glDisable(GL_FOG); }

	GLfloat PL3[] = { 0, 10, 0, 0 }; 
	glLightfv(GL_LIGHT0, GL_POSITION, PL3);

	int quad_inicial = posCam[0]/2;
	int u = quad_inicial * 2;
	float f = amplitud * sin(u * 2 * PI / periodo);
	float der_funcion_u = (2 * PI * amplitud * cos((u * 2 * PI)/periodo))/ periodo;
	float modulo = sqrt(1 + der_funcion_u * der_funcion_u);
	GLfloat n_izquierda[3] = { - der_funcion_u / modulo, 0, 1 / modulo};
	GLfloat prueba[3] = { n_izquierda[0] * anchura / 2 , 0, n_izquierda[2] * anchura / 2 };

	GLfloat v0[3] = { 0, 0, anchura / 2 };
	GLfloat v1[3] = { 2, 0, anchura / 2 };
	GLfloat v2[3] = { 2, 0, -anchura / 2 };
	GLfloat v3[3] = { 0, 0, -anchura / 2 };
	
	//glPushAttrib(GL_CURRENT_BIT);
	if (u <= 50) {
		//Palos
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(29.0, -anchura / 2.1, 0);
		glutSolidCylinder(0.1, 2.5, 4, 4);
		glTranslatef(0.0, anchura / 1.05, 0);
		glutSolidCylinder(0.1, 2.5, 4, 4);
		glPopMatrix();
		
		glBindTexture(GL_TEXTURE_2D, logo);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		GLfloat l0[3] = { 29.0, 2.5, -anchura / 2 };
		GLfloat l1[3] = { 29.0, 3.5, -anchura / 2 };
		GLfloat l2[3] = { 29.0, 3.5, anchura / 2 };
		GLfloat l3[3] = { 29.0, 2.5, anchura / 2};

		quadtex(l3, l2, l1, l0, 0.0, 1.0, 0.0, 1.0, -1, -1);
	}

	//Dibujar fondo
	glBindTexture(GL_TEXTURE_2D, fondo);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	double alpha = (2 * PI) / 10;
	int r = 98;
	for (double i = 0; i < 10; i++) {
		GLfloat r0[3] = { r * cos(alpha * i), -30, -(r * sin(alpha * i)) };
		GLfloat r1[3] = { r * cos(alpha * (i + 1)), -30, -(r * sin(alpha * (i + 1))) };
		GLfloat r2[3] = { r * cos(alpha * (i + 1)), 30, -(r * sin(alpha * (i + 1))) };
		GLfloat r3[3] = { r * cos(alpha * i), 30, -(r * sin(alpha * i)) };
		glPushMatrix();
		glTranslatef(posCam[0], posCam[1], posCam[2]);
		quadtex(r0, r1, r2, r3, i * 0.2, ((i + 1) * 0.2), 0, 1);
		glPopMatrix();
	}

	glBindTexture(GL_TEXTURE_2D, carretera);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	int u2 = quad_inicial * 2 + 2;
	//Código para recta inicial
	if (u <= 50) {
		u2 = 52;
		quadtex(v0, v1, v2, v3, 0.0, 1.0, 0.0, 1.0, 1, 1);
		for (int i = 0; i <= 23; i++) {
			for (int j = 0; j < 3; j++) {
				v0[j] = v1[j];
				v3[j] = v2[j];
			}
			v1[0] = v1[0] + 2;
			v2[0] = v2[0] + 2;
			if (i == 13) {
				glBindTexture(GL_TEXTURE_2D, goal);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
				quadtex(v1, v2, v3, v0, 0.0, 1.0, 0.0, 1.0, 25, 25);
			}
			else{ 
				glBindTexture(GL_TEXTURE_2D, carretera); 
				quadtex(v0, v1, v2, v3, 0.0, 1.0, 0.0, 1.0, 25, 25);
			}
			
		}
		if (posCam[2] < -anchura / 2 || posCam[2] > anchura / 2) { puntuacion = INT_MIN;}
	}
	//Código para recta inicial
	float f2 = amplitud * sin((u2 * 2) * PI / periodo);
	float der_funcion_u2 = (2 * PI * amplitud * cos(((u2 * 2) * PI) / periodo)) / periodo;
	float modulo2 = sqrt(1 + der_funcion_u2 * der_funcion_u2);
	GLfloat n_izquierda2[3] = { -der_funcion_u2 / modulo2, 0, 1 / modulo2 };
	GLfloat prueba2[3] = { n_izquierda2[0] * anchura / 2 , 0, n_izquierda2[2] * anchura / 2 };
	/*
	if (u <= 50) {
		for (int j = 0; j < 3; j++) {
			v0[j] = v1[j];
			v3[j] = v2[j];
		}
		// El + en v1[2] y v2[2] es para ajustar la función a la recta inicial
		v1[0] = u2 + prueba2[0];
		v1[2] = f2 + prueba2[2] + 8;
		v2[0] = u2 - prueba2[0];
		v2[2] = f2 - prueba2[2] + 8;

		quadtex(v0, v1, v2, v3, 0.0, 1.0, 0.0, 1.0, 25, 25);
	}*/
	float f3 = amplitud * sin(((u2+2) * 2) * PI / periodo);
	if (!finRecorrido && (posCam[2] + direccion[2] < f3 + 7.25 -anchura / 2 || posCam[2] + direccion[2] > f3 + 8.75 + anchura / 2 || 
		(posCam[2] < f2 + 7.75 - anchura / 2 && abs(direccion[2]) <= 0.1) || (posCam[2] > f2 + 8.25 + anchura / 2 && abs(direccion[2]) <= 0.1) ||
		(posCam[2] < f3 + 7.75 - anchura / 2 && abs(direccion[2]) <= 0.15) || (posCam[2] > f3 + 8.25 + anchura / 2 && abs(direccion[2]) <= 0.15))) { puntuacion = INT_MIN; }
	GLfloat dir_central2[] = { 0, -1, 0 };
	for (int i = 2; i < 102; i++) {
		if (u <= 50) {
			u2 = 50 + 2*i;
		} else {
			u2 = quad_inicial * 2 + 2 * i;
		}

		f2 = amplitud * sin(((u2 * 2)) * PI / periodo);
		der_funcion_u2 = (2 * PI * amplitud * cos((((u2 * 2)) * PI) / periodo)) / periodo;
		modulo2 = sqrt(1 + der_funcion_u2 * der_funcion_u2);
		GLfloat n_izquierda3[3] = { -der_funcion_u2 / modulo2, 0, 1 / modulo2 };
		GLfloat prueba3[3] = { n_izquierda3[0] * anchura / 2 , 0, n_izquierda3[2] * anchura / 2 };
		for (int j = 0; j < 3; j++) {
			v0[j] = v1[j];
			v3[j] = v2[j];
		}
		// El + en v1[2] y v2[2] es para ajustar la función a la recta inicial
		v1[0] = u2 + prueba3[0];
		v1[2] = f2 + prueba3[2] + 8;
		v2[0] = u2 - prueba3[0];
		v2[2] = f2 - prueba3[2] + 8;
		//quad(v0, v1, v2, v3, 1, 5);
		glBindTexture(GL_TEXTURE_2D, carretera);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

		if (u > 900 && u <= 1026) {
			if (u2 == 1026) {
				glBindTexture(GL_TEXTURE_2D, goal);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
				quadtex(v1, v2, v3, v0, 0.0, 1.0, 0.0, 1.0, 25, 25);
			} else { quadtex(v0, v1, v2, v3, 0.0, 1.0, 0.0, 1.0, 25, 25); }
		}
		else {
			quadtex(v0, v1, v2, v3, 0.0, 1.0, 0.0, 1.0, 25, 25);
		}
		


		if (i == 2) {
			//light 2
			if (u <= 25) {
				GLfloat dir_central3[] = { 1, 0.9, 0 };
				GLfloat PL4[] = { 25 , 2, 0, 1 };
				glLightfv(GL_LIGHT2, GL_POSITION, PL4);
				glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir_central3);
			}
			else {
				GLfloat dir_central3[] = { 1, 0.9, 0 };
				if (u % ((u / 100) * 100 + 25) < 100) {
					u2 = ((u / 100) + 1) * 100 + 25;
					f2 = amplitud * sin(((u2 * 2)) * PI / periodo);
					GLfloat PL4[] = { u2 - 5 , 2, f2 + 8, 1 };
					glLightfv(GL_LIGHT2, GL_POSITION, PL4);
					glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir_central3);
					if (primero) {
						turno = !turno;
						primero = false;
					}
					DibujarPalos((float)u2, (float)(-f2 - 8 - anchura/ 2.1), 0.0f);
				}
				else {
					u2 = ((u / 100) * 100) + 25;
					f2 = amplitud * sin(((u2 * 2)) * PI / periodo);
					GLfloat PL4[] = { u2 - 5 , 2, f2 + 8, 1 };
					glLightfv(GL_LIGHT2, GL_POSITION, PL4);
					glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir_central3);
					primero = true;
					DibujarPalos((float)u2, (float)(-f2 - 8 - anchura / 2.1), 0.0f);
				}
			}
		}

		if (i == 3) {
			//light 3
			if (u <= 50) {
				GLfloat PL4[] = { 50 , 4, 0, 1 };
				glLightfv(GL_LIGHT3, GL_POSITION, PL4);
				glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir_central2);
			}
			else {
				if (u % ((u / 100) * 100 + 50) < 100) {
					u2 = ((u / 100) + 1) * 100 + 50;
					f2 = amplitud * sin(((u2 * 2)) * PI / periodo);
					GLfloat PL4[] = { u2 , 4, f2 + 8, 1 };
					glLightfv(GL_LIGHT3, GL_POSITION, PL4);
					glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir_central2);
				}
				else {
					u2 = ((u / 100) * 100) + 50;
					f2 = amplitud * sin(((u2 * 2)) * PI / periodo);
					GLfloat PL4[] = { u2 , 4, f2 + 8, 1 };
					glLightfv(GL_LIGHT3, GL_POSITION, PL4);
					glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir_central2);
				}
			}
		}

		if (i == 4) {
			//light 4
			if (u <= 75) {
				f2 = amplitud * sin((((75) * 2)) * PI / periodo);
				GLfloat PL4[] = { 75 , 4, f2 + 8, 1 };
				glLightfv(GL_LIGHT4, GL_POSITION, PL4);
				glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir_central2);
				DibujarCubo(PL4[0], 0.2, PL4[2]);
				DibujarCubo(PL4[0], 0.2, PL4[2] - anchura/4);
				DibujarCubo(PL4[0], 0.2, PL4[2] + anchura / 4);
				if (abs(posCam[0] - PL4[0]) < 1 && abs(posCam[2] - PL4[2]) < 1.6 && !item && hudON) {
					item = true;
				}
			}
			else {
				if (u % ((u / 100) * 100 + 75) < 100) {
					u2 = ((u / 100) + 1) * 100 + 75;
					f2 = amplitud * sin(((u2 * 2)) * PI / periodo);
					GLfloat PL4[] = { u2 , 4, f2 + 8, 1 };
					glLightfv(GL_LIGHT4, GL_POSITION, PL4);
					glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir_central2);
					DibujarCubo(PL4[0], 0.2, PL4[2]);
					DibujarCubo(PL4[0], 0.2, PL4[2] - anchura / 4);
					DibujarCubo(PL4[0], 0.2, PL4[2] + anchura / 4);
					if (abs(posCam[0] - PL4[0]) < 1 && abs(posCam[2] - PL4[2]) < 1.6 && !item && hudON) {
						item = true;
					}
				}
				else {
					u2 = ((u / 100) * 100) + 75;
					f2 = amplitud * sin(((u2 * 2)) * PI / periodo);
					GLfloat PL4[] = { u2 , 4, f2 + 8, 1 };
					glLightfv(GL_LIGHT4, GL_POSITION, PL4);
					glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir_central2);
					DibujarCubo(PL4[0], 0.2, PL4[2]);
					DibujarCubo(PL4[0], 0.2, PL4[2] - anchura/4);
					DibujarCubo(PL4[0], 0.2, PL4[2] + anchura / 4);
					if (abs(posCam[0] - PL4[0]) < 1 && abs(posCam[2] - PL4[2]) < 1.6 && !item && hudON) {
						item = true;
					}
				}
			}
		}
		
		if (i == 5) {
			//light 5
			if (u <= 100) {
				f2 = amplitud * sin((((100) * 2)) * PI / periodo);
				GLfloat PL4[] = { 100 , 4, f2 + 8, 1 };
				glLightfv(GL_LIGHT5, GL_POSITION, PL4);
				glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dir_central2);
			}
			else {
				if (u % ((u / 100) * 100 + 100) < 100) {
					u2 = ((u / 100) + 1) * 100 + 100;
					f2 = amplitud * sin(((u2 * 2)) * PI / periodo);
					GLfloat PL4[] = { u2 , 4, f2 + 8, 1 };
					glLightfv(GL_LIGHT5, GL_POSITION, PL4);
					glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dir_central2);
				}
				else {
					u2 = ((u / 100) * 100) + 100;
					f2 = amplitud * sin(((u2 * 2)) * PI / periodo);
					GLfloat PL4[] = { u2 , 4, f2 + 8, 1 };
					glLightfv(GL_LIGHT5, GL_POSITION, PL4);
					glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dir_central2);
				}
			}
		}
	}

	GLfloat k0[3] = { 0, 0, anchura / 2 };
	GLfloat k1[3] = { 2, 0, anchura / 2 };
	GLfloat k2[3] = { 2, 0, -anchura / 2 };
	GLfloat k3[3] = { 0, 0, -anchura / 2 };
	GLfloat k4[3] = { 0, 0.75, anchura / 2 };
	GLfloat k5[3] = { 2, 0.75, anchura / 2 };
	GLfloat k6[3] = { 0, 0.75, -anchura / 2 };
	GLfloat k7[3] = { 2, 0.75, -anchura / 2 };
	for (int j = 0; j < 3; j++) {
		v0[j] = k1[j];
		v1[j] = k1[j];
		v2[j] = k1[j];
		v3[j] = k2[j];
	}
	u2 = quad_inicial * 2 + 2;
	if (u <= 50) {
		u2 = 52;
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_LIGHTING);
		glDepthMask(GL_FALSE);
		glBindTexture(GL_TEXTURE_2D, valla);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		for (int i = 0; i <= 25; i++) {
			quadtex(k3, k6, k7, k2, 0.0, 1.0, 0.0, 1.0, 1, 1);
			quadtex(k0, k4, k5, k1, 0.0, 1.0, 0.0, 1.0, 1, 1);
			for (int j = 0; j < 3; j++) {
				k0[j] = k1[j];
				k4[j] = k5[j];
				k3[j] = k2[j];
				k6[j] = k7[j];
			}
			k1[0] = k1[0] + 2;
			k5[0] = k5[0] + 2;
			k2[0] = k2[0] + 2;
			k7[0] = k7[0] + 2;
		}
		glDepthMask(GL_TRUE);
		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);
		glPopAttrib();
	}
	
	if (u <= 50) {
		for (int j = 0; j < 3; j++) {
			v0[j] = v1[j];
			v3[j] = v2[j];
		}
		// El + en v1[2] y v2[2] es para ajustar la función a la recta inicial
		v1[0] = u2 + prueba2[0];
		v1[2] = f2 + prueba2[2] + 8;
		v2[0] = u2 - prueba2[0];
		v2[2] = f2 - prueba2[2] + 8;
	}
	for (int i = 2; i < 102; i++) {
		if (u <= 50) {
			u2 = 50 + 2 * i;
		}
		else {
			u2 = quad_inicial * 2 + 2 * i;
		}

		f2 = amplitud * sin(((u2 * 2)) * PI / periodo);
		der_funcion_u2 = (2 * PI * amplitud * cos((((u2 * 2)) * PI) / periodo)) / periodo;
		modulo2 = sqrt(1 + der_funcion_u2 * der_funcion_u2);
		GLfloat n_izquierda3[3] = { -der_funcion_u2 / modulo2, 0, 1 / modulo2 };
		GLfloat prueba3[3] = { n_izquierda3[0] * anchura / 2 , 0, n_izquierda3[2] * anchura / 2 };
		for (int j = 0; j < 3; j++) {
			v0[j] = v1[j];
			v3[j] = v2[j];
		}
		// El + en v1[2] y v2[2] es para ajustar la función a la recta inicial
		v1[0] = u2 + prueba3[0];
		v1[2] = f2 + prueba3[2] + 8;
		v2[0] = u2 - prueba3[0];
		v2[2] = f2 - prueba3[2] + 8;
		GLfloat v4[3];
		GLfloat v5[3];
		GLfloat v6[3];
		GLfloat v7[3];
		for (int j = 0; j < 3; j++) {
			if (j != 1) {
				v4[j] = v0[j];
				v5[j] = v1[j];
				v6[j] = v2[j];
				v7[j] = v3[j];
			}
			else {
				v4[j] = v0[j] + 0.75;
				v5[j] = v1[j] + 0.75;
				v6[j] = v2[j] + 0.75;
				v7[j] = v3[j] + 0.75;
			}
		}
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_LIGHTING);
		glDepthMask(GL_FALSE);
		glBindTexture(GL_TEXTURE_2D, valla);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		quadtex(v3, v7, v6, v2, 0.0, 1.0, 0.0, 1.0, 1, 1);
		quadtex(v0, v4, v5, v1, 0.0, 1.0, 0.0, 1.0, 1, 1);
		glDepthMask(GL_TRUE);
		glEnable(GL_LIGHTING);
		glDisable(GL_BLEND);
		glPopAttrib();
	}
	if(mostrarLakitu)if (!hiloLanzado) { hiloLanzado = true; std::thread th1(hiloAcabado); th1.detach(); }
	if (hudON) {
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_LIGHTING);
		glDepthMask(GL_FALSE);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		double wid = glutGet(GLUT_WINDOW_WIDTH);
		double hei = glutGet(GLUT_WINDOW_HEIGHT);
		float ar = wid / hei;
		glOrtho(-wid / 600 * ar, wid / 600 * ar, -hei / 600 * ar, hei / 600 * ar, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		switch (personaje % 4) {
		case(0): 
			if (girando == RECTO) { glBindTexture(GL_TEXTURE_2D, cocheM1); }
			else
			{
				glBindTexture(GL_TEXTURE_2D, cocheM2);
			}
			break;
		case(1): 
			if (girando == RECTO) { glBindTexture(GL_TEXTURE_2D, cocheL1); }
			else
			{
				glBindTexture(GL_TEXTURE_2D, cocheL2);
			}
			break;
		case(2): 
			if (girando == RECTO) { glBindTexture(GL_TEXTURE_2D, cocheP1); }
			else
			{
				glBindTexture(GL_TEXTURE_2D, cocheP2);
			}
			break;
		case(3): 
			if (girando == RECTO) { glBindTexture(GL_TEXTURE_2D, cocheB1); }
			else
			{
				glBindTexture(GL_TEXTURE_2D, cocheB2);
			}
			break;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		GLfloat c0[] = { -wid / 600 * 0.3,-hei / 600 * ar,0 };
		GLfloat c1[] = { wid / 600 * 0.3,-hei / 600 * ar,0 };
		GLfloat c2[] = { wid / 600  * 0.3,-hei / 600 * ar * 0.4,0 };
		GLfloat c3[] = { -wid / 600 * 0.3,-hei / 600 * ar * 0.4,0 };
		if (girando != IZQUIERDA) { quadtex(c0, c1, c2, c3, 0, 1, 0, 1, 1, 1); }
		else
		{
			quadtex(c1, c0, c3, c2, 0, 1, 0, 1, 1, 1);
		}
		
		glBindTexture(GL_TEXTURE_2D, roster);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		GLfloat r0[] = { -wid / 600 * 0.5, hei / 600 * ar * 0.75,0 };
		GLfloat r1[] = { wid / 600 * 0.5, hei / 600 * ar * 0.75,0 };
		GLfloat r2[] = { wid / 600 * 0.5, hei / 600 * ar,0 };
		GLfloat r3[] = { -wid / 600 * 0.5, hei / 600 * ar,0 };
		quadtex(r0, r1, r2, r3, 0, 1, 0, 1, 1, 1);

		glBindTexture(GL_TEXTURE_2D, window);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		float desplazamiento = personaje % 4;
		GLfloat w0[] = { -wid / 600 * 0.48 + wid / 600 * 0.243 * desplazamiento, hei / 600 * ar * 0.76,0 };
		GLfloat w1[] = { -wid / 600 * 0.25 + wid / 600 * 0.243 * desplazamiento, hei / 600 * ar * 0.76,0 };
		GLfloat w2[] = { -wid / 600 * 0.25 + wid / 600 * 0.243 * desplazamiento, hei / 600 * ar * 0.938,0 };
		GLfloat w3[] = { -wid / 600 * 0.48 + wid / 600 * 0.243 * desplazamiento, hei / 600 * ar * 0.938,0 };
		quadtex(w0, w1, w2, w3, 0, 1, 0, 1, 1, 1);

		if (mostrarLakitu) {
			GLfloat l0[] = { wid / 600 * 0.51, hei / 600 * ar * 0.3, 0 };
			GLfloat l1[] = { wid / 600 * 0.6, hei / 600 * ar * 0.3,0 };
			GLfloat l2[] = { wid / 600 * 0.6, hei / 600 * ar * lightRange,0 };
			GLfloat l3[] = { wid / 600 * 0.51, hei / 600 * ar * lightRange, 0 };

			glDisable(GL_TEXTURE_2D);
			glPushAttrib(GL_CURRENT_BIT);
			GLfloat CYAN[4] = { 0, 1, 1, 1 };
			glColor4f(isRed, isGreen, 0, 0.6);
			quad(l0, l1, l2, l3, 1, 1);
			glPopAttrib();
			if (!alambrico) { glEnable(GL_TEXTURE_2D); }
			
			glBindTexture(GL_TEXTURE_2D, lakitu);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			GLfloat d0[] = { wid / 600 * 0.5, hei / 600 * ar * 0.5,0 };
			GLfloat d1[] = { wid / 600 * 0.95, hei / 600 * ar * 0.5,0 };
			GLfloat d2[] = { wid / 600 * 0.95, 0,0 };
			GLfloat d3[] = { wid / 600 * 0.5, 0,0 };
			quadtex(d2, d3, d0, d1, 0, 1, 0, 1, 1, 1);
		}

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPushMatrix();
		glLoadIdentity();
		glOrtho(-1, 1, -1, 1, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		if (item) {
			glBindTexture(GL_TEXTURE_2D, seta);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, box);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		int tamaño = 150;
		if (wid < 250 || hei < 150) {
			tamaño = 75;
		}
		GLfloat o0[] = { -1 + tamaño / wid, 1 - tamaño / hei, 0 };
		GLfloat o1[] = { -1, 1 - tamaño / hei, 0 };
		GLfloat o2[] = { -1, 1, 0 };
		GLfloat o3[] = { -1 + tamaño / wid, 1, 0 };
		quadtex(o0, o1, o2, o3, 0, 1, 0, 1, 1, 1);

		
		if (u >= 1026 || puntuacion < 0) {

			glBindTexture(GL_TEXTURE_2D, pizarra);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			GLfloat p0[] = { 0.6 / (wid/600), 0.075, 0 };
			GLfloat p1[] = {-0.6 / (wid / 600), 0.075, 0 };
			GLfloat p2[] = { -0.6 / (wid / 600), 0.625, 0 };
			GLfloat p3[] = { 0.6 / (wid / 600), 0.625, 0 };
			quadtex(p1, p0, p3, p2, 0, 1, 0, 1, 1, 1);

			glPushAttrib(GL_CURRENT_BIT);
			std::string imprimir;
			std::string imprimir2;
			std::string imprimir3;
			std::string imprimir4;
			if (!finRecorrido) {
				ahora = glutGet(GLUT_ELAPSED_TIME);
				finRecorrido = true;
				setas = puntuacion / 500;
				ttrans = (ahora - antes) / 1000.0f;
				puntuacion += 900000 / ttrans;
				if (puntuacion > maximaPuntuacion) maximaPuntuacion = puntuacion;
			}
			if (puntuacion < 0) {
				glColor3f(1.0, 0.0, 0.0); imprimir = "DISQUALIFIED"; imprimir2 = "Press right click to restart";
			}
			else {
				float decimales = round((ttrans - round(ttrans - 0.5)) * 100 - 0.5);
				glColor3f(0.0, 1.0, 1.0);
				imprimir = "Score: " + std::to_string(puntuacion);
				imprimir2 = "Mushrooms: " + std::to_string(setas);
				imprimir3 = "Time: " + std::to_string((int)round(ttrans - 0.5)) + "." + std::to_string((int)decimales) + "s";
				imprimir4 = "Press right click to restart";
			}
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_FOG);
			std::string impresiones[4] = { imprimir, imprimir2, imprimir3, imprimir4 };
			for (int i = 0; i < size(impresiones); i++) {
				unsigned char* b = (unsigned char*)impresiones[i].c_str();
				int w = glutBitmapLength(GLUT_BITMAP_8_BY_13, b);
				glRasterPos2d(-0.525 / (wid / 600), 0.45 - 0.1 * i);
				int len = size(impresiones[i]);
				for (int i = 0; i < len; i++) {
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, b[i]);
				}
			}
			
			if (!alambrico) { glEnable(GL_TEXTURE_2D); }
			if (nieblaON) { glEnable(GL_FOG); }
			glPopAttrib();
		} 
		
		glBindTexture(GL_TEXTURE_2D, brujula);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		GLfloat b0[] = { -1 + (tamaño + 10) / wid, -1, 0 };
		GLfloat b1[] = { -1, -1, 0 };
		GLfloat b2[] = { -1, -1 + (tamaño + 10) / hei, 0 };
		GLfloat b3[] = { -1 + (tamaño + 10) / wid, -1 + (tamaño + 10) / hei, 0 };
		quadtex(b1, b0, b3, b2, 0, 1, 0, 1, 1, 1);

		GLfloat operacion = (velocidad[0] / 50.0);
		GLfloat m0[] = { 1, -1, 0 };
		GLfloat m1[] = { 1 - 60 / wid, -1,0 };
		GLfloat m2[] = { 1 - 60 / wid, -1 + operacion,0 };
		GLfloat m3[] = { 1, -1 + operacion, 0 };

		glDisable(GL_TEXTURE_2D);
		glPushAttrib(GL_CURRENT_BIT);
		glColor4f(0, 1, 0, 0.6);
		quad(m0, m1, m2, m3, 1, 1);

		glPushMatrix();
		glTranslatef(-1 + ((tamaño + 10) / 2) / wid, -1 + (-4 + 3 * tamaño/5)/hei, 0);
		glRotatef(-(direccion[2]) * 180 / PI, 0, 0, 1);
		glTranslatef(-1 * (-1 + ((tamaño + 10) / 2) / wid), -1 * (-1 + (-4 + 3 * tamaño / 5) / hei), 0);
		glColor4f(1, 0, 0, 0.6);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-1 + ((tamaño + 10) / 3) / wid, -1 + ((tamaño + 10) / 2.5) / hei, 0);
		glVertex3f(-1 + ((tamaño + 10) / 1.5) / wid, -1 + ((tamaño + 10) / 2.5) / hei, 0);
		glVertex3f(-1 + ((tamaño + 10) /2) / wid, -1 + (tamaño - 20) / hei, 0);
		glEnd();
		glColor4f(0, 0, 1, 0.4);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-1 + ((tamaño + 10) / 2) / wid, -1 + (tamaño - 20) / hei, 0);
		glVertex3f(-1 + ((tamaño + 10) / 1.75) / wid, -1 + (tamaño - 50) / hei, 0);
		glVertex3f(-1 + ((tamaño + 10) / 2.25) / wid, -1 + (tamaño - 50) / hei, 0);
		glEnd();
		glPopMatrix();
		glPopAttrib();

		if (!alambrico) { glEnable(GL_TEXTURE_2D); }

		if (music) {
			glBindTexture(GL_TEXTURE_2D, audio2);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, audio1);

		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		GLfloat a0[] = { 1 - tamaño / wid, 1 - tamaño / hei, 0 };
		GLfloat a1[] = { 1, 1 - tamaño / hei, 0 };
		GLfloat a2[] = { 1, 1, 0 };
		GLfloat a3[] = { 1 - tamaño / wid, 1, 0 };
		quadtex(a0, a1, a2, a3, 0, 1, 0, 1, 1, 1);


		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glDepthMask(GL_TRUE);
		glPopAttrib();
	}
	

	glPopAttrib();
	if (reset) {
		posCam[0] = 0;
		posCam[1] = 1;
		posCam[2] = 0;
		direccion[0] = 5;
		direccion[1] = 1;
		direccion[2] = 0;
		puntuacion = 0;
		setas = 0;
		velocidad[0] = 0;
		hudON = true;
		//music = true;
		//alambrico = false;
		//nightON = false;
		//nieblaON = false;
		mostrarLakitu = true;
		isRed = false;
		isGreen = false;
		finRecorrido = false;
		lightRange = 0.3;
		girando = RECTO;
		item = false;
		turno = true;
		reset = false;
	}

	glutSwapBuffers();
}

void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);

	float ar = (float)w / (float)h;

	// Crear la camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Perspectiva
	//La distancia de plano cercano tiene que ser siempre > 0

	gluPerspective(25, ar, 1, 100);
}

void onKey(unsigned char tecla, int x, int y) {
	switch (tecla) {
	case 'S': alambrico = !alambrico;
		break;
	case 's': alambrico = !alambrico;
		break;
	case 'N': nieblaON = !nieblaON;
		break;
	case 'n': nieblaON = !nieblaON;
		break;
	case 'C': hudON = !hudON;
		break;
	case 'c': hudON = !hudON;
		break;
	case 'L': nightON = !nightON;
		break;
	case 'l': nightON = !nightON;
		break;
	case 'A': if(hudON)personaje++;
		break;
	case 'a': if (hudON)personaje++;
		break;
	case 'M': music = !music;
		break;
	case 'm': music = !music;
		break;
	case 'Q': 
		if (item && hudON) {
			velocidad[0] = velocidad[0] + 5;
			item = false;
			if(!finRecorrido)puntuacion += 500;
		}
		break;
	case 'q':
		if (item && hudON) {
			velocidad[0] = velocidad[0] + 5;
			item = false;
			if (!finRecorrido)puntuacion += 500;
		}
		break;
	case 27: exit(0);
	}

	glutPostRedisplay();
}

void onIdle()
{
	//Control del tiempo en la animacion
	static const float vueltasXsegundo = 1;
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	int ahora = glutGet(GLUT_ELAPSED_TIME);

	float ttrans = (ahora - antes) / 1000.0f;

	posCam[0] = posCam[0] + (double)(velocidad[0]) * (double)ttrans;
	posCam[1] = posCam[1] + (double)modulo(velocidad[1]) * (double)ttrans;
	posCam[2] = posCam[2] + direccion[2]* (double)(velocidad[0]) * (double)ttrans;
	
	angulo += vueltasXsegundo * 360 * ttrans;
	antes = ahora;

	glutPostRedisplay();
}

void onTimer(int tiempo)
{
	glutTimerFunc(tiempo, onTimer, tiempo);
	onIdle();
}

void onSpecialKey(int specialKey, int x, int y) {
	int posicion = posCam[0];
	if (!mostrarLakitu) {
		switch (specialKey) {
		case GLUT_KEY_UP:
			velocidad[0] = velocidad[0] + 0.25;
			girando = RECTO;
			break;
		case GLUT_KEY_DOWN:
			velocidad[0] = velocidad[0] - 0.25;
			if (velocidad[0] < 0) { velocidad[0] = 0; }
			girando = RECTO;
			break;
		case GLUT_KEY_LEFT:
			direccion[2] -= rad(0.4);
			//alpha += 0.15;
			girando = IZQUIERDA;
			break;
		case GLUT_KEY_RIGHT:
			direccion[2] += rad(0.4);
			//alpha -= 0.15;
			girando = DERECHA;
			break;
		}
		//direccion[0] = sin(rad(alpha));
		//direccion[2] = cos(rad(alpha));
	}

	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	FreeImage_Initialise();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Practica 9");
	std::cout << "Practica 9 running" << "\n";
	std::cout << ":::::::::::::::::::::::::::::::::::OBJETIVO:::::::::::::::::::::::::::::::::::" << "\n";
	std::cout << "Llega a la meta (1000m) en el menor tiempo posible y usando el mayor numero de setas" << "\n";
	std::cout << "Cada seta da 500 puntos y aumenta tu velocidad. Si te sales de la carretera pierdes" << "\n";
	std::cout << ":::::::::::::::::::::::::::::::::::CONTROLES::::::::::::::::::::::::::::::::::" << "\n";
	std::cout << "1. Flecha izquierda / derecha: giro del vehiculo" << "\n";
	std::cout << "2. Flecha arriba / abajo : aumento / disminucion de la velocidad" << "\n";
	std::cout << "3. S / s : Activa / desactiva un modelo simple en alambrico de la practica 6 sin luces ni texturas" << "\n";
	std::cout << "4. L / l : Cambia entre modo diurno / nocturno" << "\n";
	std::cout << "5. N / n : Cambia el estado de la niebla(on / off)" << "\n";
	std::cout << "6. C / c : Cambia la visibilidad de elementos solidarios a la camara - HUD - (on / off)" << "\n";
	std::cout << "7. A / a : Cambia de personaje una vez el HUD esta activado" << "\n";
	std::cout << "8. Q / q : Si tienes una seta aumenta la velocidad (una vez el HUD esta activado y se ha atravesado un cubo)" << "\n";
	std::cout << "9. M / m : Activa / desactiva la musica" << "\n";
	std::cout << "10. Clic derecho: Abre un menu para reiniciar la carrera" << "\n" << std::endl;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	glutTimerFunc(1000 / TASAFPS, onTimer, 1000 / TASAFPS);
	glutKeyboardFunc(onKey);
	glutSpecialFunc(onSpecialKey);
	
	glutMainLoop();
	FreeImage_DeInitialise();
}