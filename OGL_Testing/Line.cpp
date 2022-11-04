#include "Line.h"

Line::Line(GLfloat x, GLfloat y, GLfloat z, GLfloat xa, GLfloat ya, GLfloat za, GLfloat r, GLfloat g, GLfloat b)
{
	GLfloat data[12] = {
		x,
		y,
		z,
		r,
		g,
		b,
		xa,
		ya,
		za,
		r,
		g,
		b
	};
	vao.Bind();
	VBO vbo(data,sizeof(data));
	vao.Link(vbo, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	vao.Link(vbo, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	vao.Unbind();
	vbo.Delete();
}

void Line::Draw()
{
	vao.Bind();
	glDrawArrays(GL_LINES, 0, 2);
}
