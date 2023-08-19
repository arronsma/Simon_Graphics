#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include<glm/glm.hpp>
class Renderer {
public:
	int init();
	int Render();
	void SetFramebufferSizeCallback();
	void Loop();
private:
	GLFWwindow* window;
};