#include "Renderer.h"

#include "Texture.h"
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


	std::cout << ("OpenGL实现的版本号：") << ((char*)OpenGLVersion) << std::endl;
	Shader shader("vertexShader.vs", "fragmentShader.fs");
	
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	
	unsigned VAO_ID;
	unsigned VBO_ID;
	unsigned EBO_ID;
	glGenVertexArrays(1, &VAO_ID);
	glGenBuffers(1, &VBO_ID);
	glGenBuffers(1, &EBO_ID);

	glBindVertexArray(VAO_ID);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	Texture t("../resources/textures/container.jpg", GL_TEXTURE0);
	Texture t2("../resources/textures/awesomeface.png", GL_TEXTURE1);
	
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
	auto rotate2D = glm::mat2(trans);
	// 渲染循环
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //状态设置
		glClear(GL_COLOR_BUFFER_BIT); //状态使用
		shader.use();
		shader.setInt("texture2D_0", 0);
		shader.setInt("texture2D_1", 1);
		shader.setMat2("transform", rotate2D);
		glBindVertexArray(VAO_ID);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


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


