#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	this->width = width;
	this->height = height;
	this->Position = position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, UP);
	proj = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(proj * view));
}

void Camera::Inputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += Orientation * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += -glm::normalize(glm::cross(Orientation,UP)) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += -Orientation * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += glm::normalize(glm::cross(Orientation, UP)) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += UP * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += -UP * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed=0.4;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed=0.1;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstclick)
		{
			glfwSetCursorPos(window, width / 2, height / 2);
			firstclick = false;
		}

		double mouseX, mouseY = 0;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotx = sensitivity * (float)(mouseY - height / 2) / height;
		float roty = sensitivity * (float)(mouseX - width / 2) / width;

		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotx), glm::normalize(glm::cross(Orientation, UP)));

		if (!(glm::angle(newOrientation, UP) <= glm::radians(5.0f) || glm::angle(newOrientation, -UP) <= glm::radians(5.0f)))
		{
			Orientation = newOrientation;
		}
		Orientation = glm::rotate(Orientation, glm::radians(-roty),UP);

		glfwSetCursorPos(window, width / 2, height / 2);

	}

}