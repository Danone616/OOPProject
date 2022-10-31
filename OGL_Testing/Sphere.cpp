#include "Sphere.h"

Sphere::Sphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius,GLint precision)
{

	SphereStruct sphere = CreateSphere(x, y, z, radius, precision);

	verticesSize = 2 * sphere.points.size();
	indicesSize = sphere.triangles.size();
	vertices = new GLfloat[verticesSize];
	indices = new GLuint[indicesSize];
	

	for (int i = 0; i < sphere.points.size(); i += 3)
	{
		//position
		vertices[i * 2] = sphere.points[i];
		vertices[i * 2 + 1] = sphere.points[i + 1];
		vertices[i * 2 + 2] = sphere.points[i + 2];
		//color
		vertices[i * 2 + 3] = sphere.points[i];
		vertices[i * 2 + 4] = sphere.points[i + 1];
		vertices[i * 2 + 5] = sphere.points[i + 2];
	}


	for (int i = 0; i < sphere.triangles.size(); i += 3)
	{
		indices[i] = sphere.triangles[i];
		indices[i + 1] = sphere.triangles[i + 1];
		indices[i + 2] = sphere.triangles[i + 2];
	}
	vao = new VAO();
	vao->Bind();
	vbo = new VBO(vertices, sizeof(vertices));
	ebo = new EBO(indices, sizeof(indices));
	vao->Link(*vbo, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	vao->Link(*vbo, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));

	vao->Unbind();
	vbo->Unbind();
	ebo->Unbind();
};

Sphere::SphereStruct Sphere::CreateSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat r, int depth)
{
	if (depth == 1)
	{
		std::vector<GLfloat> points =
		{
			x + r,0.0f,0.0f,
			x - r,0.0f,0.0f,
			0.0f,y + r,0.0f,
			0.0f,y - r,0.0f,
			0.0f,0.0f,z + r,
			0.0f,0.0f,z - r
		};
		std::vector<GLint> triangles =
		{
			0, 2, 4,
			0, 2, 5,
			0, 3, 4,
			0, 3, 5,
			1, 2, 4,
			1, 2, 5,
			1, 3, 4,
			1, 3, 5
		};
		return { points,triangles };
	}
	SphereStruct sphere = CreateSphere(x, y, z, r, depth - 1);

	std::vector<GLint> triangles = sphere.triangles;
	std::vector<GLfloat> points = sphere.points;
	std::vector<GLint> trianglesnew;

	for (int i = 0; i < triangles.size(); i += 3)
	{
		GLfloat newx1 = (points[triangles[i] * 3] + points[triangles[i + 1] * 3]) / 2;
		GLfloat newy1 = (points[triangles[i] * 3 + 1] + points[triangles[i + 1] * 3 + 1]) / 2;
		GLfloat newz1 = (points[triangles[i] * 3 + 2] + points[triangles[i + 1] * 3 + 2]) / 2;

		GLfloat newx2 = (points[triangles[i + 2] * 3] + points[triangles[i + 1] * 3]) / 2;
		GLfloat newy2 = (points[triangles[i + 2] * 3 + 1] + points[triangles[i + 1] * 3 + 1]) / 2;
		GLfloat newz2 = (points[triangles[i + 2] * 3 + 2] + points[triangles[i + 1] * 3 + 2]) / 2;

		GLfloat newx3 = (points[triangles[i] * 3] + points[triangles[i + 2] * 3]) / 2;
		GLfloat newy3 = (points[triangles[i] * 3 + 1] + points[triangles[i + 2] * 3 + 1]) / 2;
		GLfloat newz3 = (points[triangles[i] * 3 + 2] + points[triangles[i + 2] * 3 + 2]) / 2;

		GLfloat dist1 = sqrt((newx1 - x) * (newx1 - x) + (newy1 - y) * (newy1 - y) + (newz1 - z) * (newz1 - z));
		newx1 *= r / dist1;
		newy1 *= r / dist1;
		newz1 *= r / dist1;
		GLfloat dist2 = sqrt((newx2 - x) * (newx2 - x) + (newy2 - y) * (newy2 - y) + (newz2 - z) * (newz2 - z));
		newx2 *= r / dist2;
		newy2 *= r / dist2;
		newz2 *= r / dist2;
		GLfloat dist3 = sqrt((newx3 - x) * (newx3 - x) + (newy3 - y) * (newy3 - y) + (newz3 - z) * (newz3 - z));
		newx3 *= r / dist3;
		newy3 *= r / dist3;
		newz3 *= r / dist3;

		sphere.points.push_back(newx1);
		sphere.points.push_back(newy1);
		sphere.points.push_back(newz1);

		sphere.points.push_back(newx2);
		sphere.points.push_back(newy2);
		sphere.points.push_back(newz2);

		sphere.points.push_back(newx3);
		sphere.points.push_back(newy3);
		sphere.points.push_back(newz3);


		trianglesnew.push_back(triangles[i]);
		trianglesnew.push_back(sphere.points.size() / 3 - 3);
		trianglesnew.push_back(sphere.points.size() / 3 - 1);

		trianglesnew.push_back(triangles[i + 1]);
		trianglesnew.push_back(sphere.points.size() / 3 - 3);
		trianglesnew.push_back(sphere.points.size() / 3 - 2);

		trianglesnew.push_back(triangles[i + 2]);
		trianglesnew.push_back(sphere.points.size() / 3 - 1);
		trianglesnew.push_back(sphere.points.size() / 3 - 2);

		trianglesnew.push_back(sphere.points.size() / 3 - 1);
		trianglesnew.push_back(sphere.points.size() / 3 - 2);
		trianglesnew.push_back(sphere.points.size() / 3 - 3);
	}

	sphere.triangles = trianglesnew;

	return sphere;
}

void Sphere::DrawSphere()
{
	vao->Bind();
	glDrawElements(GL_TRIANGLES,indicesSize*3, GL_UNSIGNED_INT, 0);
}
//todo
/*
transfer sphere to the class(make it with VBOs and shit)(For simplicity make sphere and separate sphere with gl compatibitity)
make an asteroid class(same shit, gl compatible)
remove magic numbers from perlin noise generation
make the main loop framerate capped(FPS variable dependent, no magic numbers)
introduce camera class(kill me)
*/

Tile_plain::Tile_plain(double xPos, double yPos, double xSize, double ySize) {
	xpos = xPos;
	ypos = yPos;
	xsize = xSize;
	ysize = ySize;
	//bt-lt
	vertices[0] = xPos;
	vertices[1] = yPos;
	vertices[2] = 0;

	vertices[3] = 0;
	vertices[4] = 0;
	vertices[5] = 0;
	//tp-lt
	vertices[6] = xPos;
	vertices[7] = yPos + ySize;
	vertices[8] = 0;

	vertices[9] = 0;
	vertices[10] = 0;
	vertices[11] = 0;
	//bt-rt
	vertices[12] = xPos + xSize;
	vertices[13] = yPos;
	vertices[14] = 0;

	vertices[15] = 0;
	vertices[16] = 0;
	vertices[17] = 0;
	//tp-rt
	vertices[18] = xPos + xSize;
	vertices[19] = yPos + ySize;
	vertices[20] = 0;

	vertices[21] = 0;
	vertices[22] = 0;
	vertices[23] = 0;


	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;

	TileVAO = new VAO();
	TileVAO->Bind();

	TileVBO = new VBO(vertices, sizeof(GLfloat) * 24);

	TileEBO = new EBO(indices, sizeof(GLuint) * 6);


	TileVAO->Link(*TileVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	TileVAO->Link(*TileVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	TileVAO->Unbind();
	TileEBO->Unbind();
	TileVBO->Unbind();
}

Tile_plain::Tile_plain()
{
}


void Tile_plain::draw()
{
	TileVAO->Bind();




	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Tile_plain::setColor(float red, float green, float blue)
{
	vertices[3] = red;
	vertices[4] = green;
	vertices[5] = blue;

	vertices[9] = red;
	vertices[10] = green;
	vertices[11] = blue;

	vertices[15] = red;
	vertices[16] = green;
	vertices[17] = blue;

	vertices[21] = red;
	vertices[22] = green;
	vertices[23] = blue;

	TileVAO->Delete();
	TileVBO->Delete();
	delete TileVAO;
	delete TileVBO;
	TileVAO = new VAO();
	TileVAO->Bind();
	TileEBO->Bind();

	TileVBO = new VBO(vertices, sizeof(GLfloat) * 24);

	TileVAO->Link(*TileVBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	TileVAO->Link(*TileVBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	TileVAO->Unbind();
	TileEBO->Unbind();
	TileVBO->Unbind();
}

float Tile_plain::getRed()
{
	return vertices[3];
}

float Tile_plain::getGreen()
{
	return vertices[4];
}

float Tile_plain::getBlue()
{
	return vertices[5];
}