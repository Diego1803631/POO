#include "Water.h"
Water::Water(WCHAR* texturePath)
{
	Load(texturePath);
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, GetWidth(), GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, GetPath());
	Unload();
}


Water::~Water(void)
{
	glDeleteTextures(1, &_texture);
}

void Water::Draw()
{
	glPushAttrib(GL_CURRENT_BIT | GL_TEXTURE_BIT);
	glBindTexture(GL_TEXTURE_2D, _texture);

	// U V
	static float water_factor_min = 0.0f;
	static float water_factor_max = 20.0f;
	static float water_size = 30;
	static double modifier = 0;
	// water_factor_min += 1;
	modifier += .1;
	water_factor_max += sin(modifier);

	glBegin(GL_QUADS);
	glTexCoord2f(water_factor_min, water_factor_min);
	glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
	glVertex3f(-water_size, 0.0f, water_size);

	glTexCoord2f(water_factor_max, water_factor_min);
	glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
	glVertex3f(water_size, 0.0f, water_size);

	glTexCoord2f(water_factor_max, water_factor_max);
	glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
	glVertex3f(water_size, 0.0f, -water_size);

	glTexCoord2f(water_factor_min, water_factor_max);
	glColor4f(0.1f, 0.3f, 0.6f, 0.2f);
	glVertex3f(-water_size, 0.0f, -water_size);
	glEnd();
	glPopAttrib();
}