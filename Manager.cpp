#include "Manager.h"

Manager::Manager(HWND hWnd)
{
	triangle = new Triangle();
	box = new Box(.5);
	sky = new SkyDome(hWnd, 32, 32, 500, L"assets/terrain/earth.jpg");
	terrain = new Terrain(hWnd, L"assets/terrain/terreno.jpg", L"assets/terrain/desert.jpg", 1000, 1000);
	camera = new Camera();
	gamepad = new GamePad(1);
	tank = new Model("assets/models/robot.obj",L"assets/models/robot_skin.jpg");
	thing = new Model("assets/models/Chickie.obj", L"assets/models/Image09660880_0965E7B0.png");
	castle = new Model("assets/models/castillito3.obj",L"hyruSS32.png");
	tree = new Billboard(hWnd, L"assets/billboards/Arbol.png", 6, 6, position);
	water = new Water(L"assets/water/water_2.bmp");
	Log::log("Finish Loading");
}
Manager::~Manager()
{
	if (triangle)
		delete triangle;
	if (box)
		delete box;
	if (terrain)
		delete terrain;
	if (camera)
		delete camera;
	if (gamepad)
		delete gamepad;
	if (tank)
		delete tank;
	if (castle)
		delete castle;
	if (thing)
		delete thing;
	if (tree)
		delete tree;
	if (sky)
		delete sky;
}
void Manager::Render(HDC hDC)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.6, 0.6, 0.6, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//Para usar el control:
	VerifyGamepad();
	camera->MoveForward(lY);
	camera->StrafeRight(lX);
	//Para usar el teclado:
	camera->MoveForward(position.y);
	camera->StrafeRight(position.x);
	//Giro con control:
	camera->RotateX(rY);
	camera->RotateY(-rX);
	camera->SetAltitudPosition(terrain->Surface(camera->GetPosition().x, camera->GetPosition().z)+1.7);
	camera->Update();
	//skydome
	glPushMatrix();
	glTranslatef(0, 8, 0);
	sky->Draw();
	glPopMatrix();
	//terreno
	glPushMatrix();
	terrain->Draw();
	glPopMatrix();
	//castillo
	glPushMatrix();
	glTranslated(0, 20, -60);
	glScaled(20, 20, 20);
	castle->Draw();
	glPopMatrix();
	//mono
	glPushMatrix();
	glTranslated(0, 11, -10);
	thing->Draw();
	glPopMatrix();

	/*tank->Draw();*/
	/*water->Draw();*/
	/*tree->Draw(camera->GetPosition());*/
	
	/*if (aPress) {
		terrain->Draw();
	}
	*/

	SwapBuffers(hDC);
}

void Manager::VerifyGamepad()
{
	if (gamepad->IsConnected()) {
		lX = gamepad->GetState().Gamepad.sThumbLX / 32767;
		lY = gamepad->GetState().Gamepad.sThumbLY / 32767;
		rX = gamepad->GetState().Gamepad.sThumbRX / 32767;
		rY = gamepad->GetState().Gamepad.sThumbRY / 32767;

		if ((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0) {
			aPress = !aPress;
			gamepad->Vibrate(32767, 32767);
		}
		else {
			gamepad->Vibrate(0, 0);
		}
	}
}

