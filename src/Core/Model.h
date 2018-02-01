#pragma once

#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h>
#include "RenderObject.h"
namespace SRE {
	
	//mesh,submesh --> sub mesh����mesh����

	class Model : public Object{
	public:

		Object* loadModel(const std::string& path);
		void saveModel(const std::string fileName);
	protected:
		Object* processNode(aiNode* node, const aiScene* scene);
		aiScene* modelToAiScene();
		RenderObject* processMesh(aiMesh* mesh, const aiScene* scene);
		Material::ptr parseMaterial(aiMaterial *mat);
		TextureUnitState::ptr parseTexture(aiTextureType type, aiMaterial* aiMat);
		string directory;
		//std::vector<RenderObject::ptr> 

	};
}