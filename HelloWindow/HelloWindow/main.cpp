#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void genTriangle();
void setShaders();
void setShadersYellow();
void genRectangle();
void genDTriangle();//产生两个相连的三角形
void genDTriangleSpe();//产生两个三角形，使用不同的VAO和VBO
//settings
unsigned int shaderProgram;
unsigned int shaderProgramYellow;
unsigned int VAO,VBO,EBO;
unsigned int VAOARR[2], VBOARR[2];
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
int main()
{
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/**这段代码不能放在最后面**/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	Shader myshader("Shader.vs", "shader.fs");
	//setShaders();
	//setShadersYellow();
	//genDTriangleSpe();
	genTriangle();
	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		///////////////////
		myshader.use();
		

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glUseProgram(shaderProgramYellow);
		//glBindVertexArray(VAOARR[1]);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void genTriangle()
{
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,1.0f,0.0f,0.0f,
	 0.5f, -0.5f, 0.0f,0.0f,1.0f,0.0f,
	 0.0f,  0.5f, 0.0f,0.0f,0.0f,1.0f
	};
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//绑定VAO,所有VAO之后创建的VBO都属于该VAO
	glBindVertexArray(VAO);

	//绑定VBO之后，后面的操作都是针对VBO进行的
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);//以顶点属性位置值作为参数，启动顶点属性

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//解除VBO的绑定
	glBindVertexArray(0);//接触VAO的绑定
}

void setShaders()
{
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	////判断是否编译成功
	//int success;
	//char infoLog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	//}
	//memset(infoLog, 0, sizeof(infoLog));
	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	//	cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << endl;
	//}

	//memset(infoLog, 0, sizeof(infoLog));
	///*unsigned int shaderProgram;*/
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);
	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success)
	//{
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//	cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << endl;
	//}
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
}

void genRectangle()
{
	float vertices[] = {
		0.5f,0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		-0.5f,-0.5f,0.0f,
		-0.5f,0.5f,0.0f
	};

	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};
	//创建三个对象
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//绑定VAO
	glBindVertexArray(VAO);

	//绑定VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//绑定EBO对象
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//设置属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void genDTriangle()
{
	float vertices[] = {
		//第一个三角形
		-0.5f,0.0f,0.0f,//左下
		0.0f,0.5f,0.0f,//右上
		0.0f,0.0f,0.0f,//右下
		//第二个三角形
		0.0f,0.5f,0.0f,//左上
		0.0f,0.0f,0.0f,//左下
		0.5f,0.0f,0.0f//左下
	};
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//绑定VAO
	glBindVertexArray(VAO);
	//绑定VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//设置指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//解除绑定
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void genDTriangleSpe()
{
	float vertices1[] = {
		//第一个三角形
		-0.5f,0.5f,0.0f,//左上
		0.0f,0.0f,0.0f,//中下
		0.5f,0.5f,0.0f,//右上
	};

	float vertices2[] = {
		//第二个三角形
		-0.5f,-0.5f,0.0f,//左下
		0.0f,0.0f,0.0f,//中上
		0.5f,-0.5f,0.0f//右下
	};

	//创建缓冲对象
	glGenBuffers(2, VBOARR);
	glGenVertexArrays(2, VAOARR);

	//绑定缓冲对象1
	glBindVertexArray(VAOARR[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOARR[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	//设置对象1的指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//绑定缓冲对象2
	glBindVertexArray(VAOARR[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOARR[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	//设置对象2的指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//解除绑定
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}

void setShadersYellow()
{
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	////判断是否编译成功
	//int success;
	//char infoLog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	//}
	//memset(infoLog, 0, sizeof(infoLog));
	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSourceYellow, NULL);
	//glCompileShader(fragmentShader);
	//glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	//	cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << endl;
	//}

	//memset(infoLog, 0, sizeof(infoLog));
	///*unsigned int shaderProgram;*/
	//shaderProgramYellow = glCreateProgram();
	//glAttachShader(shaderProgramYellow, vertexShader);
	//glAttachShader(shaderProgramYellow, fragmentShader);
	//glLinkProgram(shaderProgramYellow);
	//glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
	//if (!success)
	//{
	//	glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
	//	cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << endl;
	//}
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
}