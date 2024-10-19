#include "Window.h"
#include <iostream>

int GLFWWindow::Init(int width, int height)
{
	this->width = width;
	this->height = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//GLFW Get Context
	glfwMakeContextCurrent(window);
	return 0;
}

void GLFWWindow::SetFramebufferSizeCallback(GLFWframebuffersizefun framebuffer_size_callback) {
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

bool GLFWWindow::ShouldClose()
{
	return glfwWindowShouldClose(window);
}


void GLFWWindow::ProcessInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	// press ESC key
		glfwSetWindowShouldClose(window, true);
}

void GLFWWindow::SwapBuffers() {
	glfwSwapBuffers(window);
}
