#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader(const GLchar* vertexPath,const GLchar* fragmentPath);
	~Shader();
public:
	//使用/激活函数
	void use();
	//uniform工具函数
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string&name, float value) const;
private:
	unsigned int ID;
};

