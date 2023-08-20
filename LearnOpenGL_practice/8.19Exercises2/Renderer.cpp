#include "Renderer.h"

#include "Texture.h"
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

std::ostream& operator<<(std::ostream& os, glm::mat4 m) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << m[j][i] << " ";
		}
		std::cout << std::endl;
	}
	return os;
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


	std::cout << ("OpenGLʵ�ֵİ汾�ţ�") << ((char*)OpenGLVersion) << std::endl;
	Shader shader("vertexShader.vs", "fragmentShader.fs");
	
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
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
	
	glm::mat4 rMatirx = glm::mat4(1.0f);

	glm::mat4 tMatrix = glm::mat4(1.0f);
	tMatrix = glm::translate(tMatrix, { 0.45,0.45,0 });
	
	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //״̬����
		glClear(GL_COLOR_BUFFER_BIT); //״̬ʹ��
		shader.use();
		shader.setInt("texture2D_0", 0);
		shader.setInt("texture2D_1", 1);
		shader.setFloat("mixFactor", 0.2);
		shader.setMat4("transform", glm::mat4(1.0f));
		glBindVertexArray(VAO_ID);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glm::mat4 scaleTime(1.0f);
		scaleTime = glm::scale(scaleTime, glm::vec3(sin(glfwGetTime())));
		shader.setMat4("transform", tMatrix * scaleTime);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

