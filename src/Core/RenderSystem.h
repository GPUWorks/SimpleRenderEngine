#pragma once
#include <vector>
#include "Scene.h"
#include "Object.h"
#include "Camera.h"
#include "Mesh.h"
#include "Plugin.h"

namespace Core {
	class RenderSystem {
	public:		
		RenderSystem(Scene* scene, Camera* camera);
		void render();				
	protected:
		void beforeRender();//��Ⱦ֮ǰ����renderstate		
		void renderImpl();
		void afterRender();//һ֡����		
	private:	
		Scene::ptr _scene;
		Camera::ptr _camera;	


	};
}


