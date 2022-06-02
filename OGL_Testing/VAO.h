#ifndef VAO_H
#define VAO_H

#include<glad/glad.h>
#include "VBO.h"

class VAO
{
	public:
		GLuint ID;
		VAO();

		void Link(VBO VBO,GLuint layout, GLuint numComponents, GLuint type, GLuint stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();
};

#endif