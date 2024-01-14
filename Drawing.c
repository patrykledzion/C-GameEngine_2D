#include "Drawing.h"

void DrawRectangle(long x, long y, long w, long h, Color4_t* color, long depth, Window* window)
{

	glColor4f(color->r, color->g, color->b, color->a);
	glBegin(GL_QUADS);
	glVertex3f(x, y, depth);
	glVertex3f(x + w, y, depth);
	glVertex3f(x + w, y + h, depth);
	glVertex3f(x, y + h, depth);
	glEnd();
}
