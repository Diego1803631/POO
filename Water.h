#pragma once
#include "Images.h"
#include <gl/GL.h>
#include <gl/GLU.h>
class Water: public Images
{
	unsigned int _texture;
public:
	Water(WCHAR* texturePath);
	~Water(void);

	void Draw();
	void Update();
};

