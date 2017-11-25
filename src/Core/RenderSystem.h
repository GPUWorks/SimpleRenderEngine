#pragma once
#include <vector>
#include "Scene.h"
#include "Object.h"
#include "Camera.h"
#include "Mesh.h"
#include "Plugin.h"

namespace SRE {
	class RenderSystem {
	public:		
		RenderSystem(Scene* scene, Camera* camera);
		void render();				
	protected:
		void beforeRender();//��Ⱦ֮ǰ����renderstate		
		void renderImpl();
		void afterRender();//һ֡����	
		void resize(int x, int y, int width, int height);

		void projectObject(Object::ptr object);
	private:	
		Scene::ptr _scene;
		Camera::ptr _camera;	

		std::vector<Mesh::ptr> _meshs;
		std::vector<Light::ptr> _lights

	};
}


