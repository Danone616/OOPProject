#ifndef ASTEROID_H
#define ASTEROID_H

#include <glad/glad.h>
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "Sphere.h"

class Asteroid
{
public:
	VAO* vao;
	GLuint verticesSize;
	GLuint indicesSize;
	int colorType;
	int drawType;
	void Draw();
	Asteroid(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint precision, int colortype, int drawtype);
};

#endif