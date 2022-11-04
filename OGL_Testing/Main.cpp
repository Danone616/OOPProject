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
#include<chrono>

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

	Sphere s1(0.3f, 5, 1, 0);
	Sphere s2(0.3f, 5, 1, 0);
	Sphere s3(0.3f, 5, 1, 0);
	Grid grid1(100,3);
	Grid axis(0, 1);

	GLfloat rotation = 0.0f;
	glEnable(GL_DEPTH_TEST);
	Shader axisshader("line.vert", "line.frag");
	Shader shaderProgram("default.vert", "default.frag");
	shaderProgram.Activate();
	double FPS = 60;
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	float frames = 0;

	glm::vec3 velocity1 = { 0.0009f, 0.022f, 0.001f };
	s1.ChangePosition({ 1.000f, 2.000f, 3.000f }, 0.00f, { 1,1,1 });
	glm::vec3 velocity2 = { 0.0032f, 0.000f, 0.07f };
	s2.ChangePosition({ 5.500f, 5.500f, 0.000f }, 0.00f, { 1,1,1 });
	glm::vec3 velocity3 = { 0.012f, 0.000f, 0.000f };
	s2.ChangePosition({ 0.000f, 0.000f, 1.000f }, 0.00f, { 1,1,1 });
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
		velocity1 = velocity1 + (s2.position - s1.position) * 0.0001f;
		velocity1 = velocity1 + (s3.position - s1.position) * 0.0001f;
		velocity2 = velocity2 + (s1.position - s2.position) * 0.0001f;
		velocity2 = velocity2 + (s3.position - s2.position) * 0.0001f;
		velocity3 = velocity3 + (s1.position - s3.position) * 0.0001f;
		velocity3 = velocity3 + (s2.position - s3.position) * 0.0001f;
		s1.Draw(shaderProgram);
		s1.ChangePosition(velocity1, 0.01f, { 1,1,1 });
		s2.Draw(shaderProgram);
		s2.ChangePosition(velocity2, 0.01f, { 1,1,1 });
		s3.Draw(shaderProgram);
		s3.ChangePosition(velocity3, 0.01f, { 1,1,1 });

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}