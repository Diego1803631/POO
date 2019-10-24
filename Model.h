#pragma once
#include <windows.h>
#include "glm.h"
#include "Images.h"
#include "Primitive.h"
#include <gl/GL.h>
#include <gl/GLU.h>
class Model: public Images
{
private: 
	float _width{ 0 };
	float _depth{ 0 };
	float _deltaX{ 0 };
	float _deltaZ{ 0 };
	GLMmodel* _model;
	unsigned int _texture;
public:
	Model(char* path);
	Model(char* path, WCHAR texture[]);
	~Model();

	void Draw();
};

