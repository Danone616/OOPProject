
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include<utility>

#include<vector>
#include<chrono>
#include<cmath>
#include<iostream>
#include<algorithm>

#include"Shaders.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"PerlinNoise3D.h"
#include"Sphere.h"
#include"Asteroid.h"
#include"Camera.h"
#include"Line.h"
#include"Grid.h"

const int width = 1000;
const int height = 1000;
const GLfloat mindist = 0.1f;

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

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 0.0f));

	Sphere s1(0.3f, 5, 0, 0);
	Sphere s2(0.3f, 5, 1, 0);
	Sphere s3(0.3f, 5, 0, 0);
	Grid grid1(100,3);
	Grid axis(0, 1);

	GLfloat rotation = 0.0f;
	glEnable(GL_DEPTH_TEST);
	Shader axisshader("line.vert", "line.frag");
	Shader shaderProgram("default.vert", "default.frag");
	shaderProgram.Activate();
	GLfloat* light = new GLfloat[3];
	light[0] = 1;
	light[1] = 1;
	light[2] = 1;
	//LightSource
	double FPS = 60;
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	float frames = 0;
	
	GraphicsObject* object;
	glm::vec3 velocity1 = { 0.0f, 0.0f, 0.0f };
	s1.ChangePosition({ 0.000f, 3.000f, 0.000f }, 0.00f, { 1,1,1 });
	glm::vec3 velocity2 = { 0.0f, 0.0f, 0.0f };
	s2.ChangePosition({ 5.500f, -5.500f, 0.000f }, 0.00f, { 1,1,1 });
	glm::vec3 velocity3 = { 0.0f, 0.0f, 0.0 };
	s3.ChangePosition({ -4.000f, 2.000f, 1.000f }, 0.00f, { 1,1,1 });
	/*velocity1 = {0.0f, 0.0f, 0.0f};
	velocity2 = { 0.0f, 0.0f, 0.0f };
	velocity3 = { 0.0f, 0.0f, 0.0f };*/
	bool pause = true;
	while (!glfwWindowShouldClose(window))
	{
		rotation += 0.05f;
		std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
		frames+=1;
		
		while (time_span.count()<1/FPS)
		{
			t2 = std::chrono::high_resolution_clock::now();
			time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
		}
		t1= std::chrono::high_resolution_clock::now();

		camera.Inputs(window);
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		axisshader.Activate();
		camera.Matrix(45.0f, 0.1f, 100000.0f, axisshader, "camMatrix");
		axis.Draw();
		camera.Matrix(45.0f, 0.1f, 10.0f, axisshader, "camMatrix");
		grid1.Draw();

		shaderProgram.Activate();
		camera.Matrix(45.0f, 0.1f, 10000.0f, shaderProgram, "camMatrix");
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		{
			pause = false;
		}
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
		{
			pause = true;
		}
		if(!pause)
		{
			std::cout << glm::dot((s2.position - s1.position), (s2.position - s1.position))<<std::endl;
			velocity1 = velocity1 + 0.01f * glm::normalize((s2.position - s1.position)) / std::max(glm::dot((s2.position - s1.position), (s2.position - s1.position)), mindist);
			velocity1 = velocity1 + 0.01f * glm::normalize((s3.position - s1.position)) / std::max(glm::dot((s3.position - s1.position), (s3.position - s1.position)), mindist);
			velocity2 = velocity2 + 0.01f * glm::normalize((s1.position - s2.position)) / std::max(glm::dot((s1.position - s2.position), (s1.position - s2.position)), mindist);
			velocity2 = velocity2 + 0.01f * glm::normalize((s3.position - s2.position)) / std::max(glm::dot((s3.position - s2.position), (s3.position - s2.position)), mindist);
			velocity3 = velocity3 + 0.01f * glm::normalize((s1.position - s3.position)) / std::max(glm::dot((s1.position - s3.position), (s1.position - s3.position)), mindist);
			velocity3 = velocity3 + 0.01f * glm::normalize((s2.position - s3.position)) / std::max(glm::dot((s2.position - s3.position), (s2.position - s3.position)), mindist);

			std::cout << s2.position.x << " " << s1.position.x << " " << glm::normalize((s2.position - s1.position)).x << std::endl;

			s1.ChangePosition(velocity1, 0.00f, { 1,1,1 });
			s2.ChangePosition(velocity2, 0.00f, { 1,1,1 });
			s3.ChangePosition(velocity3, 0.00f, { 1,1,1 });

		s2.ChangePosition(-s1.position, 0.0f, {1,1,1});
		s3.ChangePosition(-s1.position, 0.0f, { 1,1,1 });

		s1.ChangePosition(-s1.position, 0.0f, { 1,1,1 });
		}
		GLfloat* shinecolor = new GLfloat[3];
		shinecolor[0] = 1;
		shinecolor[1] = 1;
		shinecolor[2] = 1;
		GLfloat* nullvector = new GLfloat[3];
		shinecolor[0] = 0;
		shinecolor[1] = 0;
		shinecolor[2] = 0;
		glUniform3fv(glGetUniformLocation(shaderProgram.ID, "Shinecolor"), 1, shinecolor);
		glUniform3fv(glGetUniformLocation(shaderProgram.ID, "LightSource"), 1, value_ptr(s1.position));
		s1.Draw(shaderProgram);
		glUniform3fv(glGetUniformLocation(shaderProgram.ID, "Shinecolor"), 1, nullvector);
		s2.Draw(shaderProgram);
		s3.Draw(shaderProgram);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}