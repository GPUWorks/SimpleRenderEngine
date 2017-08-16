#include "Mesh.h"
#include "TextureManager.h"
#include <glew\glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
namespace RenderSystem {

	void Mesh::setProgram(Shader::ptr shader)
	{
		_shader = shader;
		_shader->use();
		//if (_material)
	}
	void Mesh::setupBuffer()
	{
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);


		glBindVertexArray(_vao);
		glBindBuffer(GL_VERTEX_ARRAY, _vbo);

		glBufferData(GL_VERTEX_ARRAY, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

		if (!_indices.empty())
		{
			glGenBuffers(1, &_ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);
		}


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)24);

		glBindVertexArray(0);

	}
	bool Mesh::loadFromObjFile(const char* filename)
	{
		std::ifstream file(filename);
		if (!file)
		{
			std::cerr << "Error::ObjLoader, could not open obj file:"
				<< filename << " for reading." << std::endl;
			return false;
		}
		std::string line;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec3> positions;
		while (std::getline(file, line))
		{
			if (line.substr(0, 2) == "vt")     // ����������������
			{
				std::istringstream s(line.substr(2));
				glm::vec2 v;
				s >> v.x; s >> v.y;
				uvs.push_back(v);
			}
			else if (line.substr(0, 2) == "vn") // ���㷨��������
			{
				std::istringstream s(line.substr(2));
				glm::vec3 v;
				s >> v.x; s >> v.y; s >> v.z;
				normals.push_back(v);
			}
			else if (line.substr(0, 1) == "v")  // ����λ������
			{
				std::istringstream s(line.substr(1));
				glm::vec3 v;
				s >> v.x; s >> v.y; s >> v.z;
				positions.push_back(v);
			}
			else if (line.substr(0, 1) == "f")  // ������
			{
				Vertex v;
				//cout << "f ";
				std::istringstream vtns(line.substr(1));
				std::string vtn;
				while (vtns >> vtn)             // ����һ���ж����������
				{
					Vertex vertex;
					std::replace(vtn.begin(), vtn.end(), '/', ' ');
					std::istringstream ivtn(vtn);
					int uvindex, normalindex, posindex;
					if (vtn.find("  ") != std::string::npos) // û���������ݣ�ע��������2���ո�
					{

						ivtn >> posindex >> normalindex;

						vertex.Position = positions[posindex - 1];
						vertex.Normal = normals[normalindex - 1];
					}
					else
					{
						ivtn >> posindex >> uvindex >> normalindex;

						vertex.Position = positions[posindex - 1];
						vertex.TexCoords = uvs[uvindex - 1];
						vertex.Normal = normals[normalindex - 1];

					}
					vertices.push_back(vertex);
				}
			}
			else if (line[0] == '#')            // ע�ͺ���
			{
			}
			else
			{
				// �������� ��ʱ������
			}
		}
		this->setVertices(vertices);
	}
	void Mesh::render(Shader::ptr shader)
	{

	}
	void Mesh::draw()
	{
		//shader��ֵ
		_shader->use();
		_shader->setMat4("modelMatrix", _modelMatrix);
		if (_hasMaterial)
		{
			_shader->setVec3("ambientMt", _material.ambient);
			_shader->setVec3("diffuseMt", _material.diffuse);
			_shader->setVec3("specularMt", _material.specular);
			_shader->setFloat("shininessMt", _material.shininess);
		}
		if (!_textures.empty())
		{
			for (int i = 0; i < _textures.size(); i++)
			{
				TextureManager::Inst()->bindTexture(_textures[i]);
				_shader->setInt(_textures[i], TextureManager::Inst()->getTextureUnit(_textures[i]));
			}

		}

		glBindVertexArray(_vao);
		if (_indices.empty())
			glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
		else
			glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

}