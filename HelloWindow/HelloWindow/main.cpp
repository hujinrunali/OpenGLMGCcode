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
void genDTriangle();//��������������������
void genDTriangleSpe();//�������������Σ�ʹ�ò�ͬ��VAO��VBO
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

	/**��δ��벻�ܷ��������**/
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
	//��VAO,����VAO֮�󴴽���VBO�����ڸ�VAO
	glBindVertexArray(VAO);

	//��VBO֮�󣬺���Ĳ����������VBO���е�
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);//�Զ�������λ��ֵ��Ϊ������������������

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);//���VBO�İ�
	glBindVertexArray(0);//�Ӵ�VAO�İ�
}

void setShaders()
{
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	////�ж��Ƿ����ɹ�
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
	//������������
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//��VAO
	glBindVertexArray(VAO);

	//��VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//��EBO����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//��������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void genDTriangle()
{
	float vertices[] = {
		//��һ��������
		-0.5f,0.0f,0.0f,//����
		0.0f,0.5f,0.0f,//����
		0.0f,0.0f,0.0f,//����
		//�ڶ���������
		0.0f,0.5f,0.0f,//����
		0.0f,0.0f,0.0f,//����
		0.5f,0.0f,0.0f//����
	};
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//��VAO
	glBindVertexArray(VAO);
	//��VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//����ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//�����
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void genDTriangleSpe()
{
	float vertices1[] = {
		//��һ��������
		-0.5f,0.5f,0.0f,//����
		0.0f,0.0f,0.0f,//����
		0.5f,0.5f,0.0f,//����
	};

	float vertices2[] = {
		//�ڶ���������
		-0.5f,-0.5f,0.0f,//����
		0.0f,0.0f,0.0f,//����
		0.5f,-0.5f,0.0f//����
	};

	//�����������
	glGenBuffers(2, VBOARR);
	glGenVertexArrays(2, VAOARR);

	//�󶨻������1
	glBindVertexArray(VAOARR[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOARR[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	//���ö���1��ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//�󶨻������2
	glBindVertexArray(VAOARR[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOARR[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	//���ö���2��ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//�����
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}

void setShadersYellow()
{
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	////�ж��Ƿ����ɹ�
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