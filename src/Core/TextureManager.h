//**********************************************
//��freeimage��ֲ����
//**********************************************

#pragma once
#include <glew\glew.h>
#include <windows.h>
#include "FreeImage.h"
#include <map>
#include <vector>
#include "Texture.h"
namespace Core {
	class TextureManager
	{
	public:
		static TextureManager* Inst();
		virtual ~TextureManager();

		Texture::ptr createFromFile(const char* filename);
		bool loadTexture(const char* filename, const std::string texName, GLenum image_format = GL_RGB, GLint internal_format = GL_RGB, GLint level = 0, GLint border = 0);

		bool unloadTexture(std::string texName);

		bool loadCubeMap(std::vector<const char*> flies);

		bool bindTexture(const std::string texName, int units);
		bool bindTexture(const std::string texName, bool isCube);

		GLuint getTextureUnit(const std::string texName);

		void unloadAllTextures();

		void addTexture(const std::string texName, GLuint textureID);

	protected:
		TextureManager();//��ֹ����
		TextureManager(const TextureManager& tm);//��ֹ����
		TextureManager& operator=(const TextureManager& tm);//��ֹ��ֵ

		static TextureManager* m_inst;
		std::map<std::string, GLuint> m_texID;
		unsigned int m_cubeMap;
	};

}

