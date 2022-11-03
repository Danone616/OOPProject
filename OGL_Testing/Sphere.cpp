#include "Sphere.h"



Sphere::Sphere(GLfloat radius,GLint precision,int colortype,int drawtype)
{
	colorType = colortype;
	drawType = drawtype;
	SphereStruct sphere = CreateSphere(0, 0, 0, radius, precision);

	verticesSize = 2 * sphere.points.size();
	if(drawType == 0)indicesSize = sphere.triangles.size();
	else if(drawType == 1)indicesSize = 2 * sphere.triangles.size();
	GLfloat* vertices = new GLfloat[verticesSize];
	GLuint* indices = new GLuint[indicesSize];
	VBO* vbo;
	EBO* ebo;

	for (int i = 0; i < sphere.points.size(); i += 3)
	{
		//position
		vertices[i * 2] = sphere.points[i];
		vertices[i * 2 + 1] = sphere.points[i + 1];
		vertices[i * 2 + 2] = sphere.points[i + 2];
		//color
		if (colorType == 0)
		{
			vertices[i * 2 + 3] = 1.0f;
			vertices[i * 2 + 4] = 1.0f;
			vertices[i * 2 + 5] = 1.0f;
		}
		if (colorType == 1)
		{
			vertices[i * 2 + 3] = 0.5 + sphere.points[i] /radius;
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
	else if(drawType == 1)for (int i = 0; i < sphere.triangles.size(); i += 3)
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
	vbo = new VBO(vertices, verticesSize*sizeof(GLfloat));
	ebo = new EBO(indices, indicesSize*sizeof(GLuint));
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

Sphere::SphereStruct Sphere::CreateSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat r, int depth)
{
	if (depth == 1)
	{
		std::vector<GLfloat> points =
		{
			x + r,y,z,
			x - r,y,z,
			x,y + r,z,
			x,y - r,z,
			x,y,z + r,
			x,y,z - r
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

		newx1 = (newx1 - x) * r / dist1 + x;
		newy1 = (newy1 - y) * r / dist1 + y;
		newz1 = (newz1 - z) * r / dist1 + z;
		GLfloat dist2 = sqrt((newx2 - x) * (newx2 - x) + (newy2 - y) * (newy2 - y) + (newz2 - z) * (newz2 - z));
		newx2 = (newx2 - x) * r / dist2 + x;
		newy2 = (newy2 - y) * r / dist2 + y;
		newz2 = (newz2 - z) * r / dist2 + z;
		GLfloat dist3 = sqrt((newx3 - x) * (newx3 - x) + (newy3 - y) * (newy3 - y) + (newz3 - z) * (newz3 - z));
		newx3 = (newx3 - x) * r / dist3 + x;
		newy3 = (newy3 - y) * r / dist3 + y;
		newz3 = (newz3 - z) * r / dist3 + z;

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

void Sphere::Draw(Shader& shader)
{
	vao->Bind();
	glm::mat4 positionmatrix = glm::mat4(1.0f);
	positionmatrix = glm::translate(positionmatrix, position);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "objectMatrix"), 1, GL_FALSE, glm::value_ptr(positionmatrix * orientation));
	if(drawType == 0)glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
	else if (drawType == 1)glDrawElements(GL_LINES, indicesSize, GL_UNSIGNED_INT, 0);
}

void Sphere::ChangePosition(glm::vec3 shift, GLfloat deg, glm::vec3 axis)
{
	position += shift;
	orientation = glm::rotate(orientation, deg, axis);
}



//todo
/*
add position matrices to asteroids
remove magic numbers from perlin noise generation
*/
