#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#include <glad/glad.h>
#include<vector>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "Shaders.h"

class GraphicsObject
{
public:
	
	VAO* vao;
	void Draw(Shader& shader);
};

#endif
