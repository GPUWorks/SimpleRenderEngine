#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "Scene.h"
#include "Camera.h"
namespace Core {
	class RenderSystem {//������չ��һ�������ר������Ⱦ�Ĺ���
	public:
		static RenderSystem* Inst();
		void beginRender();//��Ⱦ֮ǰ����renderstate
		void render();
		void render(Scene::ptr scene, Camera::ptr camera);

		void endRender();//һ֡����
	protected:
		RenderSystem() {}
		RenderSystem(const RenderSystem&);
		RenderSystem& operator = (const RenderSystem&);
	private:
		static RenderSystem* m_Inst;
	};
}
#endif // !RENDERSYSTEM_H

