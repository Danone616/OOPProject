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
	VAO* vao;
	GLuint verticesSize;
	GLuint indicesSize;
	int colorType;
	int drawType;
	Sphere(GLfloat radius, GLint precision,int colortype,int drawtype);
	static SphereStruct CreateSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat r, int depth);
	void Draw();
};

#endif
