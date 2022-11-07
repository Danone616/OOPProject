#ifndef SPHERE_H
#define SPHERE_H

#include <glad/glad.h>
#include<vector>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "Shaders.h"
#include "GraphicsObject.h"

class Sphere : GraphicsObject
{
public:
	struct SphereStruct
	{
		std::vector<GLfloat> points;//vertices
		std::vector<GLint> triangles;//indices
		~SphereStruct()
		{
			points.~vector();
			triangles.~vector();
		}
	};
	VAO* vao;
	GLuint verticesSize;
	GLuint indicesSize;
	glm::vec3 position = glm::vec3(1.0f,1.0f,1.0f);
	glm::mat4 orientation = glm::mat4(1.0f);
	int colorType;
	int drawType;
	Sphere(GLfloat radius, GLint precision, int colortype, int drawtype);
	static SphereStruct CreateSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat r, int depth);
	void ChangePosition(glm::vec3 shift, GLfloat deg, glm::vec3 axis);
	void Draw(Shader& shader);
};

#endif
