#include "Asteroid.h"
#include "PerlinNoise3D.h"

Asteroid::Asteroid(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint precision, int colortype, int drawtype)
{
	colorType = colortype;
	drawType = drawtype;
	Sphere::SphereStruct sphere = Sphere::CreateSphere(x, y, z, radius, precision);

	verticesSize = 2 * sphere.points.size();
	if (drawType == 0)indicesSize = sphere.triangles.size();
	else if (drawType == 1)indicesSize = 2 * sphere.triangles.size();
	GLfloat * vertices = new GLfloat[verticesSize];
	GLuint * indices = new GLuint[indicesSize];
	VBO * vbo;
	EBO * ebo;
	PerlinNoise3D noise(0, 6);
	GLfloat radiuschangestrength = 1;
	for (int i = 0; i < sphere.points.size(); i += 3)
	{

		GLfloat noisevalue = noise.Calculate((sphere.points[i]-x) / radius, (sphere.points[i + 1] - y)/radius, (sphere.points[i + 2] - z))/radius;
		GLfloat radiuschange = 1 + (2 * radiuschangestrength * noisevalue - radiuschangestrength);

		//position
		vertices[i * 2] = sphere.points[i] * radiuschange;
		vertices[i * 2 + 1] = sphere.points[i + 1] * radiuschange;
		vertices[i * 2 + 2] = sphere.points[i + 2] * radiuschange;

		//color
		if (colorType == 0)
		{
			vertices[i * 2 + 3] = 1.0f;
			vertices[i * 2 + 4] = 1.0f;
			vertices[i * 2 + 5] = 1.0f;
		}
		if (colorType == 1)
		{
			vertices[i * 2 + 3] = (sphere.points[i] - x) / radius;
			vertices[i * 2 + 4] = (sphere.points[i + 1] - y) / radius;
			vertices[i * 2 + 5] = (sphere.points[i + 2] - z) / radius;
		}

	}
	if (drawType == 0)for (int i = 0; i < sphere.triangles.size(); i += 3)
	{
		indices[i] = sphere.triangles[i];
		indices[i + 1] = sphere.triangles[i + 1];
		indices[i + 2] = sphere.triangles[i + 2];
	}
	else if (drawType == 1)for (int i = 0; i < sphere.triangles.size(); i += 3)
	{
		indices[i * 2] = sphere.triangles[i];
		indices[i * 2 + 1] = sphere.triangles[i + 1];
		indices[i * 2 + 2] = sphere.triangles[i];
		indices[i * 2 + 3] = sphere.triangles[i + 2];
		indices[i * 2 + 4] = sphere.triangles[i + 1];
		indices[i * 2 + 5] = sphere.triangles[i + 2];
	}
	vao = new VAO();
	vao->Bind();
	vbo = new VBO(vertices, verticesSize * sizeof(GLfloat));
	ebo = new EBO(indices, indicesSize * sizeof(GLuint));
	vbo->Bind();
	ebo->Bind();
	vao->Link(*vbo, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	vao->Link(*vbo, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	vao->Unbind();
	vbo->Delete();
	ebo->Delete();
};

void Asteroid::Draw()
{
	vao->Bind();
	if (drawType == 0)glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
	else if (drawType == 1)glDrawElements(GL_LINES, indicesSize, GL_UNSIGNED_INT, 0);
}
