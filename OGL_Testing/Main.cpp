#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<cmath>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<utility>
#include<vector>

#include"Shaders.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"PerlinNoise3D.h"
#include"Sphere.h"
#include"Asteroid.h"

const int width = 900;
const int height = 900;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(width, height, "Test", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	PerlinNoise3D noise(0, 6);

	/*float SphereCentre[3] = {0,0,0};

	Sphere::SphereStruct sphere = Sphere::CreateSphere(0.0f, 0.0f, 0.0f, 0.5f,5);

	GLfloat radiuschangestrength = 1;

	for (int i = 0; i < sphere.points.size(); i += 3)
	{
		
		GLfloat noisevalue = noise.Calculate(sphere.points[i], sphere.points[i + 1], sphere.points[i + 2]);
		GLfloat radiuschange = 1+(2*radiuschangestrength*noisevalue-radiuschangestrength);

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
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	VAO1.Link(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.Link(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	*/
	
	Sphere s1(0.5f, 5, 1, 0);
	Sphere s2(0.5f, 5, 1, 0);
	Sphere s3(0.5f, 5, 1, 0);
	Sphere s4(0.5f, 5, 1, 0);

	GLfloat rotation = 0.0f;
	glEnable(GL_DEPTH_TEST);
	Shader shaderProgram("default.vert", "default.frag");
	shaderProgram.Activate();
	glm::mat4 model1 = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
	proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);
	while (!glfwWindowShouldClose(window))
	{
		rotation += 0.05f;

		
		model1 = glm::translate(model1, glm::vec3(0.0f, 0.0f, -0.0001f));
		glm::mat4 model = glm::rotate(model1, glm::radians(rotation), glm::vec3(1.0f, 1.0f, 1.0f));

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
		glUniform1f(uniID, 1.0f);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		s1.Draw();
		/*s2.Draw();
		s3.Draw();
		s4.Draw();*/

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}