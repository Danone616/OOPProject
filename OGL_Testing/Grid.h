#ifndef GRID_H
#define GRID_H

#include <glad/glad.h>
#include<vector>
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "Shaders.h"

class Grid
{
public:
	VAO vao;
	int datasize;
	Grid(int num,int space);
	Grid() {};
	void Draw();
};

#endif
