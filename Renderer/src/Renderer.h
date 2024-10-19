#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "Screen/Window.h"

class Renderer {
public:
	int init();
	int Render();
	void Loop();
private:
	GLFWWindow* mainWindow;
};