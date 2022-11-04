#ifndef LINE_H
#define LINE_H

#include <glad/glad.h>
#include<vector>
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "Shaders.h"

class Line
{
public:
	VAO vao;
	Line(GLfloat x, GLfloat y, GLfloat z, GLfloat xa, GLfloat ya, GLfloat za, GLfloat r, GLfloat g, GLfloat b);
	Line() {};
	void Draw();
};

#endif
