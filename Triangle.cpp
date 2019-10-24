#include "GL/glut.h"
#include "Triangle.h"

void Triangle::Draw()
{
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_COLOR_MATERIAL);
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex3f(-0.5, 0, -1);
	glColor3f(0.5, 0.5, 0);
	glVertex3f(0.5, 0, -1);
	glColor3f(0, 0.5, 0.5);
	glVertex3f(0, 0.5, -1);
	glEnd();
	glPopAttrib();
	glPopMatrix();
}
