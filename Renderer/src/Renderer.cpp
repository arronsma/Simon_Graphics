#include "Renderer.h"

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	//摁Esc键退出
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

int Renderer::init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//GLFW将窗口的上下文设置为当前线程的上下文
	glfwMakeContextCurrent(window);
	return 0;
}

int Renderer::Render() {

	//GLAD
	 //glad: 加载所有OpenGL函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	const GLubyte* name = glGetString(GL_VENDOR);
	const GLubyte* biaoshifu = glGetString(GL_RENDERER);
	const GLubyte* OpenGLVersion = glGetString(GL_VERSION);


	std::cout << ("OpenGL实现的版本号：") << ((char*)OpenGLVersion);
	Shader shader("vertexShader.vs", "fragmentShader.fs");

	float vertices[] = {
		-0.25f, -0.25f, 0.0f,
		 0.25f, -0.25f, 0.0f,
		 0.0f,  0.25f, 0.0f,

		 0.25f, -0.25f, 0.0f,
		 0.75f, -0.25f, 0.0f,
		 0.5f,  0.25f, 0.0f,
	};

	
	unsigned VAO_ID;
	glGenVertexArrays(1, &VAO_ID);
	glBindVertexArray(VAO_ID);

	unsigned VBO_ID;
	glGenBuffers(1, &VBO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 渲染循环
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //状态设置
		glClear(GL_COLOR_BUFFER_BIT); //状态使用
		shader.use();
		glBindVertexArray(VAO_ID);
		processInput(window);
		//glDrawBuffer(VBO_ID);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// glfw: 交换缓冲区和轮询IO事件（按键按下/释放、鼠标移动等）
		glfwSwapBuffers(window);
		glfwPollEvents();
		glBindVertexArray(0);
	}

	// glfw: 回收前面分配的GLFW先关资源. 
	glfwTerminate();
	return 0;
}

void Renderer::SetFramebufferSizeCallback(){
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void Renderer::Loop() {

}

