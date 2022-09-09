#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<cmath> 

#include"Shaders.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

GLfloat func(GLfloat x)
{
	return (GLfloat)(sin(40* x));
}

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



const int numberofpoints = 1000;
GLfloat vertices[6 * numberofpoints];
int main()
{

	// Vertices coordinates


	
	GLfloat valuelimitx = 10.0f,step = (valuelimitx * 2) / numberofpoints;
	GLfloat valuelimity = 0.5f;
	for (int c = 0; c < numberofpoints; c++)
	{
		vertices[c * 6] = (- valuelimitx + c * step)/(valuelimitx*2);
		vertices[c * 6+1] = func(-valuelimitx + c * step) / (valuelimity * 2);
		vertices[c * 6+2] = 0.0f;
		vertices[c * 6+3] = 1.0f;
		vertices[c * 6+4] = 1.0f;
		vertices[c * 6+5] = 1.0f;
	}
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Test", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(50, 50, 1800, 1000);



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
	GLfloat Xaxis[12] = {
	-0.5f,
	0.0f,
	0.0f,
	0.0f,
	1.0f,
	0.0f,

	0.5f,
	0.0f,
	0.0f,
	0.0f,
	1.0f,
	0.0f
	};
	GLfloat Yaxis[12] = {
		0.0f,
		-0.5f,
		0.0f,
		1.0f,
		0.0f,
		0.0f,

		0.0f,
		0.5f,
		0.0f,
		1.0f,
		0.0f,
		0.0f
	};
	VAO VAOX;
	VAOX.Bind();
	VBO VBOX(Xaxis, sizeof(Xaxis));
	VAOX.Link(VBOX, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAOX.Link(VBOX, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAOX.Unbind();
	VBOX.Unbind();

	VAO VAOY;
	VAOY.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBOY(Yaxis, sizeof(Yaxis));
	// Generates Element Buffer Object and links it to indices
	//EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAOY.Link(VBOY, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAOY.Link(VBOY, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAOY.Unbind();
	VBOY.Unbind();
	// Main while loop
	int time=0;
	int framecount = 0;
	const GLfloat timestep = 0.02f;
	while (!glfwWindowShouldClose(window))
	{
		framecount++;
		if (framecount % 10 == 0) {
			for (int c = 0; c < numberofpoints - 1; c++)
			{
				vertices[c * 6 + 1] = vertices[(c + 1) * 6 + 1];
				vertices[c * 6 + 3] = vertices[(c + 1) * 6 + 3];
				vertices[c * 6 + 4] = vertices[(c + 1) * 6 + 4];
				vertices[c * 6 + 5] = vertices[(c + 1) * 6 + 5];
			}
			vertices[(numberofpoints - 1) * 6 + 1] = func(valuelimitx + step * time) / (valuelimity * 2);
			vertices[(numberofpoints - 1) * 6 + 3] = red(time*timestep);
			vertices[(numberofpoints - 1) * 6 + 4] = green(time * timestep);
			vertices[(numberofpoints - 1) * 6 + 5] = blue(time * timestep);

			time++;
		}
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
		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 1.0f);
		// Bind the VAO so OpenGL knows to use it
		/*VAOX.Bind();
		glDrawArrays(GL_LINE_STRIP, 0, 2);
		VAOX.Unbind();
		VAOY.Bind();
		glDrawArrays(GL_LINE_STRIP, 0, 2);
		VAOY.Unbind();*/
		VAO1.Bind();
		glDrawArrays(GL_LINE_STRIP, 0, numberofpoints);
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