#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

class Renderer {
public:
	int init();
	int Render();
	void SetFramebufferSizeCallback();
	void Loop();
private:
	GLFWwindow* window;
};