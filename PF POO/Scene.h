
//#define ScenePlantilla
#define SceneGAMEPADMiModificacion
//#define CambioLUZ01
#define CambioLUZ02

#include <Windows.h>
#include <gl\GLU.h>
#include <gl\GL.h>
#include "SkyDome.h"
#include "Terrain.h"
#include "Model.h"
#include "Water.h"
#include "Billboard.h"
#include "Fog.h"
#include "Camera.h"
#include "EventoLago.h"
#include "EventoNevar.h"
#include "Colisiones.h"
#define BILLSIZE 50


int cuenta01 = 0;
int cuenta02 = 0;

#ifdef ScenePlantilla

#include <gl\GLU.h>
#include <gl\GL.h>
#include "SkyDome.h"
#include "Terrain.h"
#include "Model.h"
#include "Water.h"
#include "Billboard.h"
#include "Fog.h"
#include "Camera.h"

#define BILLSIZE 50

//BIENVENIDO AL ARCHIVO MAS IMPORTANTE DE TU PROYECTO

class Scene : public Camera
{
public:

	HWND hWnd = 0;

	short int skyIndex, lightIndex;
	float skyRotation;

	SkyDome *skyDome = new SkyDome(hWnd, 32, 32, 500, L"Imagenes//espacio.bmp");
	Terrain *terrain;
	Water *lago;
	GLfloat AmbMat[4] = { 255, 255, 220, 1 };


	Billboard *billBoard[BILLSIZE];
	

	Scene(HWND hWnd)
	{
		this->hWnd = hWnd;
		skyIndex = lightIndex, skyRotation = 0;
		
		GLfloat AmbPos[] = { 0, 400, 400, 1 };

		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, AmbPos);

		//lago = Pista, busca en sus constructores para poder crear un lago.

		terrain = new Terrain(hWnd, L"Imagenes//terreno_moon02.bmp", L"Imagenes//moon_textura.jpg", L"Imagenes//moon_textura.jpg", 512, 512);
		

		Billboards(billBoard, hWnd);

		cameraInitialize();
	}

	void Billboards(Billboard *bills[], HWND hWnd)
	{
		//Aqui puedes crear algo util con un FOR quiza.
	}
	

	void render(HDC hDC)
	{
		skyRotation < 360 ? skyRotation +=0.1f : skyRotation = 0;

		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 0);
		glLoadIdentity();

		GLfloat AmbInt[] = { 0.1, 0.1, 0.1, 1 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbInt);
		py = terrain->Superficie(px, pz) * 4 + 6;

		cameraUpdate();

		//Skydome
		glPushMatrix();
			glTranslatef(0, 8, 0);
			glRotatef(skyRotation, 0, 1, 0);
			skyDome->Draw();
		glPopMatrix();

		//Terreno
		glPushMatrix();
			glScalef(1, 2, 1);
			terrain->Draw();
		glPopMatrix();


		glPushMatrix();
		for (int i = 0; i < BILLSIZE; i++)
			//Aqui puede ir algo en especial, en tu carpeta de HEADER_FILES, el primer archivo es la respuesta.
		glPopMatrix();


		SwapBuffers(hDC);
		
	}

	~Scene()
	{
		//NO OLVIDES PONER AQUI TODOS TUS PUNTEROS
		delete skyDome;
		delete terrain;
		
	}
};
#endif

#ifdef SceneGAMEPADMiModificacion

enum Tiempo_dia {

	dia,
	mediodia,
	atardecer,
	noche,
	medianoche,
	madrugada,
	nevara,
	nonevar,

};

class SceneGAMEPAD : public Camara, public Colision, public Random
{
public:

	short int skyIndex, lightIndex;
	float skyRotation;
	float ArdillaAnima = 7;
	float BellotaAnimaX, BellotaAnimaY;
	float Pez01AnimaX=0, Pez01AnimaY = 0, Pez01AnimaZ=0;
	float Pez02AnimaX=0, Pez02AnimaY = 0, Pez02AnimaZ=0;
	float CucharaAnimaX = 0, CucharaAnimaY = 0, CucharaAnimaZ = 0;
	float CerealAnimaX = 0, CerealAnimaY = 0, CerealAnimaZ = 0;
	bool Pez01Anima = true, Pez02Anima = true, CerealAnima = true;
	int contador = 0;
	float angulo = 0;
	double Trans_01 = 1.00000000000, Trans_02 = 0.00000000000, Trans_03 = 0.00000000000, Trans_04 = 0.00000000000,
		Trans_05 = 0.00000000000, Trans_06 = 0.00000000000;
	float Luz = 1.0;
	Tiempo_dia horadeldia;
	Tiempo_dia clima;
	bool burbuja = true;
	bool nieve = true;


	SkyDome *skyDomeCielo_01;
	SkyDome *skyDomeCielo_02;
	SkyDome *skyDomeCielo_03;
	SkyDome *skyDomeCielo_04;
	SkyDome *skyDomeCielo_05;
	SkyDome *skyDomeCielo_06;
	Terrain *terrain;
	Water *water;
	Billboard *billBoard[BILLSIZE];
	Billboard *Nevar[BILLSIZE];
	Billboard *Laguna[BILLSIZE];

	//MODELOS
	EDXFramework::Model *CASA01;
	EDXFramework::Model *NUBE01;
	EDXFramework::Model *NUBE02;
	EDXFramework::Model *NUBE03;
	EDXFramework::Model *SOL;
	EDXFramework::Model *PEZ01;
	EDXFramework::Model *PEZ02;
	EDXFramework::Model *ARDILLA;
	EDXFramework::Model *BELLOTA01;
	EDXFramework::Model *BELLOTA02;
	EDXFramework::Model *CEREAL;
	EDXFramework::Model *CUCHARA;
	EDXFramework::Model *TAZON;
	EDXFramework::Model *MESA;
	EDXFramework::Model *SILLA;
	EDXFramework::Model *LATA;
	EDXFramework::Model *VALLA01;
	EDXFramework::Model *VALLA02;
	EDXFramework::Model *CAJA;
	EDXFramework::Model *LAPTOP;
	

	SceneGAMEPAD(HWND hWnd)
	{
		posc = VectorRR(200, 50, 50);
		dirc = VectorRR(0, 0, -1);
		angulo = 0;
		skyIndex = lightIndex, skyRotation = 0;
		float AmbMat[] = { 1,1,1,1 };
		float AmbPos[] = { 1,1,1,1 };
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, AmbPos);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_DIFFUSE);
		glEnable(GL_NORMALIZE);

		
		////////////////////////////////////////////////////////////

		water = new Water(hWnd, L"Imagenes//water.bmp", L"Imagenes//water.jpg", 750, 750);
		skyDomeCielo_01 = new SkyDome(hWnd, 32, 32, 500, L"Imagenes//cielo_01.jpg");
		skyDomeCielo_02 = new SkyDome(hWnd, 32, 32, 500, L"Imagenes//cielo_02.jpg");
		skyDomeCielo_03 = new SkyDome(hWnd, 32, 32, 500, L"Imagenes//cielo_03.jpg");
		skyDomeCielo_04 = new SkyDome(hWnd, 32, 32, 500, L"Imagenes//cielo_04.jpg");
		skyDomeCielo_05 = new SkyDome(hWnd, 32, 32, 500, L"Imagenes//cielo_05.jpg");
		skyDomeCielo_06 = new SkyDome(hWnd, 32, 32, 500, L"Imagenes//cielo_06.jpg");
		terrain = new Terrain(hWnd, L"Imagenes//terreno_04.bmp", L"Imagenes//test1.jpg", L"Imagenes//test1.jpg", 750, 750);

		//MODELOS
		CASA01 = new EDXFramework::Model("Modelos//Casa//Casa.obj", "Modelos//Casa//TexturaCasa.bmp", 1);
		NUBE01 = new EDXFramework::Model("Modelos//Clouds//Cloud.obj", "Modelos//Clouds//cloud.bmp", 0);
		NUBE02 = new EDXFramework::Model("Modelos//Clouds//Cloud.obj", "Modelos//Clouds//cloud.bmp", 0);
		NUBE03 = new EDXFramework::Model("Modelos//Clouds//Cloud.obj", "Modelos//Clouds//cloud.bmp", 0);
		SOL = new EDXFramework::Model("Modelos//estambre//estambre.obj", "Modelos//estambre//estambresito.bmp", 0);
		PEZ01 = new EDXFramework::Model("Modelos//pez_01//TropicalFish01.obj", "Modelos//pez_01//TropicalFish01.bmp", 0);
		PEZ02 = new EDXFramework::Model("Modelos//pez_02//PEZ1.obj", "Modelos//pez_02//PEZ.bmp", 0);
        ARDILLA = new EDXFramework::Model("Modelos//ardillosho//Squirrel.obj", "Modelos//ardillosho//squirrel128.bmp", 0);
		BELLOTA01 = new EDXFramework::Model("Modelos//bellota//nuez.obj", "Modelos//bellota//nuez1.bmp", 0);
		BELLOTA02 = new EDXFramework::Model("Modelos//bellota//casco.obj", "Modelos//bellota//casco1.bmp", 0);
		CEREAL = new EDXFramework::Model("Modelos//Cereal//cerealito.obj", "Modelos//Cereal//cerealito.bmp", 0);
		CUCHARA = new EDXFramework::Model("Modelos//cuchara//cucharita.obj", "Modelos//cuchara//cuchara.bmp", 0);
		TAZON = new EDXFramework::Model("Modelos//Tazon//tazoncito.obj", "Modelos//Tazon//bowltex1.bmp", 0);
		MESA = new EDXFramework::Model("Modelos//Mesa//Mesa.obj", "Modelos//Mesa//cuchara.bmp", 0);
		SILLA = new EDXFramework::Model("Modelos//Silla//sillita.obj", "Modelos//Silla//TexturaSilla.bmp", 0);
		LATA = new EDXFramework::Model("Modelos//whiskas//whiskas.obj", "Modelos//whiskas//whiskastex.bmp", 0);
		VALLA01 = new EDXFramework::Model("Modelos//valla//valla.obj", "Modelos//valla//casco1.bmp", 0);
		VALLA02 = new EDXFramework::Model("Modelos//valla//valla.obj", "Modelos//valla//casco1.bmp", 0);
		CAJA = new EDXFramework::Model("Modelos//Box//Beat_The_Boss_3_-_Wooden_Crate.obj", "Modelos//Box//WoodenCrate_Texture_gradient.bmp", 0);
		LAPTOP = new EDXFramework::Model("Modelos//Laptop//laptop.obj", "Modelos//Laptop//laptop.bmp", 0);
		




		Billboards(billBoard, hWnd);
		Lago(Laguna, hWnd);
		Nevara(Nevar, hWnd);

	}

	void Billboards(Billboard *bills[], HWND hWnd)
	{
		float y = terrain->Superficie(0, 0);
		bills[0] = new Billboard(hWnd, L"Billboards//arbol01.png", 100, 100, -250, y, 80);
		bills[1] = new Billboard(hWnd, L"Billboards//arbol02.png", 100, 100, -180, y, -200);
		bills[2] = new Billboard(hWnd, L"Billboards//arbol04.png", 100, 100, 200, y, 150);
		bills[3] = new Billboard(hWnd, L"Billboards//pino01.png", 100, 100, -50, y, 300);
		bills[4] = new Billboard(hWnd, L"Billboards//pino04.png", 100, 125, 200, y, -250);

		bills[5] = new Billboard(hWnd, L"Billboards//arbol01.png", 100, 100, 137, y, -243);
		bills[6] = new Billboard(hWnd, L"Billboards//arbol02.png", 100, 100, -281, y, -49);
		bills[7] = new Billboard(hWnd, L"Billboards//arbol04.png", 100, 100, 258, y, 29);
		bills[8] = new Billboard(hWnd, L"Billboards//pino01.png", 100, 100, 43, y, 262);
		bills[9] = new Billboard(hWnd, L"Billboards//pino04.png", 100, 125, -267, y, 169);

		bills[10] = new Billboard(hWnd, L"Billboards//arbol01.png", 100, 100, 191, y, -131);
		bills[11] = new Billboard(hWnd, L"Billboards//arbol02.png", 100, 100, -155, y, -250);
		bills[12] = new Billboard(hWnd, L"Billboards//arbol04.png", 100, 100, -211, y, 252);
		bills[13] = new Billboard(hWnd, L"Billboards//pino01.png", 100, 100, -245, y, -144);
		bills[14] = new Billboard(hWnd, L"Billboards//pino04.png", 100, 125, 298, y, 80);

		bills[15] = new Billboard(hWnd, L"Billboards//arbol01.png", 100, 100, -115, y, 249);
		bills[16] = new Billboard(hWnd, L"Billboards//arbol02.png", 100, 100, 168, y, 255);
		bills[17] = new Billboard(hWnd, L"Billboards//arbol04.png", 100, 100, -228, y, 139);
		bills[18] = new Billboard(hWnd, L"Billboards//pino01.png", 100, 100, -275, y, 18);
		bills[19] = new Billboard(hWnd, L"Billboards//pino04.png", 100, 125, 273, y, -68);

		bills[20] = new Billboard(hWnd, L"Billboards//pino05.png", 100, 125, 96, y, 252);
	}

	void Lago(Billboard *bills[], HWND hWnd)
	{
		Random* BurbujaPosicion = new EventoLago(burbuja);

		int RAX = BurbujaPosicion->PosicionRandomX();
		int RAY = BurbujaPosicion->PosicionRandomY();
		int RAZ = BurbujaPosicion->PosicionRandomZ();


		bills[0] = new Billboard(hWnd, L"Billboards//burbuja01.png", 10, 10, RAX, RAY, RAZ);
		RAX = BurbujaPosicion->PosicionRandomX(); RAY = BurbujaPosicion->PosicionRandomY();	RAZ = BurbujaPosicion->PosicionRandomZ();
		bills[1] = new Billboard(hWnd, L"Billboards//burbuja02.png", 10, 10, RAX, RAY, RAZ);
		RAX = BurbujaPosicion->PosicionRandomX(); RAY = BurbujaPosicion->PosicionRandomY();	RAZ = BurbujaPosicion->PosicionRandomZ();
		bills[2] = new Billboard(hWnd, L"Billboards//burbuja03.png", 10, 10, RAX, RAY, RAZ);

		RAX = BurbujaPosicion->PosicionRandomX(); RAY = BurbujaPosicion->PosicionRandomY();	RAZ = BurbujaPosicion->PosicionRandomZ();
		bills[3] = new Billboard(hWnd, L"Billboards//burbuja01.png", 10, 10, -RAX, RAY, RAZ);
		RAX = BurbujaPosicion->PosicionRandomX(); RAY = BurbujaPosicion->PosicionRandomY();	RAZ = BurbujaPosicion->PosicionRandomZ();
		bills[4] = new Billboard(hWnd, L"Billboards//burbuja02.png", 10, 10, -RAX, RAY, RAZ);
		RAX = BurbujaPosicion->PosicionRandomX(); RAY = BurbujaPosicion->PosicionRandomY();	RAZ = BurbujaPosicion->PosicionRandomZ();
		bills[5] = new Billboard(hWnd, L"Billboards//burbuja03.png", 10, 10, -RAX, RAY, RAZ);

		RAX = BurbujaPosicion->PosicionRandomX(); RAY = BurbujaPosicion->PosicionRandomY();	RAZ = BurbujaPosicion->PosicionRandomZ();
		bills[6] = new Billboard(hWnd, L"Billboards//burbuja01.png", 10, 10, RAX, RAY, -RAZ);
		RAX = BurbujaPosicion->PosicionRandomX(); RAY = BurbujaPosicion->PosicionRandomY();	RAZ = BurbujaPosicion->PosicionRandomZ();
		bills[7] = new Billboard(hWnd, L"Billboards//burbuja02.png", 10, 10, RAX, RAY, -RAZ);
		RAX = BurbujaPosicion->PosicionRandomX(); RAY = BurbujaPosicion->PosicionRandomY();	RAZ = BurbujaPosicion->PosicionRandomZ();
		bills[8] = new Billboard(hWnd, L"Billboards//burbuja03.png", 10, 10, RAX, RAY, -RAZ);

		RAX = BurbujaPosicion->PosicionRandomX(); RAY = BurbujaPosicion->PosicionRandomY();	RAZ = BurbujaPosicion->PosicionRandomZ();
		bills[9] = new Billboard(hWnd, L"Billboards//burbuja01.png", 10, 10, -RAX, RAY, -RAZ);
		RAX = BurbujaPosicion->PosicionRandomX(); RAY = BurbujaPosicion->PosicionRandomY();	RAZ = BurbujaPosicion->PosicionRandomZ();
		bills[10] = new Billboard(hWnd, L"Billboards//burbuja02.png", 10, 10, -RAX, RAY, -RAZ);
		RAX = BurbujaPosicion->PosicionRandomX(); RAY = BurbujaPosicion->PosicionRandomY();	RAZ = BurbujaPosicion->PosicionRandomZ();
		bills[11] = new Billboard(hWnd, L"Billboards//burbuja03.png", 10, 10, -RAX, RAY, -RAZ);


	}

	void Nevara(Billboard *bills[], HWND hWnd)
	{
		float y = terrain->Superficie(0, 0);

		
		Random* NievePosicion = new EventoNevar(nieve);

		int RAX = NievePosicion->PosicionRandomX();
		int RAY = NievePosicion->PosicionRandomY();
		int RAZ = NievePosicion->PosicionRandomZ();

		bills[0] = new Billboard(hWnd, L"Billboards//copos01.png", 5, 5, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[1] = new Billboard(hWnd, L"Billboards//copos02.png", 5, 5, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[2] = new Billboard(hWnd, L"Billboards//copos03.png", 1,1, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[3] = new Billboard(hWnd, L"Billboards//copos04.png", 10, 10, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[4] = new Billboard(hWnd, L"Billboards//copos04.png", 5, 5, RAX, RAY, RAZ);
		
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[5] = new Billboard(hWnd, L"Billboards//copos04.png", 5, 5, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[6] = new Billboard(hWnd, L"Billboards//copos04.png", 5, 5, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[7] = new Billboard(hWnd, L"Billboards//copos04.png", 1, 1, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[8] = new Billboard(hWnd, L"Billboards//copos04.png", 10, 10, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[9] = new Billboard(hWnd, L"Billboards//copos04.png", 5, 5, RAX, RAY, RAZ);

		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[10] = new Billboard(hWnd, L"Billboards//copos02.png", 5, 5, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[11] = new Billboard(hWnd, L"Billboards//copos02.png", 5, 5, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[12] = new Billboard(hWnd, L"Billboards//copos02.png", 1, 1, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[13] = new Billboard(hWnd, L"Billboards//copos02.png", 10, 10, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[14] = new Billboard(hWnd, L"Billboards//copos02.png", 5, 5, RAX, RAY, RAZ);

		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[15] = new Billboard(hWnd, L"Billboards//destello01.png", 5, 5, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[16] = new Billboard(hWnd, L"Billboards//destello01.png", 5, 5, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[17] = new Billboard(hWnd, L"Billboards//destello01.png", 10, 10, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[18] = new Billboard(hWnd, L"Billboards//destello01.png", 10, 10, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[19] = new Billboard(hWnd, L"Billboards//destello01.png", 5, 5, RAX, RAY, RAZ);

		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[20] = new Billboard(hWnd, L"Billboards//destello02.png", 5, 5, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[21] = new Billboard(hWnd, L"Billboards//destello02.png", 5, 5, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[22] = new Billboard(hWnd, L"Billboards//destello02.png", 10, 10, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[23] = new Billboard(hWnd, L"Billboards//destello02.png", 10, 10, RAX, RAY, RAZ);
		RAX = NievePosicion->PosicionRandomX(); RAY = NievePosicion->PosicionRandomY(); RAZ = NievePosicion->PosicionRandomZ();
		bills[24] = new Billboard(hWnd, L"Billboards//destello02.png", 5, 5, RAX, RAY, RAZ);

	}

	void render(HDC hDC, HWND hWnd)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 0);
		glLoadIdentity();
		GLfloat AmbInt[] = { Luz ,Luz, Luz, Luz };
		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbInt);
		posc.Y = terrain->Superficie(posc.X, posc.Z) * 4 + 15;
		CamaraUpdate();


		//AGUA
		        {
			       glPushMatrix();
			       glScalef(1, 0, 1);
			       glTranslatef(50, 0, -50);
		           //glScalef(0.25, 0, .25);		
		           water->Draw();
		           glPopMatrix();
		       }
		// SKYDOME DEL CIELO EN SUS DISTINTAS HORAS DEL DIA :)
				{
#ifdef CambioLUZ01	  
					skyRotation < 360 ? skyRotation += 0.1f : skyRotation = 0;
					glPushMatrix();
					glTranslatef(0, 8, 0);
					glRotatef(skyRotation, 0, 1, 0);
					//Para Habilitar la transparencia(la variable ALPHA) poner las dos lineas de abajo
					//Si está habilitado, combina los valores de color de fragmentos calculados con los valores en los búferes de color
					//Aqui se hace el cambio de transparencia,por alguna razon se ebe afectar los 4 parametros(R,G,B,A)
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glColor4f(Trans_01, Trans_01, Trans_01, Trans_01);
					skyDomeCielo_01->Draw();
					glDisable(GL_BLEND);
					glPopMatrix();
#endif

#ifdef CambioLUZ02
					switch (horadeldia) {
					case dia:
					{//Skydome Cielo_01
						skyRotation < 360 ? skyRotation += 0.1f : skyRotation = 0;
						glPushMatrix();
						glTranslatef(0, 8, 0);
						glRotatef(skyRotation, 0, 1, 0);
						//Para Habilitar la transparencia(la variable ALPHA) poner las dos lineas de abajo
						//Si está habilitado, combina los valores de color de fragmentos calculados con los valores en los búferes de color
						//Aqui se hace el cambio de transparencia,por alguna razon se ebe afectar los 4 parametros(R,G,B,A)
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						glColor4f(Trans_01, Trans_01, Trans_01, Trans_01);
						skyDomeCielo_01->Draw();
						glDisable(GL_BLEND);
						glPopMatrix();

						break;
					}
					case mediodia:
					{	//Skydome Cielo_02
						skyRotation < 360 ? skyRotation += 0.1f : skyRotation = 0;
						glPushMatrix();
						glTranslatef(0, 8, 0);
						glRotatef(skyRotation, 0, 1, 0);
						//Para Habilitar la transparencia(la variable ALPHA) poner las dos lineas de abajo
						//Si está habilitado, combina los valores de color de fragmentos calculados con los valores en los búferes de color
						//Aqui se hace el cambio de transparencia,por alguna razon se ebe afectar los 4 parametros(R,G,B,A)
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						glColor4f(Trans_02, Trans_02, Trans_02, Trans_02);
						skyDomeCielo_02->Draw();
						glDisable(GL_BLEND);
						glPopMatrix();
						break;
					}
					case atardecer:
					{	 //Skydome Cielo_03
						skyRotation < 360 ? skyRotation += 0.1f : skyRotation = 0;
						glPushMatrix();
						glTranslatef(0, 8, 0);
						glRotatef(skyRotation, 0, 1, 0);
						//Para Habilitar la transparencia(la variable ALPHA) poner las dos lineas de abajo
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						//Aqui se hace el cambio de transparencia,por alguna razon se ebe afectar los 4 parametros(R,G,B,A)
						glColor4f(Trans_03, Trans_03, Trans_03, Trans_03);
						skyDomeCielo_03->Draw();
						glDisable(GL_BLEND);
						glPopMatrix();
						break;
					}
					case noche:
					{	 //Skydome Cielo_04
						skyRotation < 360 ? skyRotation += 0.1f : skyRotation = 0;
						glPushMatrix();
						glTranslatef(0, 8, 0);
						glRotatef(skyRotation, 0, 1, 0);
						//Para Habilitar la transparencia(la variable ALPHA) poner las dos lineas de abajo
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						//Aqui se hace el cambio de transparencia,por alguna razon se ebe afectar los 4 parametros(R,G,B,A)
						glColor4f(Trans_04, Trans_04, Trans_04, Trans_04);
						skyDomeCielo_04->Draw();
						glDisable(GL_BLEND);
						glPopMatrix();
						break;
					}
					case medianoche:
					{	//Skydome Cielo_05
						skyRotation < 360 ? skyRotation += 0.1f : skyRotation = 0;
						glPushMatrix();
						glTranslatef(0, 8, 0);
						glRotatef(skyRotation, 0, 1, 0);
						//Para Habilitar la transparencia(la variable ALPHA) poner las dos lineas de abajo
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						//Aqui se hace el cambio de transparencia,por alguna razon se ebe afectar los 4 parametros(R,G,B,A)
						glColor4f(Trans_05, Trans_05, Trans_05, Trans_05);
						skyDomeCielo_05->Draw();
						glDisable(GL_BLEND);
						glPopMatrix();
						break;
					}
					case madrugada:
					{//Skydome Cielo_06
						skyRotation < 360 ? skyRotation += 0.1f : skyRotation = 0;
						glPushMatrix();
						glTranslatef(0, 8, 0);
						glRotatef(skyRotation, 0, 1, 0);
						//Para Habilitar la transparencia(la variable ALPHA) poner las dos lineas de abajo
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						//Aqui se hace el cambio de transparencia,por alguna razon se ebe afectar los 4 parametros(R,G,B,A)
						glColor4f(Trans_06, Trans_06, Trans_06, Trans_06);
						skyDomeCielo_06->Draw();
						glDisable(GL_BLEND);
						glPopMatrix();
						break;
					}
					}
#endif
				}
		//TERRENO
				{
					glPushMatrix();
					AmbInt[0] = Luz; AmbInt[1] = Luz; AmbInt[2] = Luz; AmbInt[3] = Luz;
					glLightfv(GL_LIGHT0, GL_AMBIENT, AmbInt);
					glColor4f(1.0, 1.0, 1.0, 1.0);
					GLfloat LightPos[] = { 0.0, 0.0,0.0, 0.0 };
					glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
					glScalef(1, 3, 1);
					glTranslatef(2, -3, 2);
					terrain->Draw();
					glPopMatrix();
				}

		// BILLBOARDS
				{
					Random* BurbujaPosicion = new EventoLago(burbuja);
					int RAX01 = BurbujaPosicion->PosicionRandomX();
					int RAY01 = BurbujaPosicion->PosicionRandomY();
					int RAZ01 = BurbujaPosicion->PosicionRandomZ();

					Random* NievePosicion = new EventoNevar(nieve);
					int RAX02 = NievePosicion->PosicionRandomX();
					int RAY02 = NievePosicion->PosicionRandomY();
					int RAZ02 = NievePosicion->PosicionRandomZ();

					//Billboards Normales
				   for (int i = 0; i <= 20; i++) {
					   glPushMatrix();
					   glPushAttrib(GL_TEXTURE_BIT);
					   billBoard[i]->Draw(posc.X, posc.Y, posc.Z);
					   glPopMatrix();
				   }

				   //Billboards Del Lago
				   for (int i = 0; i <= 11; i++) {
					   glPushMatrix();
					   glPushAttrib(GL_TEXTURE_BIT);
					   if (cuenta01 == 30) {
						   RAX01 = BurbujaPosicion->PosicionRandomX(); RAY01 = BurbujaPosicion->PosicionRandomY(); RAZ01 = BurbujaPosicion->PosicionRandomZ();
						   Laguna[i]->x = RAX01;
						   Laguna[i]->y = RAY01;
						   Laguna[i]->z = RAZ01;
						   cuenta01 = 0;
					   }
					   else {
						   cuenta01++;
					   }
					   Laguna[i]->Draw(posc.X, posc.Y, posc.Z);
					   glPopMatrix();
				   }

				   if (clima == nevara) {
					   //Billboards Del Evento Climatico
					   for (int i = 0; i <= 24; i++) {
						   glPushMatrix();
						   glPushAttrib(GL_TEXTURE_BIT);
						   if (cuenta02 == 30) {
							   RAX02 = NievePosicion->PosicionRandomX(); RAY02 = NievePosicion->PosicionRandomY(); RAZ02 = NievePosicion->PosicionRandomZ();
							   Nevar[i]->x = RAX02;
							   Nevar[i]->y = RAY02;
							   Nevar[i]->z = RAZ02;
							   cuenta02 = 0;
						   }
						   else {
							   cuenta02++;
						   }
						   Nevar[i]->Draw(posc.X, posc.Y, posc.Z);
						   glPopMatrix();
					   }
				   }
				}
		//MODELOS
				{
					//CASA01
					glPushMatrix();
					glTranslatef(0, 0, -260);
					glScalef(2.5, 2.5, 2.5);
					CASA01->Draw();
					glPopMatrix();
					glPushMatrix();

					//NUBE01
					glPushMatrix();
					glTranslatef(-150, 200, 150);
					NUBE01->Draw();
					glPopMatrix();
					glPushMatrix();

					//NUBE02
					glPushMatrix();
					glTranslatef(100, 200, -300);
					NUBE02->Draw();
					glPopMatrix();
					glPushMatrix();

					//NUBE03
					glPushMatrix();
					glTranslatef(100, 200, 180);
					NUBE03->Draw();
					glPopMatrix();
					glPushMatrix();

					//SOL
					glPushMatrix();
					glTranslatef(0, 200, 0);
					glScalef(4, 4, 4);
					SOL->Draw();
					glPopMatrix();
					glPushMatrix();
				
				    //PEZ01
				    glPushMatrix();					
					if (Pez01Anima == true) {
						if (Pez01AnimaY <=20) {
							Pez01AnimaY += 0.5f;
						}
						else {
							Pez01Anima = false;
						}
					}
					else {
						if (Pez01AnimaY >= -5) {
							Pez01AnimaY -= 0.5f;
						}
						else {
							Pez01Anima = true;
						}
					}
					Pez01AnimaX < 360 ? Pez01AnimaX += 3 : Pez01AnimaX = 0;
					Pez01AnimaZ < 360 ? Pez01AnimaZ += 0.75f : Pez01AnimaZ = 0;
				    glTranslatef(-5, Pez01AnimaY, RandomZ);
					//glTranslatef(-5, Pez01AnimaY, -57);
					glRotatef(-Pez01AnimaX, 1, 0, 0);
					glRotatef(-Pez01AnimaZ, 0, 0, 1);
				    glScalef(0.025, 0.025, 0.025);
				    PEZ01->Draw();
				    glPopMatrix();
				    glPushMatrix();

					////PEZ02
					glPushMatrix();
					Pez02AnimaZ < 360 ? Pez02AnimaZ += 5 : Pez02AnimaZ = 0;
					if (Pez02Anima == true) {
						if (Pez02AnimaY <= 3) {
							Pez02AnimaY += 0.25f;
							Pez02AnimaX += 0.5f;							
						}
						else {
							Pez02Anima = false;
						}
					}
					else {
						if (Pez02AnimaY >= -20) {
							Pez02AnimaY -= 0.25f;
							Pez02AnimaX -= 0.5f;
					}	else {
							
							Pez02Anima = true;
						}
					}
					glTranslatef(Pez02AnimaX, Pez02AnimaY, -52);
					glRotatef(Pez02AnimaZ, 0, 0, 1);
					glScalef(0.5, 0.5, 0.5);
					PEZ02->Draw();
					glPopMatrix();
					glPushMatrix();


				    //ARDILLA
					glPushMatrix();
					ArdillaAnima < 15 ? ArdillaAnima += 0.60f : ArdillaAnima = 7;
					glTranslatef(245, ArdillaAnima, 155);
					glScalef(1.5, 1.5, 1.5);
					ARDILLA->Draw();
					glPopMatrix();
					glPushMatrix();

					//BELLOTA NUEZ
					glPushMatrix();
					BellotaAnimaY > -5 ? BellotaAnimaY -= 0.1f : BellotaAnimaY = 50;
					BellotaAnimaX < 360 ? BellotaAnimaX += 0.25f : BellotaAnimaX = 0;
					glTranslatef(240, BellotaAnimaY, 178);
					glRotatef(BellotaAnimaX, 0, 1, 0);
					glRotatef(50, 0, 0, -10);
					BELLOTA01->Draw();
					glPopMatrix();
					glPushMatrix();

					//BELLOTA CASCO
					glPushMatrix();
					BellotaAnimaY > -5 ? BellotaAnimaY -= 0.1f : BellotaAnimaY = 50;
					BellotaAnimaX < 360 ? BellotaAnimaX += 0.25f : BellotaAnimaX = 0;
					glTranslatef(240, BellotaAnimaY, 178);
					glRotatef(BellotaAnimaX, 0, 1, 0);
					glRotatef(50, 0, 0, -10);
					BELLOTA02->Draw();
					glPopMatrix();
					glPushMatrix();

					//CEREAL
					glPushMatrix();

					if (CerealAnima == true) {
						if (CerealAnimaY <= 3) {
							CerealAnimaY += 0.25f;
						}
						else {
							CerealAnima = false;
						}
					}
					else {
						if (CerealAnimaY >= -20) {
							CerealAnimaY -= 0.25f;
						}
						else {
							CerealAnima = true;
						}
					}
					glTranslatef(1.5, 28, -300);
					glScalef(.25, .25, .25);
					glRotatef(30, 0, 10, 0);
					CEREAL->Draw();
					glPopMatrix();
					glPushMatrix();

					//CUCHARA
					glPushMatrix();
					CucharaAnimaZ < 360 ? CucharaAnimaZ += 0.75f : CucharaAnimaZ = 0;
					glTranslatef(12, 38, -306);
					glRotatef(60, 0, 0, -10);
					glRotatef(90, -10, 0, 0);
					glRotatef(CucharaAnimaZ, 0, 0, 1);
					//glScalef(2, 2, 2);
					CUCHARA->Draw();
					glPopMatrix();
					glPushMatrix();

					//TAZON
					glPushMatrix();
					glTranslatef(15, 26, -275);
					TAZON->Draw();
					glPopMatrix();
					glPushMatrix();

					//MESA
					glPushMatrix();
					glTranslatef(10, 10, -303);
					glScalef(.025, .025, .025);
					MESA->Draw();
					glPopMatrix();
					glPushMatrix();

					//SILLA
					glPushMatrix();
					glTranslatef(30, -60, -300);
					glScalef(2.25, 2.25, 2.25); 
					glRotatef(40, 0, 10, 0);
					SILLA->Draw();
					glPopMatrix();
					glPushMatrix();

					//LATA
					glPushMatrix();
					glTranslatef(25, 28, -300);
					LATA->Draw();
					glPopMatrix();
					glPushMatrix();

					////VALLA01
					glPushMatrix();
					glTranslatef(93, 0, -350);
					VALLA01->Draw();
					glPopMatrix();
					glPushMatrix();

					////VALLA02
					glPushMatrix();
					glTranslatef(-82, 0, -350);
					VALLA02->Draw();
					glPopMatrix();
					glPushMatrix();

					//CAJA
					glPushMatrix();
					glTranslatef(40, 20, -310);
					glScalef(12, 12, 12);
					glRotatef(-20, 0, 10, 0);
					CAJA->Draw();
					glPopMatrix();
					glPushMatrix();

					//LAPTOP
					glPushMatrix();
					glTranslatef(38, 25, -310);
					glScalef(6, 6, 6);
					glRotatef(-20, 0, 10, 0);
					LAPTOP->Draw();
					glPopMatrix();
					glPushMatrix();
				}
		

		//COLISIONES
				{
					//COLISIONES CASA
						 //Donde solo se manda posicion X y Z de la camara y de la recta X, Z formada por dos 
						 // puntos, en si esta colision esta formada como si fuera de tipo Rectangulo-Punto


					ColisionPared = true;

					// PAREDES AFUERA
					if (PuntoLinea<float>(posc.X, posc.Z, 58, -173, 60, -345) == true)
					{
						MessageBox(hWnd, "ño", "Ño ño ño, no puedes pasar por aqui", MB_OK);
						if (posc.X < 0) {
							//IZQUIERDA
							posc.X = posc.X - 20;
						}
						else {
							//DERECHA
							posc.X = posc.X + 20;
						}

					}

					// PAREDES ADENTRO
					if (PuntoLinea<float>(posc.X, posc.Z, 56, -173, 58, -345) == true)
					{
						MessageBox(hWnd, "ño", "Ño ño ño, no puedes pasar por aqui", MB_OK);

						if (posc.X < 0) {
							//IZQUIERDA
							posc.X = posc.X + 20;
						}
						else {
							//DERECHA
							posc.X = posc.X - 20;
						}
					}

					ColisionPared = false;

					//PARED PUERTA ENFRENTE
					if (PuntoLinea<float>(posc.X, posc.Z, -58, -175, -32, -170) == true)
					{
						MessageBox(hWnd, "ño", "Ño ño ño, no puedes pasar por aqui", MB_OK);
						if (posc.Z <= -172.5) {
							//IZQUIERDA
							posc.Z = posc.Z - 20;

						}
						else {
							//DERECHA
							posc.Z = posc.Z + 20;
						}

					}

					//PARED PUERTA DEBAJO
					if (PuntoLinea<float>(posc.X, posc.Z, -4, -175, 58, -170) == true)
					{
						MessageBox(hWnd, "ño", "Ño ño ño, no puedes pasar por aqui", MB_OK);
						if (posc.Z <= -172.5) {
							//IZQUIERDA
							posc.Z = posc.Z - 20;

						}
						else {
							//DERECHA
							posc.Z = posc.Z + 20;
						}

					}

					// COLISIONES DEL TERRENO
						// Aqui las colisiones son de tipo Recta-Esfera (PUNTO)
						// Posicion X y Z de la camara, el radio de colision de la camara,
						// Posicion X y Z de un punto izquierdo, X y Z del otro punto derecho dependiendo de
						// Como este situada mi camara, haciendo referencia a una recta

						// DERECHA DE LA CAMARA
					if (EsferaLinea<float>(posc.X, posc.Z, 5, 284, 298, 284, -277) == true)
					{
						MessageBox(hWnd, "ño", "Ño ño ño, no puedes pasar por aqui", MB_OK);
						posc.X = posc.X - 20;

					}

					//IZQUIERDA DE LA CAMARA
					if (EsferaLinea<float>(posc.X, posc.Z, 5, -300, 237, -300, -313) == true)
					{
						MessageBox(hWnd, "ño", "Ño ño ño, no puedes pasar por aqui", MB_OK);
						posc.X = posc.X + 20;

					}

					//ATRAS DE LA CAMARA
					if (EsferaLinea<float>(posc.X, posc.Z, 5, 250, 280, -310, 280) == true)
					{
						MessageBox(hWnd, "ño", "Ño ño ño, no puedes pasar por aqui", MB_OK);
						posc.Z = posc.Z - 20;

					}

					//ADELANTE DE LA CAMARA
					if (EsferaLinea<float>(posc.X, posc.Z, 5, 284, -300, -248, -300) == true)
					{
						MessageBox(hWnd, "ño", "Ño ño ño, no puedes pasar por aqui", MB_OK);
						posc.Z = posc.Z + 20;

					}
				}


		glPopMatrix();
		SwapBuffers(hDC);

	}

	~SceneGAMEPAD()
	{
		delete skyDomeCielo_01;
		delete skyDomeCielo_02;
		delete skyDomeCielo_03;
		delete skyDomeCielo_04;
		delete skyDomeCielo_05;
		delete skyDomeCielo_06;
		delete terrain;
		delete water;
		delete CASA01;
		delete NUBE01;
		delete NUBE02;
		delete NUBE03;
		delete SOL;
		delete PEZ01;
		delete PEZ02;
		delete ARDILLA;
		delete BELLOTA01;
		delete BELLOTA02;
		delete CEREAL;
		delete CUCHARA;
		delete TAZON;
		delete MESA;
		delete SILLA;
		delete LATA;
		delete VALLA01;
		delete VALLA02;
		delete CAJA;
		delete LAPTOP;


	}
};
#endif
