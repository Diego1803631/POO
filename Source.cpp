#include <iostream>
#include <windows.h>
#include <windowsx.h>
#include "Manager.h"
#include <stdio.h>
#include "Console.h"
using namespace std;
#define Timer1 100

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void SetUpPixelFormat(HDC hDC);
HDC gHDC;

Manager* manager;

bool renderiza = false;
float giro = 0;

int APIENTRY  WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _LOG
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	cout << "START CONSOLE" << std::endl;
#endif
	HWND hWnd;

	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "EjemploLMAD";
	RegisterClassEx(&wc);
	RECT wr = { 0, 0, 800, 600 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(NULL,
		"EjemploLMAD",
		"Programa de win32 tutorial",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);

	OutputDebugString("Inicializado.\n");


	//Creamos al objeto y se lo pasamos al puntero
	manager = new Manager(hWnd);

	SetTimer(hWnd, Timer1, 30, NULL);

	MSG msg = { 0 };
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
			//en este lazo estara ejecutandose el render
			//"renderiza" controla si se hace el render o no a traves
			//del timer Timer1
			if (renderiza)
			{
				manager->Render(gHDC);
				renderiza = false;
			}
		}
	}

	return msg.wParam;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HGLRC hRC;
	static HDC hDC;
	int ancho, alto;

	switch (message)
	{
		//este case se ejecuta cuando se crea la ventana, aqui asociamos al 
		//opengl con el dispositivo
	case WM_CREATE:
		hDC = GetDC(hWnd);
		gHDC = hDC;
		SetUpPixelFormat(hDC);
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);
		break;

	case WM_TIMER:
		renderiza = true;
		break;
	case WM_DESTROY:
	{
		KillTimer(hWnd, Timer1);
		//en caso de salir desocupar los recursos del opengl
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);
		PostQuitMessage(0);
		return 0;
	} break;

	case WM_SIZE:
	{
		//esta opcion del switch se ejecuta una sola vez al arrancar y si se
		//afecta el tamaño de la misma se dispara de nuevo
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
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 'W':
			cout << "UP" << endl;
			manager->position.y = 1;
			break;
		case 'S':
			cout << "DOWN" << endl;
			manager->position.y = -1;
			break;
		case 'D':
			cout << "RIGHT" << endl;
			manager->position.x = 1;
			break;
		case 'A':
			cout << "LEFT" << endl;
			manager->position.x = -1;
			break;
		default:
			break;
		}
	}break;
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case 'W':
			cout << "RELEASE UP" << endl;
			manager->position.y = 0;
			break;
		case 'S':
			cout << "RELEASE DOWN" << endl;
			manager->position.y = 0;
			break;
		case 'D':
			cout << "RELEASE RIGHT" << endl;
			manager->position.x = 0;
			break;
		case 'A':
			cout << "RELEASE LEFT" << endl;
			manager->position.x = 0;
			break;
		default:
			break;
		}
	}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void SetUpPixelFormat(HDC hDC)
{
	int PixForm;

	static PIXELFORMATDESCRIPTOR pixfordes = {
		sizeof(PIXELFORMATDESCRIPTOR), //tamaño de la estructura
		1, //numero de version
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //soporta la ventana, el opengl y manejara doble buffer
		PFD_TYPE_RGBA, //formato de 32 bits rgba
		32, //tamaño del color en 32 bits
		0,0,0,0,0,0, //bits de color, no se usan
		0, //no hay buffer para el alfa
		0, //ignore el bit de corrimiento
		0, //no hay buffer de acumulacion
		0,0,0,0, //no hay bits de acumulacion
		16, //tamaño del flotante para el buffer z
		0, //no hay buffers de stencil
		0, //no hay buffers auxiliares
		PFD_MAIN_PLANE, //plano principal para dibujo
		0, //reservado
		0,0,0 //mascaras de capas ignoradas
	};

	PixForm = ChoosePixelFormat(hDC, &pixfordes);
	SetPixelFormat(hDC, PixForm, &pixfordes);
}