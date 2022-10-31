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

const int width = 900;
const int height = 900;

struct SphereS
{
	std::vector<GLfloat> points;//vertices
	std::vector<GLint> triangles;//indices
};

SphereS CreateSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat r, int depth)
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
		return {points,triangles};
	}
	SphereS sphere = CreateSphere(x, y, z, r, depth - 1);

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

GLfloat vertices[6138*2];
GLuint indices[6144*2];
int main()
{
	glfwInit();
	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Test", NULL, NULL);
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
	glViewport(0, 0, width, height);

	PerlinNoise3D noise(0, 6);

	float SphereCentre[3] = { 0,0,0 };

	SphereS sphere = CreateSphere(0.0f, 0.0f, 0.0f, 0.5f,5);

	//std::cout << sphere.triangles.size() << " " << sphere.points.size()<<std::endl;

	GLfloat radiuschangestrength = 1;

	

	for (int i = 0; i < sphere.points.size(); i += 3)
	{
		
		GLfloat noisevalue = noise.Calculate(sphere.points[i], sphere.points[i + 1], sphere.points[i + 2]);
		GLfloat radiuschange = 1+(2*radiuschangestrength*noisevalue-radiuschangestrength);

		//position
		vertices[i * 2] = sphere.points[i] * radiuschange;
		vertices[i * 2 + 1] = sphere.points[i + 1] * radiuschange;
		vertices[i * 2 + 2] = sphere.points[i + 2] * radiuschange;
		
		//color
		vertices[i * 2 + 3] = sphere.points[i]*2;
		vertices[i * 2 + 4] = sphere.points[i + 1]*2;
		vertices[i * 2 + 5] = sphere.points[i + 2]*2;
		
	}
	for (int i = 0; i < sphere.triangles.size(); i += 3)
	{
		indices[i] = sphere.triangles[i];
		indices[i + 1] = sphere.triangles[i + 1];
		indices[i + 2] = sphere.triangles[i + 2];
	}
	

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	VAO1.Link(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.Link(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	// Gets ID of uniform called "scale"

	// Generates Vertex Buffer Object and links it to vertices
	// Generates Element Buffer Object and links it to indices
	//EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	// Unbind all to prevent accidentally modifying them
	// Main while loop


	Sphere s(0.0f,0.0f,0.0f,0.5f,5);

	/*for (int i = 0; i < s.verticesSize; i += 6)
	{
		std::cout << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] << " " << vertices[i+3] << " " << vertices[i+4] << " " << vertices[i+5] << std::endl;
	}*/

	GLfloat rotation = 0.0f;
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		shaderProgram.Activate();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		rotation += 0.005f;

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 1.0f));

		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
		


		GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
		glUniform1f(uniID, 1.0f);

		// Generates Vertex Buffer Object and links it to vertices
		// Generates Element Buffer Object and links it to indices
		//EBO EBO1(indices, sizeof(indices));

		// Links VBO attributes such as coordinates and colors to VAO
		// Unbind all to prevent accidentally modifying them
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		
		s.vao.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		// Bind the VAO so OpenGL knows to use it
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