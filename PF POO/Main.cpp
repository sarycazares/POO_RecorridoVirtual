#include <Windows.h>
#include "glew.h"
#include <gl\GLU.h>
#include <gl\GL.h>
#include "Scene.h"
#include <time.h>
#include "GamePadRR.h"
#include "resource.h"
#pragma comment (lib, "glew32.lib") 
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib") 

#define Timer1 100

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void DefPixelFormat(HDC hDC);

HWND hInfo = 0;
HWND hText = 0;
bool ableToCheck = false;
HDC hContextoVentana;
HDC hdc;
SceneGAMEPAD *Scene;
GamePadRR *gamPad;
bool renderiza = false;
float velocidad;
unsigned int dayTimer = 0;
unsigned int contador = 0;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwndVentana;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX); //Tamaño en bytes de la estructura.
	wc.style = CS_HREDRAW | CS_VREDRAW; //Entero de 16 bits que codifica el estilo de la clase de ventana.
	wc.lpfnWndProc = WindowProc;//Apunta al procedimiento de ventana.
	wc.hInstance = hInstance;//Identifica la instancia de la ventana a la que esta clase pertenece.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//Identificador del curso de la clase. Debe ser un manipulador de un recurso de tipo icono. Si es Null, la aplicación mostrará un icono cuando el usuario minice la ventana de la aplicación.
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; //Identificador del pincel para la clase.
	wc.lpszClassName = "Window"; //Especifica el nombre de la clase ventana.
	RegisterClassEx(&wc);//Registra una clase de ventana para su uso subsecuente en llamadas a las funciones CreateWindow o CreateWindowEx
	RECT wr = { 0, 0, 1080, 720 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);//Calcula el tamaño necesario del rectángulo de la ventana.

	//Se crea la ventana definida previamente.
	hwndVentana = CreateWindowEx(NULL,//estilo extendido de ventana
		"Window",//puntero al nombre de la clase registrada *visto arriba*
		"Ventana Proyecto de POO",//puntero al nombre de la ventana
		WS_OVERLAPPEDWINDOW,//estilo de ventana
		0,//posición horizontal de la ventana
		0,//posición vertical de la ventana
		wr.right - wr.left,//ancho de la ventana
		wr.bottom - wr.top,//alto de la ventana
		NULL,//manejador de la ventana padre o propietaria
		NULL,//manejador del menu o identificador de ventana hija
		hInstance,//manejador de la instancia de la aplicación
		NULL);//puntero a los datos de creación de la ventana

	ShowWindow(hwndVentana, nCmdShow);//Muestra la ventana creada

	
	ShowWindow(hInfo, SW_SHOW);
	
	glewInit();//Inicializa glew

	//Instancia de la escena
	//scene = new Scene(hwndVentana);
	Scene = new SceneGAMEPAD(hwndVentana);

	gamPad = new GamePadRR(1);
	ableToCheck = true;

	//Crear un timer con el valor especificado de time-out
	SetTimer(hwndVentana,//Manejador de ventana que recibirá los mensajes del timer
		Timer1,//identificador del timer
		30,//valor de time-out
		NULL);//dirección del procedimiento de timer

	MSG msg = { 0 };

#ifdef SceneGAMEPADMiModificacion

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			if (renderiza)
			{
				//scene->render(hContextoVentana);
				//renderiza = false;
				if (gamPad->IsConnected())
				{
					float grados = (float)gamPad->GetState().Gamepad.sThumbLX / 32767.0;
					//debido a que los controles se aguadean con el uso entonces ya no dan el cero
					//en el centro, por eso lo comparo con una ventana de aguadencia de mi control
					if (grados>0.19 || grados <-0.19)
						Scene->CamaraGiraY(grados*3.0);


					velocidad = (float)gamPad->GetState().Gamepad.sThumbLY / 32767.0;
					velocidad = velocidad * 2.5;
					if (velocidad>0.19 || velocidad <-0.19)
						Scene->CamaraAvanza(velocidad);

					grados = (float)gamPad->GetState().Gamepad.sThumbRX / 32767.0;
					grados = grados / 2;
					if (grados>0.19 || grados <-0.19)
						Scene->CamaraGiraY(grados*3.0);

					grados = (float)gamPad->GetState().Gamepad.sThumbRY / 32767.0;
					if (grados>0.19 || grados <-0.19)
						Scene->CamaraGiraX(grados*5.0);


					//switch (gamPad->GetState) {
					//case XINPUT_GAMEPAD_DPAD_UP: //INFORMACION COORDENADAS POSICION GAMEPAD
					//{
					//	string info = "X: " + to_string(OGLobj->posc.X) + " Y: " + to_string(OGLobj->posc.Y) + " Z: " + to_string(OGLobj->posc.Z);
					//	//MessageBox(hWnd, info.c_str(), "Informacion posicion", MB_OK);
					//	break;
					//}
					//case XINPUT_GAMEPAD_DPAD_LEFT: //INFORMACION COORDENADAS DIRECCION GAMEPAD{
					//{
					//	string info = "X: " + to_string(OGLobj->dirc.X) + " Y: " + to_string(OGLobj->dirc.Y) + " Z: " + to_string(OGLobj->dirc.Z);
					//	//MessageBox(hWnd, info.c_str(), "Informacion direccion", MB_OK);
					//	break;
					//}


				}
				else
				{
					//aqui ponemos un messgaebox para decir que se perdio la conexion con el gamepad
					//MessageBox(hWnd, L"Conecte el GamePad por favor", L"Mando 1 Desconectado", MB_OK | MB_ICONEXCLAMATION);
				}

				Scene->render(hContextoVentana, hwndVentana);
				renderiza = false;


			}
		}
	}
#endif

	return msg.wParam;

}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HGLRC hContextoGL;
	static HDC hContextoAux;
	int ancho, alto;
	char epx[6] = "";
	char epz[6] = "";
	char epy[6] = "";
	char edx[6] = "";
	char edz[6] = "";
	char edy[6] = "";
	char ec[80] = "";

	switch (message)
	{
	case WM_CREATE: {
		hContextoAux = GetDC(hWnd);
		hContextoVentana = hContextoAux;
		DefPixelFormat(hContextoVentana);
		hContextoGL = wglCreateContext(hContextoVentana);
		wglMakeCurrent(hContextoVentana, hContextoGL);
		srand(time(NULL));
		break; }
	case WM_KEYDOWN: {
#ifdef SceneGAMEPADMiModificacion
		switch (wParam)
		{
		case VK_F1: //INFORMACION COORDENADAS POSICION KEYBOARD
		{
			/*string info = "X: " + to_string(scene->px) + " Y: " + to_string(scene->py)+ " Z: " +to_string(scene->pz);
			MessageBox(hWnd,info.c_str(),"INFO",MB_OK);*/

			string info = "X: " + to_string(Scene->posc.X) + " Y: " + to_string(Scene->posc.Y) + " Z: " + to_string(Scene->posc.Z);
			MessageBox(hWnd, info.c_str(), "Informacion posicion", MB_OK);
			break;
		}
		case VK_F2: //INFORMACION COORDENADAS DIRECCION KEYBOARD
		{
			string info = "X: " + to_string(Scene->dirc.X) + " Y: " + to_string(Scene->dirc.Y) + " Z: " + to_string(Scene->dirc.Z);
			MessageBox(hWnd, info.c_str(), "Informacion direccion", MB_OK);
			break;
		}

		//CAMARA DEL GAMEPAD
		case 0x44: //D
		{
			Scene->CamaraGiraY(1 * 3.0);
			break;
		}
		case 0x41: //A
		{
			Scene->CamaraGiraY((-1) * 3.0);
			break;
		}
		case 0x57: //W
		{
			Scene->CamaraAvanza(2);
			break;
		}
		case 0x53: //S
		{
			Scene->CamaraAvanza(-2);
			break;
		}
		case VK_UP: // FLECHA ARRIBA
		{
			Scene->CamaraGiraX(1 * 4);
			break; }
		case VK_DOWN: // FLECHA ABAJO
		{
			Scene->CamaraGiraX((-1) * 4);
			break; }
		}
#endif
		break; }
	case WM_TIMER: 	{

#ifdef CambioLUZ02
		//Contador suma en uno cada vez que pasa se ejecuta el TIMER
		contador++;
		//Condicion del timer
		
		if (contador <= 500)
		{
		Scene->horadeldia = dia;
		Scene->clima = nonevar;
		if (Scene->Luz < 0.5)
		{
		Scene->Luz += 0.001;
		}
		}
		else if (contador > 500 && contador <= 1000) {

		Scene->horadeldia = mediodia;
		Scene->clima = nonevar;
		if (Scene->Luz < 1.0)
		{
		Scene->Luz += 0.001;
		}
		}
		else if (contador > 1000 && contador <= 1500) {

		Scene->horadeldia = atardecer;
		Scene->clima = nevara;
		if (Scene->Luz > 0.5)
		{
		Scene->Luz -= 0.001;
		}
		}
		else if (contador > 1500 && contador <= 2000) {

		Scene->horadeldia = noche;
		Scene->clima = nevara;
		if (Scene->Luz > 0.0)
		{
		Scene->Luz -= 0.001;
		}


		}
		else if (contador > 1500 && contador <= 2000) {

		Scene->horadeldia = medianoche;
		Scene->clima = nevara;
		if (Scene->Luz < 0.5)
		{
		Scene->Luz += 0.001;
		}

		}
		else if (contador > 1500 && contador <= 2000) {

		Scene->horadeldia = madrugada;
		Scene->clima = nonevar;
		if (Scene->Luz > 0.5)
		{
		Scene->Luz -= 0.001;
		}

		}
		else {
		contador = 0;
		}
#endif
		renderiza = true;	
		break; }
	case WM_DESTROY: {
		KillTimer(hWnd, Timer1);
		delete Scene;
		wglMakeCurrent(hContextoVentana, NULL);
		wglDeleteContext(hContextoGL);
		PostQuitMessage(0);
		return 0;
		break;
	}
	case WM_SIZE:	{
		alto = HIWORD(lParam);
		ancho = LOWORD(lParam);
		if (alto == 0)
			alto = 1;
		glViewport(0, 0, ancho, alto);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)ancho / (GLfloat)alto, 1.0f, 10000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		break;
	}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void DefPixelFormat(HDC hDC)
{
	int bestmatch;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), //tamaño de la estructura
		1, //numero de version
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //soporta la ventana, el opengl y manejara doble buffer
		PFD_TYPE_RGBA, //formato de 32 bits rgba
		32, //tamaño del color en 32 bits
		0, 0, 0, 0, 0, 0, //bits de color, no se usan
		0, //no hay buffer para el alfa
		0, //ignore el bit de corrimiento
		0, //no hay buffer de acumulacion
		0, 0, 0, 0, //no hay bits de acumulacion
		16, //tamaño del flotante para el buffer z
		0, //no hay buffers de stencil
		0, //no hay buffers auxiliares
		PFD_MAIN_PLANE, //plano principal para dibujo
		0, //reservado
		0, 0, 0 //mascaras de capas ignoradas
	};

	bestmatch = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, bestmatch, &pfd);
}
