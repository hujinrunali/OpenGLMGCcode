#pragma once
//����ṹ��
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <assimp/scene.h>
#include "Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;//����
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	std::string type;//��������
	aiString path;//����·��
};


class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices,std::vector<unsigned int> indices,std::vector<Texture> textures);
	~Mesh();

	void Draw(Shader shader);
public:
	/*��������*/
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	unsigned int VAO;
private:
	void setupMesh();
private:
	unsigned int VBO, EBO;
};
