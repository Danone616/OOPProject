#include "Asteroid.h"
#include "PerlinNoise3D.h"

#include<iostream>

Asteroid::Asteroid(GLfloat radius, GLint precision, int colortype, int drawtype)
{
	colorType = colortype;
	drawType = drawtype;
	Sphere::SphereStruct sphere = Sphere::CreateSphere(0, 0, 0, radius, precision);

	verticesSize = 2 * sphere.points.size();
	if (drawType == 0)indicesSize = sphere.triangles.size();
	else if (drawType == 1)indicesSize = 2 * sphere.triangles.size();
	GLfloat * vertices = new GLfloat[verticesSize];
	GLuint * indices = new GLuint[indicesSize];
	VBO * vbo;
	EBO * ebo;
	PerlinNoise3D noise(134, 6);
	GLfloat radiuschangestrength = 0.3;
	for (int i = 0; i < sphere.points.size(); i += 3)
	{
		GLfloat noisevalue = noise.Calculate((sphere.points[i]) / radius, (sphere.points[i + 1]) / radius, (sphere.points[i + 2])) / radius;
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
			vertices[i * 2 + 3] = 0.5 + sphere.points[i] / radius;
			vertices[i * 2 + 4] = 0.5 + sphere.points[i + 1] / radius;
			vertices[i * 2 + 5] = 0.5 + sphere.points[i + 2] / radius;
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

	delete[verticesSize] vertices;
	delete[indicesSize] indices;

	vao->Unbind();
	vbo->Delete();
	ebo->Delete();
};

void Asteroid::Draw(Shader& shader)
{
	vao->Bind();
	if (drawType == 0)glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
	else if (drawType == 1)glDrawElements(GL_LINES, indicesSize, GL_UNSIGNED_INT, 0);
}
