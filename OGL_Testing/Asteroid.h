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
	glm::mat4 position = glm::mat4(1.0f);
	int colorType;
	int drawType;
	void Draw();
	Asteroid(GLfloat radius, GLint precision, int colortype, int drawtype);
};

#endif