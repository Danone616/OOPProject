#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<cmath> 

#include"Shaders.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

GLfloat red(GLfloat time)
{
	return (sin(time)*sin(time) + 1) / 2.0f;
}
GLfloat green(GLfloat time)
{
	return (sin(time+ (3.14f/3)     )* sin(time + (3.14f / 3)) + 1) / 2.0f;
}
GLfloat blue(GLfloat time)
{
	return (sin(time+ (3.14f*2 / 3) )* sin(time + (3.14f*2 / 3)) + 1) / 2.0f;
}

const int numberofpoints = 4;
GLfloat vertices[6 * numberofpoints];
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	{
		vertices[0 * 6] = -1.0f;
		vertices[0 * 6 + 1] = -1.0f;
		vertices[0 * 6 + 2] = 0.0f;
		vertices[0 * 6 + 3] = 1.0f;
		vertices[0 * 6 + 4] = 1.0f;
		vertices[0 * 6 + 5] = 1.0f;

		vertices[1 * 6] = -1.0f;
		vertices[1 * 6 + 1] = 1.0f;
		vertices[1 * 6 + 2] = 0.0f;
		vertices[1 * 6 + 3] = 1.0f;
		vertices[1 * 6 + 4] = 1.0f;
		vertices[1 * 6 + 5] = 1.0f;

		vertices[2 * 6] = 1.0f;
		vertices[2 * 6 + 1] = -1.0f;
		vertices[2 * 6 + 2] = 0.0f;
		vertices[2 * 6 + 3] = 1.0f;
		vertices[2 * 6 + 4] = 1.0f;
		vertices[2 * 6 + 5] = 1.0f;

		vertices[3 * 6] = 1.0f;
		vertices[3 * 6 + 1] = 1.0f;
		vertices[3 * 6 + 2] = 0.0f;
		vertices[3 * 6 + 3] = 1.0f;
		vertices[3 * 6 + 4] = 1.0f;
		vertices[3 * 6 + 5] = 1.0f;
	
	}

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Test", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 1920, 1080);
	Shader shaderProgram("default.vert", "default.frag");
	int framecount = 0;
	const GLfloat timestep = 0.001f;
	while (!glfwWindowShouldClose(window))
	{
		framecount++;

		vertices[0 * 6 + 3] = red(timestep * framecount);
		vertices[0 * 6 + 4] = green(timestep * framecount);
		vertices[0 * 6 + 5] = blue(timestep * framecount);

		vertices[1 * 6 + 3] = red(timestep * (framecount + 1300));
		vertices[1 * 6 + 4] = green(timestep * (framecount + 1300));
		vertices[1 * 6 + 5] = blue(timestep * (framecount + 1300));

		vertices[2 * 6 + 3] = red(timestep * (framecount + 1300));
		vertices[2 * 6 + 4] = green(timestep * (framecount + 1300));
		vertices[2 * 6 + 5] = blue(timestep * (framecount + 1300));

		vertices[3 * 6 + 3] = red(timestep * (framecount));
		vertices[3 * 6 + 4] = green(timestep * (framecount));
		vertices[3 * 6 + 5] = blue(timestep * (framecount));
		std::cout << framecount << std::endl;

		VAO VAO1;
		VAO1.Bind();
		// Generates Vertex Buffer Object and links it to vertices
		VBO VBO1(vertices, sizeof(vertices));
		// Generates Element Buffer Object and links it to indices
		//EBO EBO1(indices, sizeof(indices));

		// Links VBO attributes such as coordinates and colors to VAO
		VAO1.Link(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		VAO1.Link(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		// Unbind all to prevent accidentally modifying them
		VAO1.Unbind();
		VBO1.Unbind();
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		VAO1.Bind();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, numberofpoints);
		VAO1.Unbind();

		VAO1.Delete();
		VBO1.Delete();

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	//EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}