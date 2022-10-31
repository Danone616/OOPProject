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
	vao.Bind();
	VBO vboa(vertices, sizeof(vertices));
	EBO eboa(indices, sizeof(indices));
	vao.Link(vboa, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	vao.Link(vboa, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));

	vao.Unbind();
	vboa.Delete();
	eboa.Delete();
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
	vao.Bind();
	glDrawElements(GL_TRIANGLES,indicesSize, GL_UNSIGNED_INT, 0);
}
//todo
/*
transfer sphere to the class(make it with VBOs and shit)(For simplicity make sphere and separate sphere with gl compatibitity)
make an asteroid class(same shit, gl compatible)
remove magic numbers from perlin noise generation
make the main loop framerate capped(FPS variable dependent, no magic numbers)
introduce camera class(kill me)
*/