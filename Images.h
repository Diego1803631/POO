#pragma once
#include <windows.h>
#include <gdiplus.h>
#include <exception>
#include <gl/gl.h>
#include <gl/glu.h>
class Images
{
private:
	unsigned char* _path;
	unsigned char* _first;
	unsigned int _height;
	unsigned int _width;
public:

	HWND hWnd;

	Images();
	~Images();

	void Load(WCHAR name[]);
	void Unload();

	unsigned char* GetPath();
	unsigned int GetWidth();
	unsigned int GetHeight();
	
};

