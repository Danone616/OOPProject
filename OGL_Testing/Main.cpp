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

	


	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	Sphere s1(0.3f, 5, 1, 0);
	Sphere s2(0.3f, 5, 1, 0);

	GLfloat rotation = 0.0f;
	glEnable(GL_DEPTH_TEST);
	Shader shaderProgram("default.vert", "default.frag");
	shaderProgram.Activate();
	double FPS = 60;
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	float frames = 0;

	glm::vec3 velocity1 = { 0.05f, 0.000f, 0.000f };
	s1.ChangePosition({ 1.000f, 1.000f, 0.000f }, 0.00f, { 1,1,1 });
	glm::vec3 velocity2 = { -0.05f, -0.000f, -0.000f };
	s2.ChangePosition(-s1.position, 0.00f, {1,1,1});
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
		//std::cout << time_span.count()<<std::endl;

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 10000.0f, shaderProgram, "camMatrix");
		

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//s1.Draw();
		velocity1 = velocity1 - (s2.position - s1.position) * 0.0001f;
		velocity2 = velocity2 - (s1.position - s2.position) * 0.0001f;
		s2.Draw(shaderProgram);
		s2.ChangePosition(velocity1, 0.01f, { 1,1,1 });
		s1.Draw(shaderProgram);
		s1.ChangePosition(velocity2, 0.01f, { 1,1,1 });

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}