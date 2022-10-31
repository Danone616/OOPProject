#ifndef SPHERE_H
#define SPHERE_H

#include <glad/glad.h>
#include<vector>
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


class Sphere
{
public:
	struct SphereStruct
	{
		std::vector<GLfloat> points;//vertices
		std::vector<GLint> triangles;//indices
	};
	GLfloat* vertices;
	GLuint* indices;
	VBO* vbo;
	EBO* ebo;
	VAO* vao;
	Sphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint precision);
	static SphereStruct CreateSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat r, int depth);
	void DrawSphere();
	
	GLuint verticesSize;
	GLuint indicesSize;
};

#endif
