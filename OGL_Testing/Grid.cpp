#include "Grid.h"
Grid::Grid(int num, int space)
{
	//         data/line // line quantity 
	datasize = 12 * ((num + 1) * (num + 1) * 3 + 3);
	GLfloat* data = new GLfloat[datasize];

	data[0] = -50000.0f; data[1] = 0.0f; data[2] = 0.0f;
	data[3] = 1.0f; data[4] = 1.0f; data[5] = 1.0f;
	data[6] = 50000.0f; data[7] = 0.0f; data[8] = 0.0f;
	data[9] = 1.0f; data[10] = 1.0f; data[11] = 1.0f;

	data[12] = 0.0f; data[13] = -50000.0f; data[14] = 0.0f;
	data[15] = 1.0f; data[16] = 1.0f; data[17] = 1.0f;
	data[18] = 0.0f; data[19] = 50000.0f; data[20] = 0.0f;
	data[21] = 1.0f; data[22] = 1.0f; data[23] = 1.0f;

	data[24] = 0.0f; data[25] = 0.0f; data[26] = -50000.0f;
	data[27] = 1.0f; data[28] = 1.0f; data[29] = 1.0f;
	data[30] = 0.0f; data[31] = 0.0f; data[32] = 50000.0f;
	data[33] = 1.0f; data[34] = 1.0f; data[35] = 1.0f;
	if (num != 0)
	{
		int i = 3;
		for (int shift1 = -num / 2; shift1 <= num / 2; shift1++)
		{
			for (int shift2 = -num / 2; shift2 <= num / 2; shift2++)
			{
				if (shift2 == 0 && shift1 == 0)shift2++;
				data[i * 12] = -50000.0f; data[i * 12 + 1] = shift1 * space; data[i * 12 + 2] = shift2 * space;
				data[i * 12 + 3] = 0.5f; data[i * 12 + 4] = 0.5f; data[i * 12 + 5] = 0.5f;
				data[i * 12 + 6] = 50000.0f; data[i * 12 + 7] = shift1 * space; data[i * 12 + 8] = shift2 * space;
				data[i * 12 + 9] = 0.5f; data[i * 12 + 10] = 0.5f; data[i * 12 + 11] = 0.5f;
				i++;
			}
		}
		for (int shift1 = -num / 2; shift1 <= num / 2; shift1++)
		{
			for (int shift2 = -num / 2; shift2 <= num / 2; shift2++)
			{
				if (shift2 == 0&& shift1 == 0)shift2++;
				data[i * 12] = shift1 * space; data[i * 12 + 1] = -50000.0f; data[i * 12 + 2] = shift2 * space;
				data[i * 12 + 3] = 0.5f; data[i * 12 + 4] = 0.5f; data[i * 12 + 5] = 0.5f;
				data[i * 12 + 6] = shift1 * space; data[i * 12 + 7] = 50000.0f; data[i * 12 + 8] = shift2 * space;
				data[i * 12 + 9] = 0.5f; data[i * 12 + 10] = 0.5f; data[i * 12 + 11] = 0.5f;
				i++;
			}
		}
		for (int shift1 = -num / 2; shift1 <= num / 2; shift1++)
		{
			for (int shift2 = -num / 2; shift2 <= num / 2; shift2++)
			{
				if (shift2 == 0 && shift1 == 0)shift2++;
				data[i * 12] = shift2 * space; data[i * 12 + 1] = shift1 * space; data[i * 12 + 2] = -50000.0f;
				data[i * 12 + 3] = 0.5f; data[i * 12 + 4] = 0.5f; data[i * 12 + 5] = 0.5f;
				data[i * 12 + 6] = shift2 * space; data[i * 12 + 7] = shift1 * space; data[i * 12 + 8] = 50000.0f;
				data[i * 12 + 9] = 0.5f; data[i * 12 + 10] = 0.5f; data[i * 12 + 11] = 0.5f;
				i++;
			}
		}
	}
	vao.Bind();
	VBO vbo(data, datasize * sizeof(GLfloat));
	vao.Link(vbo, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	vao.Link(vbo, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	vao.Unbind();
	vbo.Delete();
}

void Grid::Draw()
{
	vao.Bind();
	glDrawArrays(GL_LINES, 0, datasize);
}
