#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

namespace RenderSystem {
	class RenderSystem {
	public:
		static RenderSystem* Inst();
		void beginRender();//��Ⱦ֮ǰ����renderstate
		void render(float time);
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

