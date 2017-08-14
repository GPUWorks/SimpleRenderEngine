//**********************************************
//��freeimage��ֲ����
//**********************************************

#ifndef TextureManager_H
#define TextureManager_H

#include <windows.h>
#include <glew\glew.h>
#include "FreeImage.h"
#include <map>
#include <vector>
namespace RenderSystem {
	class TextureManager
	{
	public:
		static TextureManager* Inst();
		virtual ~TextureManager();


		bool loadTexture(const char* filename, const char* texName, GLenum image_format = GL_RGB, GLint internal_format = GL_RGB, GLint level = 0, GLint border = 0);

		bool unloadTexture(const char* texName);

		bool loadCubeMap(std::vector<const char*> flies);

		bool bindTexture(const char* texName);
		bool bindTexture(const char* texName,bool isCube);

		GLuint getTextureUnit(const char* texName);

		void unloadAllTextures();

	protected:
		TextureManager();//��ֹ����
		TextureManager(const TextureManager& tm);//��ֹ����
		TextureManager& operator=(const TextureManager& tm);//��ֹ��ֵ

		static TextureManager* m_inst;
		std::map<const char*, GLuint> m_texID;
		unsigned int m_cubeMap;
	};

}

#endif