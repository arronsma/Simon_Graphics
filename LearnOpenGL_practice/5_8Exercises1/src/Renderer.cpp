#include "Renderer.h"

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)	//��Esc���˳�
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
	//GLFW�����ڵ�����������Ϊ��ǰ�̵߳�������
	glfwMakeContextCurrent(window);
	return 0;
}

int Renderer::Render() {

	//GLAD
	 //glad: ��������OpenGL����ָ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	const GLubyte* name = glGetString(GL_VENDOR);
	const GLubyte* biaoshifu = glGetString(GL_RENDERER);
	const GLubyte* OpenGLVersion = glGetString(GL_VERSION);


	std::cout << ("OpenGLʵ�ֵİ汾�ţ�") << ((char*)OpenGLVersion);
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

	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //״̬����
		glClear(GL_COLOR_BUFFER_BIT); //״̬ʹ��
		shader.use();
		glBindVertexArray(VAO_ID);
		processInput(window);
		//glDrawBuffer(VBO_ID);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// glfw: ��������������ѯIO�¼�����������/�ͷš�����ƶ��ȣ�
		glfwSwapBuffers(window);
		glfwPollEvents();
		glBindVertexArray(0);
	}

	// glfw: ����ǰ������GLFW�ȹ���Դ. 
	glfwTerminate();
	return 0;
}

void Renderer::SetFramebufferSizeCallback(){
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void Renderer::Loop() {

}

